#include <stdio.h>
#include <dlfcn.h>
#include<stdlib.h>
#include<assert.h>
#include<sstream>
#include<memory>
#include<unistd.h>
#include<iostream>
#include "lib.h"
#include "inotify/update.h"

using namespace std;

void *load_func(void *lib_handle,const char *name){
	void *r=dlsym(lib_handle,name);
	{
		char *error=dlerror();
		if(error){
			fprintf(stderr, "%s\n", error);
			exit(1);
		}
	}
	assert(r);
	return r;
}

class Library{
	void *handle;

	Library(Library const&);
	Library& operator=(Library const&);

	public:
	Library():handle(dlopen("./liblib.so", RTLD_LAZY)){
		cout<<"open lib\n";
		cout.flush();
		if(!handle){
			stringstream ss;
			ss<<dlerror()<<"\n";
			throw ss.str();
		}
	}

	~Library(){
		cout<<"close lib\n";
		cout.flush();
		dlclose(handle);//should see what this does w/ null
	}

	void *get()const{ return handle; }
};

class Lib{
	typedef void *(*Init)();
	typedef Robot_output (*Run)(void*,Robot_input);
	typedef void (*Destroy)(void*);

	Library library;
	Init init;
	Run run_;
	Destroy destroy;

	void *data;

	Lib(Lib const&);
	Lib& operator=(Lib const&);

	public:
	explicit Lib():
		init((Lib::Init)load_func(library.get(),"init")),
		run_((Lib::Run)load_func(library.get(),"run")),
		destroy((Lib::Destroy)load_func(library.get(),"destroy")),
		data(init())
	{}

	~Lib(){
		destroy(data);
	}

	Robot_output run(Robot_input in){ return run_(data,in); }
};

int main(int argc,char **argv)
{
	shared_ptr<Lib> lib=make_shared<Lib>();
	Watch_file w;
	while(1){
		if(w.change()){
			cout<<"reload\n";
			cout.flush();
			lib.reset();
			lib=make_shared<Lib>();
		}else{
			lib->run(Robot_input{});
			sleep(1);
		}
	}
	return 0;
}
