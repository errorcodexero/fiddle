#ifndef COMMON_H
#define COMMON_H

#include<vector>
#include<string>

std::vector<unsigned> range(unsigned lim);

template<typename T>
std::vector<T>& operator|=(std::vector<T>& v,T t){
	v.push_back(t);
	return v;
}

template<typename T>
T max(std::vector<T> v){
	assert(v.size());
	auto r=v[0];
	for(auto elem:v) r=max(r,elem);
	return r;
}

struct Tag{
	std::string name;

	explicit Tag(std::string);
	~Tag();
};

unsigned max_pts(unsigned totes,unsigned cans,unsigned max_stack_height);

#endif
