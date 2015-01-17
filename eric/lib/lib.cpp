#include<stdio.h>
#include<cassert>
#include<iostream>
#include "lib.h"

using namespace std;

void ctest1(int *a){
	printf("hi1\n");
	if(a) (*a)++;
}

void ctest2(int *b){
	printf("hi2\n");
	if(b) (*b)*=2;
}

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
