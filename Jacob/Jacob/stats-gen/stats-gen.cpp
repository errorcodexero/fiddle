#include<stdlib.h>

#include<fstream>
#include<iostream>

using namespace std;

void findInfo(float x, int type){
	switch (type) {
		case 1:
			cout<<"Travel speed (ft/sec): ";
			cin>>x;
			break;
		case 2:
			cout<<"Rotation speed (rpm): ";
			cin>>x;
			break;
		case 3:
			cout<<"Collection speed (ground->robot): ";
			cin>>x;		
			break;
		case 4:
			cout<<"Pass_speed (estimated ball transfer time): ";
			cin>>x;
			break;
		case 5:
			cout<<"Reload_time (optional, collected->read to fire): ";
			cin>>x;
			break;
		case 6:
			cout<<"Accuracy (%): ";
			cin>>x;
			break;
		case 7:
			cout<<"Field Length (ft): ";
			cin>>x;
			break;
		case 8:
			cout<<"Field Width (ft): ";
			cin>>x;
			break;
		default:
			cout<<"Error: ln 32, Switch case failure!";
			exit(1);
			break;
	}
}

float readSaveFile(int ){
	ifstream savefile("stats-gen-savefile.txt");
	
}

int main(){
	//Can be used as first arg in findInfo()
	float robot_travel_speed = 0; //type 1
	float robot_rotation_speed = 0; //type 2
	float pickup_speed = 0; //type 3
	float pass_speed = 0; //type 4
	float reload_time = 0; //type 5
	float accuracy = 0; //type 6
	float field_length = 0; //type 7  //54'
	float field_width = 0; //type 8  //?'
	
	int type; //used as second arg in findInfo()
	
	ifstream checkfile ("stats-gen-savefile.txt");
	if(checkfile.is_open()){
		for(type = 1; type < 8; type++){
			robot_travel_speed = changeValuesFromSaveFile(type);
			robot_rotation_speed = changeValuesFromSaveFile(type);
			pickup_speed = changeValuesFromSaveFile(type);
			pass_speed = changeValuesFromSaveFile(type);
			reload_time = changeValuesFromSaveFile(type);
			accuracy = changeValuesFromSaveFile(type);
			field_length = changeValuesFromSaveFile(type);
			field_width = changeValuesFromSaveFile(type);
		}
	} else {
		cout<<"Error: savefile doesn't exist!";
		cout<<"\n\nFixing: 
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
