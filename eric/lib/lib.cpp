#include<stdio.h>
#include<cassert>
#include<iostream>
#include "lib.h"

using namespace std;

struct A{};

#ifndef MESSAGE
#define MESSAGE "HI THERE\n";
#endif

void *init(){
	cout<<"lib init\n";
	return new A{};
}

Robot_output run(void *a,Robot_input){
	assert(a);
	cout<<MESSAGE;
	return Robot_output{};
}

void destroy(void *a){
	cout<<"lib destroy\n";
	assert(a);
	delete (A*)a;
}
