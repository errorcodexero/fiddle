//Author: Logan Traffas
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

int X_LIMIT=2;
int Y_LIMIT=2;

enum class Action{FORWARD, BACKWARD, RIGHT, LEFT, LIFT, DROP};//Types of actions the robot can preform during autonomous

ostream& operator<<(ostream & o, Action in){//How to print the types of instructions
	if(in==Action::FORWARD){
		o<<"Instruction: FORWARD  ";
	}
	else if(in==Action::BACKWARD){
		o<<"Instruction: BACKWARD ";
	}
	else if(in==Action::RIGHT){
		o<<"Instruction: RIGHT    ";
	}
	else if(in==Action::LEFT){
		o<<"Instruction: LEFT     ";
	}
	else if(in==Action::LIFT){
		o<<"Instruction: LIFT     ";
	}
	else if(in==Action::DROP){
		o<<"Instruction: DROP     ";
	}
	return o;
}

struct Environment_state{//Type to store the states of the environment
	struct Robot_state{//Type to store the current states of the robot
		pair<int, int> location;
		bool with_tote;
		Robot_state():with_tote(0){}
	};
	Robot_state robot;
	pair<int, int> tote_location;
};

ostream & operator<<(ostream & o, Environment_state in){//How to print type Environment_state
	o<<"Robot location: ("<<in.robot.location.first<<","<<in.robot.location.second<<")   Tote location: ("<<in.tote_location.first<<","<<in.tote_location.second<<")   Robot with tote: "<<in.robot.with_tote;
	return o;
}

ostream & operator<<(ostream & o, vector<Environment_state> in){//How to print type vector<Action>
	for(unsigned int i=0; i<in.size(); i++){
		o<<in[i];
	}
	return o;
}

ostream & operator<<(ostream & o, vector<Action> in){//How to print type vector<Action>
	for(unsigned int i=0; i<in.size(); i++){
		o<<in[i];
	}
	return o;
}

bool operator==(pair<int, int> a, pair<int, int> b) {
	if(a.first==b.first && a.second==b.second) return 1;
	return 0;
}

bool operator!=(pair<int, int> a, pair<int, int> b) {
	if(a.first!=b.first || a.second!=b.second) return 1;
	return 0;
}

Environment_state update_environment(Action instruction, Environment_state environment){//Determines what the robot does
	if(instruction==Action::LEFT)environment.robot.location.first--;
	if(instruction==Action::RIGHT)environment.robot.location.first++;
	if(instruction==Action::BACKWARD)environment.robot.location.second--;
	if(instruction==Action::FORWARD)environment.robot.location.second++;
	if(instruction==Action::LIFT && environment.robot.location==environment.tote_location)environment.robot.with_tote=1;
	if(instruction==Action::DROP && environment.robot.with_tote==1)environment.robot.with_tote=0;
	if(environment.robot.with_tote==1)environment.tote_location=environment.robot.location;
	return environment;
}

/*int randomize_environment(){//Randomizes the starting environment
	srand(time(NULL));
	int random=rand()%2;
	return random;
}*/

pair<int, int> make_pair(int a, int b){
	pair<int, int> c;
	c.first=a;
	c.second=b;
	return c;
}

vector<Action> get_possible_moves(Environment_state environment){
	vector<Action> possible_moves;
	if(environment.robot.location.first-1>=0){
		possible_moves.push_back(Action::LEFT);
	}
	if(environment.robot.location.first+1<X_LIMIT){
		possible_moves.push_back(Action::RIGHT);
	}
	if(environment.robot.location.second-1>=0){
		possible_moves.push_back(Action::BACKWARD);
	}
	if(environment.robot.location.second+1<Y_LIMIT){
		possible_moves.push_back(Action::FORWARD);
	}
	if(environment.robot.location==environment.tote_location && environment.robot.with_tote==0){
		possible_moves.push_back(Action::LIFT);
	}
	if(environment.robot.with_tote==1){
		possible_moves.push_back(Action::DROP);
	}
	return possible_moves;
}

vector<Environment_state> states(){
	Environment_state environment;
	vector<Environment_state> r;
	for(int x=0; x<X_LIMIT; x++){
		for(int y=0; y<Y_LIMIT; y++){
			environment.robot.location=make_pair(x,y);
			for(int z=0; z<X_LIMIT; z++){
				for(int w=0; w<Y_LIMIT; w++){
					environment.tote_location=make_pair(z,w);
					r.push_back(environment);
				}
			}
			environment.robot.with_tote=1;
			environment.tote_location=environment.robot.location;
			r.push_back(environment);
			environment.robot.with_tote=0;
		}
		
	}	
	return r;
}

vector<Action> get_instructions(Environment_state environment){//Gets instructions from a random starting environment
	vector<Action> instructions;
	return instructions;
}

bool operator!=(Environment_state a, Environment_state b) {
	if (a.robot.location!=b.robot.location || a.robot.with_tote!=b.robot.with_tote || a.tote_location!=b.tote_location) return 1;
	return 0;
}

bool operator==(Environment_state a, Environment_state b) {
	if (a.robot.location==b.robot.location && a.robot.with_tote==b.robot.with_tote && a.tote_location==b.tote_location) return 1;
	return 0;
}

double distance_formula(pair<int, int> a, pair<int, int> b){
	double distance=0;
	distance=sqrt(((a.first-b.first)^2) + ((a.second-b.second)^2));
	return distance;
}

