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

void readValues(float &tochange, int type){
	string line;
	int linei;
	float linef;
	ifstream myfile ("stats-gen-savefile.txt");
	if(myfile.is_open()){
		for(int i = 0; i < type; i++){
					getline(myfile, line);
		}
		myfile.close();
	} else {
		cout<<"stats-gen-savefile.txt not open!";
	}
	
	linei = atoi(line.c_str());
	linef = (float)linei;
	tochange = linef;
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
			readValues(robot_travel_speed, type);
			readValues(robot_rotation_speed, type);
			readValues(pickup_speed, type);
			readValues(pass_speed, type);
			readValues(reload_time, type);
			readValues(accuracy, type);
			readValues(field_length, type);
			readValues(field_width, type);
		}
	} else {
		cout<<"Error: savefile doesn't exist!";
		cout<<"\n\nFixing: 
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}
