#include<iostream>
#include<assert.h>
#include<vector>

using namespace std;

struct Joystick{
	float j1x;
	float j1y;
	float j2x;
	float j2y;
};


float override_right(float turn, float j2y){	
	if(turn > 0){
		if(j2y <= 0){
			return j2y - turn;
		}
		if(j2y > 0){
			return j2y;
		}
	} 
	if(turn <= 0){
		return j2y;
	}
	assert(false);
}

float override_left(float turn, float j1y){
	if(turn < 0){
		if(j1y >= 0){
			return j1y - turn;
		}
		if(j1y < 0){

			return j1y;
		}
	} 
	if(turn >= 0){
		return j1y;
	}
	assert(false);
}
int main(){
	Joystick joy;
	joy.j1x = 0; 
	joy.j1y = 0; //Out puts between 1 & -1 for left track
	joy.j2x = 0; 
	joy.j2y = 0; //Out puts between 1 & -1 for right track
	vector<Joystick> v;
	v.push_back(joy);
	joy.j1x = 0;
	joy.j1y = 1;
	joy.j2x = 0; 
	joy.j2y = 1;
	v.push_back(joy);
	joy.j1x = 0;
	joy.j1y = -1;
	joy.j2x = 0; 
	joy.j2y = -1;
	v.push_back(joy);
	joy.j1x = -1;
	joy.j1y = 0;
	joy.j2x = -1; 
	joy.j2y = 0;
	v.push_back(joy);
	joy.j1x = 1;
	joy.j1y = 0;
	joy.j2x = 1; 
	joy.j2y = 0;
	v.push_back(joy);


	cout<<"\n\nJ1x	J1y	J2x	J2y	Left		Right";
	int count=v.size();
	int count2 = 0;
	while(count != 0){
		
		float turn = (v[count2].j1x + v[count2].j2x)/2; //Amount of power that overrides the track powers
		float left_track_out = override_left(turn, v[count2].j1y);
		float right_track_out = override_right(turn, v[count2].j2y);
		
		
		cout<<"\n"<<v[count2].j1x<<"	"<<v[count2].j1y<<"	"<<v[count2].j2x<<"	"<<v[count2].j2y<<"	"<<left_track_out<<"		"<<right_track_out;
		count--;
		count2++;
	}
	cout<<"\n\n";














}
