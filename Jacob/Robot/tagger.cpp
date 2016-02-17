/*
	logger.cpp defines functions inside the class Logger found in logger.h
*/
#include <iostream>
#include <fstream>
#include "tagger.h"
using namespace std;

void tagThis(string str, string str2){
	fstream myfile("../doc/tagger/taglog.csv", ofstream::out | ofstream::app);
	myfile << "---------------------,";
	str2.erase(str2.size());
	str2.append(",");
	str2.append(str);
	myfile << str2<< endl;
	myfile.close();
}

/*void tagThis(string str){
	ofstream myfile("log.csv");
	
	myfile << str;
	myfile.close();
}*/