bool closer(Environment_state a, Environment_state b, Environment_state c){//Work On This
	if(c.tote_location!=a.tote_location){
		if(a.tote_location!=a.robot.location) {
			if(c.robot.with_tote==1 && a.robot.with_tote==1){
				if(distance_formula(c.robot.location, a.robot.location)>distance_formula(c.robot.location, b.robot.location)) return 1;
			}
			if(c.robot.with_tote==0 && a.robot.with_tote==1){
				if(distance_formula(c.tote_location, a.robot.location)>distance_formula(c.tote_location, b.robot.location)) return 1;
			}
			if(c.robot.with_tote==1 && a.robot.with_tote==0){
				if(distance_formula(a.tote_location, a.robot.location)>distance_formula(a.tote_location, b.robot.location)) return 1;
			}
			if(c.robot.with_tote==0 && a.robot.with_tote==0){
				if(distance_formula(a.tote_location, a.robot.location)>distance_formula(a.tote_location, b.robot.location)) return 1;
			}
		} else {
		//	if(c.robot.with_tote==1 && a.r
		}
	}
	if(c.tote_location==a.tote_location){
		if(c.robot.with_tote==1 && a.robot.with_tote==0 && b.robot.with_tote==1) return 1;
		if(c.robot.with_tote==0 && a.robot.with_tote==1 && b.robot.with_tote==0) return 1;
	}
	if(c.robot.location!=a.robot.location){

	}/*
	if(c.robot.with_tote==1 && a.robot.with_tote==0 && b.robot.with_tote==1) return 1;
	if(c.robot.with_tote==0 && a.robot.with_tote==1 && b.robot.with_tote==0) return 1;
	if(c.robot.location.first-a.robot.location.first>c.robot.location.first-b.robot.location.first) return 1;
	if(c.robot.location.second-a.robot.location.second>c.robot.location.second-b.robot.location.second) return 1;*/	
	return 0;
}

int function1(Environment_state c){
	Environment_state a;
	a.robot.location=make_pair(0,0);
	a.tote_location=make_pair(0,0);
	a.robot.with_tote=0;
	Environment_state b=a;
	vector<Action> v;
	int distance=0;
	while(1){
		v=get_possible_moves(a);
		for(unsigned int i=0; i<v.size(); i++){
			b=update_environment(v[i], a);
			if(a==c)break;
			if(closer(a, b, c)){
				distance ++;
				cout<<"NOW: "<<a<<"        "<<v[i]<<"        TARGET: "<<c<<"        "<<distance<<endl;
				a=update_environment(v[i], a);
				break;
			}
		}
		//cout<<"RAN"<<endl;
		if(a==c)break;
	}
	return distance;
}

/*void func_name(vector<Action> a, Environment_state b, Environment_state c, vector<Environment_state> d, int e = 0){
	e++;
	a = get_possible_moves(b);
	if (b==c) {
		cout<<e<<endl;
	} else {	
		for(unsigned int o=0; o<a.size(); o++){
			b=update_environment(a[o], b);
			bool retrace = 0;
			for (unsigned int i=0; i<d.size(); i++) {
				if (b==d[i]) {
					retrace=1;
					break;
				}
			}
			if (b!=c && !retrace && e<10) {
				func_name(a, b, c, d, e);
			} else if (b==c) {
				cout<<e<<endl;
				break;
			}
		}
	}
}*/

int get_distance(Environment_state b, vector<Environment_state> v){
	Environment_state a;
	Environment_state c;
	a.robot.location=make_pair(0,0);
	a.tote_location=make_pair(0,0);
	a.robot.with_tote=0;
	int distance=0;
	//c=a;	
	//vector<Action> steps;
	//vector<Action> possible;
	//vector<Environment_state> k;
	//cout<<"BEGIN - "<<b<<endl;
	//func_name(steps, c, b, k);
	/*for(unsigned int i=0; i<v.size(); i++){
		possible = get_possible_moves(b);	
	}*/
	return distance;
}

void make_graph(){
	ofstream graphy;
	int distance=0;
	Environment_state a, b;
	graphy.open("graphy.dot");
	vector<Environment_state> r;
	vector<Action> v;
	r=states();
	graphy<<"Digraph G{"<<endl;
	for(unsigned int i=0; i<r.size(); i++){
		a=r[i];
		v=get_possible_moves(a);
		distance=function1(b);
		for(unsigned int o=0; o<v.size(); o++){
			b=update_environment(v[o], r[i]);
			//cout<<"NOW: "<<a<<"        "<<v[o]<<"        NEXT: "<<b<<"        "<<distance<<endl;
			if(a.robot.location==make_pair(0,0) && a.tote_location==make_pair(0,0) && a.robot.with_tote==0){
				graphy<<"        \""<<a<<"\"[color=\"red\"];"<<endl<<"        \""<<a<<"\"->\""<<b<<"\"[label=\""<<v[o]<<"\"];"<<endl;
			}
			else graphy<<"        \""<<a<<"\"[color=\"orange\"];"<<endl<<"        \""<<a<<"\"->\""<<b<<"\"[label=\""<<v[o]<<"\"];"<<endl;
					
		}
	}
	graphy<<"}";
	graphy.close();
}

int main(){
	Environment_state environment;
	environment.robot.location.first=0;//randomize_environment();
	environment.robot.location.second=0;//randomize_environment();
	environment.tote_location.first=1;//randomize_environment();
	environment.tote_location.second=1;//randomize_environment();
	make_graph();
	vector<Action> instructions=get_instructions(environment);
	for(unsigned int i=0; i<instructions.size(); i++){//Runs instructions
		environment=update_environment(instructions[i], environment);
		cout<<instructions[i]<<"   "<<environment<<endl;
	}
	return 0;
}
