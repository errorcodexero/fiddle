//Author: Logan Traffas
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <string>
#include <utility>
#include <fstream>
#include <assert.h>

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

typedef pair<int, int> Location;

struct Environment_state{//Type to store the states of the environment
	struct Robot_state{//Type to store the current states of the robot
		Location location;
		bool with_tote;
		Robot_state():with_tote(0){}
	};
	Robot_state robot;
	Location tote_location;
};

ostream & operator<<(ostream & o, Location location){
	o<<"("<<location.first<<","<<location.second<<")";
	return o;
}

ostream & operator<<(ostream & o, Environment_state in){//How to print type Environment_state
	o<<"Robot location: "<<in.robot.location<<"   Tote location: "<<in.tote_location<<"   Robot with tote: "<<in.robot.with_tote;
	return o;
}

template<typename T>
ostream & operator<<(ostream & o, vector<T> in){//How to print type vector<type>
	for(unsigned int i=0; i<in.size(); i++){
		o<<in[i];
	}
	return o;
}

bool operator==(pair<int, int> a, pair<int, int> b) {//Sets operator "==" for pairs
	return a.first==b.first && a.second==b.second;
}

bool operator!=(pair<int, int> a, pair<int, int> b) {//Sets operator "!=" for pairs
	return !(a==b);
}

Environment_state update_environment(Action instruction, Environment_state environment){//Determines what the robot does with a give instruction
	if(instruction==Action::LEFT){
		assert(environment.robot.location.first-1>0);
		environment.robot.location.first--;
	}
	if(instruction==Action::RIGHT){
		assert(environment.robot.location.first+1<X_LIMIT);
		environment.robot.location.first++;
	}
	if(instruction==Action::BACKWARD){
		assert(environment.robot.location.second-1>0);
		environment.robot.location.second--;
	}
	if(instruction==Action::FORWARD){
		assert(environment.robot.location.second+1<Y_LIMIT);
		environment.robot.location.second++;
	}
	if(instruction==Action::LIFT){
		assert(environment.robot.location==environment.tote_location);
		assert(environment.robot.with_tote==0);
		environment.robot.with_tote=1;
	}
	if(instruction==Action::DROP){
		assert(environment.robot.with_tote==1);
		environment.robot.with_tote=0;
	}
	if(environment.robot.with_tote==1)environment.tote_location=environment.robot.location;
	return environment;
}

/*int randomize_environment(){//Returns a random number
	srand(time(NULL));
	int random=rand()%2;
	return random;
}*/

vector<Action> get_possible_moves(Environment_state environment){//Determines how to print the types of "Action"
	vector<Action> possible_moves;
	if(environment.robot.location.first-1>0){
		possible_moves.push_back(Action::LEFT);
	}
	if(environment.robot.location.first+1<X_LIMIT){
		possible_moves.push_back(Action::RIGHT);
	}
	if(environment.robot.location.second-1>0){
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

vector<Environment_state> states(){//Makes a vector of all possible environments
	Environment_state environment;
	environment.robot.with_tote=0;
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

bool operator==(Robot a, Robot b){
	return a.location==b.location && a.with_tote==b.with_tote;
}

bool operator==(Environment_state a, Environment_state b){//Sets the operator "==" for Environment_state
	return a.robot==b.robot && a.tote_location==b.tote_location;
}

bool operator!=(Environment_state a, Environment_state b){//Sets the operator "!=" for Environment_state
	return !(a==b);
}

double distance_formula(pair<int, int> a, pair<int, int> b){//Finds the distance between two points
	double distance=0;
	distance=sqrt(pow(a.first-b.first, 2)+pow(a.second-b.second, 2));
	return distance;
}

bool closer(Environment_state a, Environment_state b, Environment_state c){//Determines if a specific move will move the robot closer to the target
	if(a.tote_location!=c.tote_location){
		if(a.tote_location!=a.robot.location) {
			return (distance_formula(a.robot.location, a.tote_location)>distance_formula(b.robot.location, b.tote_location));
		} else{
			if(a.robot.with_tote==0 && b.robot.with_tote==1){
				return 1;
			} else{
				return (distance_formula(c.tote_location, a.robot.location)>distance_formula(c.tote_location, b.tote_location));
			}
		}
	} else{
		if(a.robot.with_tote==0 && b.robot.with_tote==1){
			return 1;
		}
		if(a.tote_location==c.tote_location && a.robot.with_tote==1 && c.robot.with_tote==0){
			return !(b.robot.with_tote);
		}
		if(a.robot.location!=c.robot.location){
			return (distance_formula(c.robot.location, a.robot.location)>distance_formula(c.robot.location, b.robot.location));
		}
	}
	return 0;
}

int find_distance(Environment_state c){//Determines the number of moves needed between two environments
	Environment_state a;
	a.robot.location=make_pair(0,0);
	a.tote_location=make_pair(0,0);
	a.robot.with_tote=0;
	Environment_state b=a;
	vector<Action> v;
	int distance=0;
	//cout<<endl<<"TARGET: "<<c<<endl<<endl;
	while(1){
		if(a==c)break;
		v=get_possible_moves(a);
		for(unsigned int i=0; i<v.size(); i++){
			b=update_environment(v[i], a);
			if(a==c) break;
			if(closer(a, b, c)){
				distance++;
				//cout<<"NOW: "<<a<<"    "<<v[i]<<"    OPTION: "<<b<<"    DISTANCE: "<<distance<<endl<<endl;
				a=update_environment(v[i], a);
				break;
			}
		}
		if(a==c)break;
	}
	//if(a==c) cout<<"TARGET REACHED"<<endl<<endl;
	return distance;
}

vector<Action> get_instructions(Environment_state environment){//Gets instructions from a random starting environment
	vector<Action> instructions;
	return instructions;
}

void make_graph(){//Makes a graphviz graph
	string color;
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
		cout<<a<<"  | "<<v<<endl;
		for(unsigned int o=0; o<v.size(); o++){
			b=update_environment(v[o], r[i]);
			distance=find_distance(a);
			if(distance==0)color="#FF0000";
			else if(distance==1)color="#FF2A00";
			else if(distance==2)color="#FF4D00";
			else if(distance==3)color="#FF8000";
			else if(distance==4)color="#FFA200";
			else if(distance==5)color="#FFD000";
			else if(distance==6)color="#FFFF00";
			else color="#0004FF";
			graphy<<"        \""<<a<<"  Dist: "<<distance<<"\"[color=\""<<color<<"\"];"<<endl<<"        \""<<a<<"  Dist: "<<distance<<"\"->\""<<b<<"  Dist: "<<find_distance(b)<<"\"[label=\""<<v[o]<<"\"];"<<endl;
		}
	}
	graphy<<"}";
	graphy.close();
}

int main(){
	/*Environment_state environment;
	environment.robot.location.first=0;//randomize_environment();
	environment.robot.location.second=0;//randomize_environment();
	environment.tote_location.first=1;//randomize_environment();
	environment.tote_location.second=1;//randomize_environment();*/
	make_graph();
	/*vector<Action> instructions=get_instructions(environment);
	for(unsigned int i=0; i<instructions.size(); i++){//Runs instructions
		environment=update_environment(instructions[i], environment);
		cout<<instructions[i]<<"   "<<environment<<endl;
	}*/
	return 0;
}
