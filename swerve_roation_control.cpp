//Author: Logan Traffas *****Unfinished***** Function: To simulate wheel movement given current and target positions (the current units are radians).
#include <iostream>
#include <cmath>
#include <math.h>

using namespace std;

double correct_input_form(double input){//Corrects user input to radian form (i.e. 0-(2*pi))
	while(input<0){
		input+=(2*M_PI);
	}
	while(input>(2*M_PI)){
		input-=(2*M_PI);
	}
	return input;
}

double determine_change(double current_rotation, double target_rotation){//Determine the amount of radians needed to change
	if(target_rotation-current_rotation==0 || target_rotation-current_rotation==(2*M_PI)){//Calculates the direction and magnitude of radian change
		return 0;
	}
	else if(current_rotation==-M_PI){//Corrects for preferred direction when direction and magnitude are equal
		return M_PI;
	}
	else if(target_rotation-current_rotation<=M_PI && target_rotation-current_rotation>-M_PI){
		return (target_rotation-current_rotation);
	}
	else if(target_rotation-current_rotation>M_PI){
		return ((target_rotation-current_rotation)-(2*M_PI));
	}
	else if(target_rotation-current_rotation<-M_PI){
		return ((target_rotation-current_rotation)+(2*M_PI));
	}
}

double correct_rotating_form(double current_rotation){//During wheel turn, this will correct to radian form (i.e. 0-(2*pi))
	if(current_rotation<0){//Changes negative values into the correct form
		current_rotation+=(2*M_PI);
	}
	else if(current_rotation>(2*M_PI)){//Changes numbers greater than (2*M_PI) radians into the correct form
		current_rotation-=(2*M_PI);
	}
	else if(current_rotation==(2*M_PI) || current_rotation==-(2*M_PI)){//Changes numbers at (2*M_PI) radians into the correct form
		current_rotation=0;
	}
	return current_rotation;
}

int main(){
	double current_rotation;//Variable for the current wheel rotation
	double target_rotation;//Variable for the target wheel rotation
	double radian_change;//Variable for the amount of radians needed to change
	cout<<"What is the current wheel rotation? ";//Prompts the user for current wheel rotation
	cin>>current_rotation;
	current_rotation=correct_input_form(current_rotation);
	cout<<endl<<"What is the target wheel rotation? ";//Prompts the user for current wheel rotation
	cin>>target_rotation;
	cout<<endl;
	target_rotation=correct_input_form(target_rotation);
	radian_change=determine_change(current_rotation, target_rotation);
	for(int i=-1;i<abs(radian_change);i++){//Simulates the wheel rotation
		if(i==-1)i++;
		if(i==0)cout<<"At "<<current_rotation<<" radians."<<endl;//Prints the starting rotation
		if(radian_change<0){
			if(current_rotation-target_rotation>0 && current_rotation-target_rotation<1){//Changes wheel rotation for cases when the difference is less than one radian.
				current_rotation=target_rotation;
				cout<<"At "<<current_rotation<<" radians."<<endl;
				break;
			}
			current_rotation--;
			current_rotation=correct_rotating_form(current_rotation);
			cout<<"At "<<current_rotation<<" radians."<<endl;
		}
		else if(radian_change>0){
			if(current_rotation-target_rotation>-1 && current_rotation-target_rotation<0){//Changes wheel rotation for cases when the difference is less than one radian.
				current_rotation=target_rotation;
				cout<<"At "<<current_rotation<<" radians."<<endl;
				break;
			}
			current_rotation++;
			current_rotation=correct_rotating_form(current_rotation);
			cout<<"At "<<current_rotation<<" radians."<<endl;
		}
	}
	return 0;
}