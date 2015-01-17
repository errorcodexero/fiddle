/*This is the sample program to notify us for the file creation and file deletion takes place in “/tmp” directory*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
//#include <linux/inotify.h>
#include <sys/inotify.h>
#include<unistd.h>
#include<cassert>
#include<iostream>
#include<fcntl.h>
#include "update.h"

using namespace std;

#define EVENT_SIZE ( sizeof (struct inotify_event) )

Inotify::Inotify():fd_(inotify_init()){
	if(fd_==-1) throw "inotify_init";
}

Inotify::~Inotify(){
	close(fd_);
}

int Inotify::fd()const{ return fd_; }

Watch::Watch(int fd1):fd(fd1){
	assert(fd1!=-1);

	//probably want to make these args all get passed in
	wd=inotify_add_watch(fd,"/tmp",IN_CREATE|IN_DELETE);
	if(wd<0) throw "failed to add watch";
}

Watch::~Watch(){
	inotify_rm_watch(fd,wd);
}

Watch_file::Watch_file():b(a.fd()){
	int r=fcntl(a.fd(),F_SETFL,fcntl(a.fd(),F_GETFL)|O_NONBLOCK);
	if(r==-1){
		//could look at errno
		throw "fcntl failed";
	}
}

//non-blocking
bool Watch_file::change()const{
	static const unsigned BUF=EVENT_SIZE+16;//not sure where this 16 is coming from
	char buffer[BUF];
	auto r=read(a.fd(),buffer,BUF);
	if(r==-1){
		if(errno==EAGAIN) return 0;
		throw "read failed"; //should do something with errno
	}
	while(1){
		r=read(a.fd(),buffer,BUF);
		if(r==-1){
			if(errno==EAGAIN) return 1;
			throw "read failed";
		}
	}
}

#ifdef WATCH_FILE_TEST
int main(){
	Watch_file w;
	for(unsigned i=0;;i++){
		cout<<i<<":"<<w.change()<<"\n";
		sleep(1);
	}
}
#endif
