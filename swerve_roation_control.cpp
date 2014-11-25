//Author: Logan Traffas *****Unfinished***** Function: To simulate wheel movement given current and target positions (the current units are radians).
#include <iostream>
#include <cmath>
#include <math.h>

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
		if(radian_change<0){//Negative change
			decimal_difference=target_rotation-current_rotation;//Sets and corrects the difference between current and target rotations for fractional calculation
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
		else if(radian_change>0){//Positive change
			decimal_difference=correct_radian_form(target_rotation-current_rotation);//Sets and corrects the difference between current and target rotations for fractional calculation 
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

void current_rotation_direction(){//Uses the order of channel inputs for pins two (a) and four (b) to determine wheel rotating direction
	char leader; 
	bool rotating_direction;
	cout<<"What is the leading channel? ";
	cin>>leader;
	cout<<endl;
	if(leader=='a')cout<<"Wheel currently rotating clockwise."<<endl;
	else if(leader=='b')cout<<"Wheel currently rotating counter-clockwise."<<endl;
	cout<<endl;
}

int main(){
	current_rotation_direction();
	double current_rotation, target_rotation, radian_change, decimal_difference;
	cout<<"What is the current wheel rotation? ";//Prompts the user for current wheel rotation
	cin>>current_rotation;
	current_rotation=correct_radian_form(current_rotation);
	cout<<"What is the target wheel rotation? ";//Prompts the user for current wheel rotation
	cin>>target_rotation;
	cout<<endl;
	target_rotation=correct_radian_form(target_rotation);
	radian_change=determine_change(current_rotation, target_rotation);
	current_rotation=simulation(current_rotation, target_rotation, radian_change);//Returns current_rotation after simulation
	return 0;
}