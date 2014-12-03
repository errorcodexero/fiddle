//Author: Logan Traffas *****Unfinished***** Function: To simulate wheel movement given current and target positions (the current units are radians).
#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>

#ifndef M_PI//Defines a variable for pi if the variable does not exist
#define M_PI 3.141592653589793238462643383
#endif

using namespace std;

double correct_radian_form(double input){//Corrects to the correct radian form (i.e. 0-(2*pi))
	while(input<0)input+=(2*M_PI);
	while(input>(2*M_PI))input-=(2*M_PI);
	return input;
}

double determine_change(double current_rotation, double target_rotation){//Determine the amount of radians needed to change
	if(target_rotation-current_rotation==0 || target_rotation-current_rotation==(2*M_PI))return 0;//Calculates the direction and magnitude of radian change
	else if(current_rotation==-M_PI)return M_PI;//Corrects for preferred direction when direction and magnitude are equal
	else if(target_rotation-current_rotation<=M_PI && target_rotation-current_rotation>-M_PI)return (target_rotation-current_rotation);//Determine the amount of radians needed to change
	else if(target_rotation-current_rotation>M_PI)return ((target_rotation-current_rotation)-(2*M_PI));//Determine the amount of radians needed to change
	else if(target_rotation-current_rotation<-M_PI)return ((target_rotation-current_rotation)+(2*M_PI));//Determine the amount of radians needed to change
	else{
		cout<<endl<<"ERROR IN DETERMINING CHANGE."<<endl;
		return 0;
	}
}

double correct_rotating_form(double current_rotation){//During wheel turn, this will correct to radian form (i.e. 0-(2*pi))
	if(current_rotation<0)current_rotation+=(2*M_PI);//Changes negative values into the correct form
	else if(current_rotation>(2*M_PI))current_rotation-=(2*M_PI);//Changes numbers greater than (2*M_PI) radians into the correct form
	else if(current_rotation==(2*M_PI) || current_rotation==-(2*M_PI))current_rotation=0;//Changes numbers at (2*M_PI) radians into the correct form
	return current_rotation;
}

double simulation(double current_rotation, double target_rotation, double radian_change){//Simulates wheel rotation
	double decimal_difference;
	for(int i=-1;i<abs(radian_change);i++){//Simulates the wheel rotation
		if(i==-1)i++;
		if(i==0)cout<<"At "<<current_rotation<<" radians."<<endl;//Prints the starting rotation
		if(radian_change<0){//Simulates negative change
			decimal_difference=target_rotation-current_rotation;//Sets and corrects the difference of current and target rotations for fractional calculation
			if(decimal_difference>M_PI)decimal_difference=target_rotation-current_rotation-(2*M_PI);//Ensures it will calculate in the right direction
			if(decimal_difference>-1 && decimal_difference<0){//Changes wheel rotation for cases when the difference is less than one radian.
				current_rotation=target_rotation;
				cout<<"At "<<current_rotation<<" radians."<<endl;
				return current_rotation;
			}
			current_rotation--;
			current_rotation=correct_rotating_form(current_rotation);
			cout<<"At "<<current_rotation<<" radians."<<endl;
		}
		else if(radian_change>0){//Simulates positive change
			decimal_difference=correct_radian_form(target_rotation-current_rotation);//Sets and corrects the difference of current and target rotations for fractional calculation 
			if(decimal_difference>0 && decimal_difference<1){//Changes wheel rotation for cases when the difference is less than one radian.
				current_rotation=target_rotation;
				cout<<"At "<<current_rotation<<" radians."<<endl;
				return current_rotation;
			}
			current_rotation++;
			current_rotation=correct_rotating_form(current_rotation);
			cout<<"At "<<current_rotation<<" radians."<<endl;
		}
	}
	return current_rotation;
}

struct Input{//This is a type for the input received from the encoder -- "a" (pin two) and "b" (pin four)
	bool a,b;
};

ostream & operator<<(ostream & o, Input in){//Outputs from the vector if type Input the states of the a and b channels as this code interprets it
	o<<in.a<<" | "<<in.b;
	return o;
}

void current_rotation_direction(){//Uses the order of channel outputs for pins two (a) and four (b) to determine wheel rotating direction and estimates the amount of rotational change
	double estimated_rotation=0;
	cout<<"time | a | b | estimated rotation"<<endl;
	vector<Input> time;
	Input channel_value;//The following are example values received from the encoder for the purpose of simulation.
	channel_value.a=0;
	channel_value.b=0;//t=0
	time.push_back(channel_value);
	channel_value.a=1;
	channel_value.b=0;//t=1
	time.push_back(channel_value);
	channel_value.a=1;
	channel_value.b=1;//t=2
	time.push_back(channel_value);
	channel_value.a=0;
	channel_value.b=1;//t=3
	time.push_back(channel_value);
	channel_value.a=0;
	channel_value.b=0;//t=4
	time.push_back(channel_value);
	channel_value.a=1;
	channel_value.b=0;//t=5
	time.push_back(channel_value);
	channel_value.a=1;
	channel_value.b=1;//t=6
	time.push_back(channel_value);
	channel_value.a=0;
	channel_value.b=1;//t=7
	time.push_back(channel_value);
	channel_value.a=0;
	channel_value.b=0;//t=8
	time.push_back(channel_value);
	channel_value.a=1;
	channel_value.b=0;//t=9
	time.push_back(channel_value);
	for(unsigned int i=0;i<time.size(); i++){//TURNING DOESN'T WORK YET!! FIXING THIS IS TOP PRIORITY!!
		if(time[i].a==time[i].b){
			//Null (i.e it assumes there was no change -- at least, for now... maybe...)
		}
		else if(((time[i].a==1 && time[i].b==0) && (time[i-1].a==0 && time[i-1].b==0)) || ((time[i].a==0 && time[i].b==1) && (time[i-1].a==1 && time[i-1].b==1))){//Determines if wheel is rotating clockwise
			estimated_rotation+=M_PI;
		}
		else if(((time[i].a==0 && time[i].b==1) && (time[i-1].a==0 && time[i-1].b==0)) || ((time[i].a==1 && time[i].b==0) && (time[i-1].a==1 && time[i-1].b==1))){//Determines if wheel is rotating counter-clockwise
			estimated_rotation-=M_PI;
		}
		cout<<"  "<<i<<"  | "<<time[i]<<" | "<<estimated_rotation<<endl;
	}
}

int main(){
	current_rotation_direction();
	/*double current_rotation, target_rotation, radian_change;
	cout<<endl<<"What is the current wheel rotation? ";//Prompts the user for current wheel rotation
	cin>>current_rotation;
	current_rotation=correct_radian_form(current_rotation);
	cout<<"What is the target wheel rotation? ";//Prompts the user for current wheel rotation
	cin>>target_rotation;
	cout<<endl;
	target_rotation=correct_radian_form(target_rotation);
	radian_change=determine_change(current_rotation, target_rotation);
	current_rotation=simulation(current_rotation, target_rotation, radian_change);//Returns current_rotation after simulation*/
	return 0;
}