//Author: Logan Traffas
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

enum class Action{FORWARD, BACKWARD, RIGHT, LEFT, LIFT, DROP};//Types of actions the robot can preform during autonomous

ostream& operator<<(ostream & o, Action in){//How to print the types of instructions
	if(in==Action::FORWARD){
		o<<"Instruction: FORWARD ";
	}
	else if(in==Action::BACKWARD){
		o<<"Instruction: BACKWARD";
	}
	else if(in==Action::RIGHT){
		o<<"Instruction: RIGHT   ";
	}
	else if(in==Action::LEFT){
		o<<"Instruction: LEFT    ";
	}
	else if(in==Action::LIFT){
		o<<"Instruction: LIFT    ";
	}
	else if(in==Action::DROP){
		o<<"Instruction: DROP    ";
	}
	return o;
}

struct Environment_state{//Type to store the states of the environment
	struct Robot_state{//Type to store the current states of the robot
		pair<int, int> location;
		pair<int, int> target;
		bool with_tote;
		vector<Action> instructions;
		Robot_state():with_tote(0){}
	};
	Robot_state robot;
	pair<int, int> tote_location;
};

ostream & operator<<(ostream & o, Environment_state in){//How to print type Environment_state
	o<<"Robot location: ("<<in.robot.location.first<<","<<in.robot.location.second<<")   Robot target: ("<<in.robot.target.first<<","<<in.robot.target.second<<")   Tote location: ("<<in.tote_location.first<<","<<in.tote_location.second<<")   Robot with tote: "<<in.robot.with_tote;
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

/*Environment_state randomize_environment(){//Randomizes the starting environment
	srand(time(NULL));
	int robot_start=rand()%1;
	int tote_start=rand()%1;
	int robot_target=rand()%1;
	Environment_state environment;
	environment.robot.location=robot_start;
	environment.robot.target=robot_target;
	environment.tote_location=tote_start;
	return environment;
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
	if(environment.robot.location.first+1<=2){
		possible_moves.push_back(Action::RIGHT);
	}
	if(environment.robot.location.second-1>=0){
		possible_moves.push_back(Action::BACKWARD);
	}
	if(environment.robot.location.second+1<=2){
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

vector<Action> get_instructions(Environment_state environment){//Gets instructions from a random starting environment
	vector<Action> instructions;
	vector<Action> possible_moves;
	possible_moves=get_possible_moves(environment);
	return instructions;
}

int main(){
	Environment_state environment;
	environment.robot.location.first=0;//randomize_environment();
	environment.robot.location.second=0;//randomize_environment();
	environment.tote_location.first=1;
	environment.tote_location.second=1;
	environment.robot.target.first=1;
	environment.robot.target.second=0;
	cout<<"STARTING:               "<<environment<<endl;//The starting environment conditions
	environment.robot.instructions=get_instructions(environment);
	for(unsigned int i=0; i<environment.robot.instructions.size(); i++){//Runs instructions
		environment=update_environment(environment.robot.instructions[i], environment);
		cout<<environment.robot.instructions[i]<<"   "<<environment<<endl;
	}
	return 0;
}