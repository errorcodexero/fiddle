//Author(s): Logan Traffas, Matthew Macovsky
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

const int X_LIMIT=3;//The limits for the field
const int Y_LIMIT=3;

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

ostream & operator<<(ostream & o, Location location){//Sets how type "Location" prints
	o<<"("<<location.first<<","<<location.second<<")";
	return o;
}

ostream & operator<<(ostream & o, Environment_state in){//How to print type Environment_state
	o<<"Robot location: "<<in.robot.location<<"   Tote location: "<<in.tote_location<<"   Robot with tote: "<<in.robot.with_tote;
	return o;
}

template<typename T>
ostream & operator<<(ostream & o, vector<T> in){//How to print type vector<type>
	o<<"[";
	for(unsigned int i=0; i<in.size(); i++){
		o<<in[i];
	}
	o<<"]";
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
		assert(environment.robot.location.first>0);
		environment.robot.location.first--;
	}
	if(instruction==Action::RIGHT){
		assert(environment.robot.location.first+1<X_LIMIT);
		environment.robot.location.first++;
	}
	if(instruction==Action::BACKWARD){
		assert(environment.robot.location.second>0);
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

vector<Action> get_possible_moves(Environment_state environment){//Determines how to print the types of "Action"
	vector<Action> possible_moves;
	if(environment.robot.location.first>0){
		possible_moves.push_back(Action::LEFT);
	}
	if(environment.robot.location.first+1<X_LIMIT){
		possible_moves.push_back(Action::RIGHT);
	}
	if(environment.robot.location.second>0){
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

bool operator==(Environment_state::Robot_state a, Environment_state::Robot_state b){//Sets the operator "==" for Robot_state
	return a.location==b.location && a.with_tote==b.with_tote;
}

bool operator==(Environment_state a, Environment_state b){//Sets the operator "==" for Environment_state
	return a.robot==b.robot && a.tote_location==b.tote_location;
}

bool operator!=(Environment_state a, Environment_state b){//Sets the operator "!=" for Environment_state
	return !(a==b);
}

vector<vector<Action>> find_available_moves(int x){//Finds all the possible instructions of length "x"
	vector<vector<Action>> v;
	vector<Action> c;
	c.push_back(Action::FORWARD);
	c.push_back(Action::BACKWARD);
	c.push_back(Action::RIGHT);
	c.push_back(Action::LEFT);
	c.push_back(Action::LIFT);
	c.push_back(Action::DROP);
	if(x==0) return v;
	else if(x==1){
		for(Action move1:c){
			vector<Action> b;
			b.push_back(move1);
			v.push_back(b);
		}
		return v;
	}
	else if(x==2){
		for(Action move1:c){
			for(Action move2:c){
				vector<Action> b;
				b.push_back(move1);
				b.push_back(move2);
				v.push_back(b);
			}
		}
		return v;
	}
	else if(x==3){
		for(Action move1:c){
			for(Action move2:c){
				for(Action move3:c){
					vector<Action> b;
					b.push_back(move1);
					b.push_back(move2);
					b.push_back(move3);
					v.push_back(b);
				}
			}
		}
		return v;
	}
	else if(x==4){
		for(Action move1:c){
			for(Action move2:c){
				for(Action move3:c){
					for(Action move4:c){
						vector<Action> b;
						b.push_back(move1);
						b.push_back(move2);
						b.push_back(move3);
						b.push_back(move4);
						v.push_back(b);
					}
				}
			}
		}
		return v;
	}
	else if(x==5){
		for(Action move1:c){
			for(Action move2:c){
				for(Action move3:c){
					for(Action move4:c){
						for(Action move5:c){
							vector<Action> b;
							b.push_back(move1);
							b.push_back(move2);
							b.push_back(move3);
							b.push_back(move4);
							b.push_back(move5);
							v.push_back(b);
						}
					}
				}
			}
		}
		return v;
	}
	cout<<"Not Done";
	exit(1);
}

pair<bool, Environment_state> determine_possible(Environment_state e, vector<Action> a){//Determines if a set of instructions can be carried out given an environment
	pair<bool, Environment_state> c;
	for (unsigned int i=0; i<a.size(); i++){
		if (i!=0) e=update_environment(a[i-1], e);
		vector<Action> b=get_possible_moves(e);
		for (unsigned int k=0; k<b.size(); k++) {
			if (b[k]==a[i]) {
				break;
			} else if (k==(b.size()-1)) {
				c.first= 0;
				c.second=e;
				return c;
			}
		}
	}
	e=update_environment(a[a.size()-1], e);
	c.first=1;
	c.second=e;
	return c;
}

bool reached_target(Environment_state a, Environment_state b, vector<Action> v){//Determines if a set of instructions will take a starting robot to a target
	pair<bool, Environment_state> c = determine_possible(a, v);
	return c.first && c.second==b;
}

void print_results(){//Prints the results from find_available_moves()
	for(unsigned int i=0; i<5; i++){
		vector<vector<Action>> v;
		v=find_available_moves(i);
		for(unsigned int o=0; o<v.size(); o++){
			cout<<v[o]<<endl;
		}
	}
}

vector<Action> get_instructions(Environment_state a, Environment_state b){//Gets instructions from a starting environment and a target
	vector<vector<Action>> v;
	bool target_reached=0;
	vector<Action> instructions;
	for(unsigned int i=0; i<6; i++){
		if(target_reached==1)break;
		v=find_available_moves(i);
		if(i!=0){
			for(unsigned int k; k<v.size(); k++){
				if(reached_target(a,b,v[k])){
					cout<<"BEGIN: "<<a<<endl<<"TARGET: "<<b<<endl<<"COMPLETED: "<<v[k];
					instructions=v[k];
					target_reached=1;
					break;
				}
			}
		}
	}
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
		for(unsigned int o=0; o<v.size(); o++){
			b=update_environment(v[o], r[i]);
			//distance=find_distance(a);
			if(distance==0)color="#FF0000";
			else if(distance==1)color="#FF2A00";
			else if(distance==2)color="#FF4D00";
			else if(distance==3)color="#FF8000";
			else if(distance==4)color="#FFA200";
			else if(distance==5)color="#FFD000";
			else if(distance==6)color="#FFFF00";
			else color="#0004FF";
			graphy<<"        \""<<a<<"  Dist: "<<distance<<"\"[color=\""<<color<<"\"];"<<endl<<"        \""<<a<<"  Dist: "<<distance<<"\"->\""<<b<<"  Dist: "<<distance+1<<"\"[label=\""<<v[o]<<"\"];"<<endl;
		}
	}
	graphy<<"}";
	graphy.close();
}

int main(){//Main, if you don't know what this is, then you shouldn't be looking at this code
	Environment_state a,b;
	a.robot.location=make_pair(0,0);
	a.tote_location=make_pair(0,0);
	a.robot.with_tote=1;
	b.robot.location=make_pair(2,2);
	b.tote_location=make_pair(2,2);
	b.robot.with_tote=1;
	get_instructions(a,b);
	return 0;
}