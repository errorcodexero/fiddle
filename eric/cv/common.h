#ifndef COMMON_H
#define COMMON_H

#include<sstream>
#include<cv.h>

#define nyi { std::cout<<"NYI "<<__FILE__<<":"<<__LINE__<<"\n"; exit(44); }

template<typename T>
std::vector<T>& operator|=(std::vector<T>& v,T t){
	v.emplace_back(std::move(t));
	return v;
}

template<typename Func,typename Collection>
auto mapf(Func f,Collection const& c)->std::vector<decltype(f(*std::begin(c)))>{
	std::vector<decltype(f(*std::begin(c)))> r;
	for(auto a:c) r|=f(a);
	return r;
}

std::vector<std::string> split(std::string s){
	std::vector<std::string> r;
	std::stringstream ss;
	auto push=[&](){
		if(ss.str().size()){
			r|=ss.str();
			ss.str("");
		}
	};
	for(auto c:s){
		if(isblank(c)){
			push();
		}else{
			ss<<c;
		}
	}
	push();
	return r;
}

std::vector<std::string> split(char c,std::string s){
	std::vector<std::string> r;
	std::stringstream ss;
	auto push=[&](){
		r|=ss.str();
		ss.str("");
	};
	for(auto here:s){
		if(here==c){
			push();
		}else{
			ss<<here;
		}
	}
	push();
	return r;
}

//size of the monitor in px
Size display_size(){
	const char *command="xrandr|grep '*'";
	FILE *fpipe=popen(command,"r");
	char line[256];
	vector<string> r;
	while(fgets(line,sizeof(line),fpipe)){
		r|=string(line);
	}
	pclose(fpipe);
	assert(r.size()==1);//not dealing w/ 0 or multi-screen setups at this time
	auto sp=split(r[0]);
	assert(sp.size());
	auto sp2=split('x',sp[0]);
	assert(sp2.size()==2);
	auto x=atoi(sp2[0].c_str());
	auto y=atoi(sp2[1].c_str());
	assert(x);
	assert(y);
	return Size(x,y);
}

Size operator/(Size a,unsigned u){
	assert(u);
	return {(int)(a.width/u),(int)(a.height/u)};
}

#endif
