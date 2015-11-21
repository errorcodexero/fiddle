#include<stdlib.h>
#include<fstream>
#include<iostream>

using namespace std;

void userMenuString(int cpu_count){
	//cpu_count is the requested terminal output
	switch (cpu_count) {
		case 0:
			//Start menu
			cout<< string(50, '\n');
			cout<<"Menu:\n";
			cout<<"1) Statistical analysis calculator\n";
			//cout<<"2) Statistical team ranking\n;
			//cout<<"3) Single team statistics\n";
			//cout<<"4) Options\n";
			cout<<"5) Exit\n";
			break;
		case 1:
			//Statistical analysis calculator menu
			cout<< string(50, '\n');
			cout<<"Statistical analysis calculator:\n";
			cout<<"1) Initiate\n";
			cout<<"2) Return to menu\n";
			break;
		case 2:
			//Statistical team ranking list
			cout<< string(50, '\n');
			cout<<"Statisitical team ranking:\n\n";
			break;
		case 3:
			//Single team statistics
			cout<< string(50, '\n');
			cout<<"Single team statistics:\n";
			cout<<"Enter nothing to return to menu\n"; 
			cout<<"Enter team number: ";
			break;
		case 4:
			//Options
			cout<< string(50, '\n');
			cout<<"Options:\n";
			cout<<"1) Change field dimensions\n";
			cout<<"2) Change team settings\n";
			cout<<"3) Return to menu\n";
			break;
		case 5:
			//Options->Change team settings
			cout<< string(50, '\n');
			cout<<"Change team settings:\n";
			cout<<"Enter nothing to return to menu\n";
			cout<<"Enter team number: \n";
			break;
		default:
			cout<<"\n\nError: No output requested!";
			cout<<"\nRequest number: "<<cpu_count;
			exit(2);
			break;
	}
}

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

void statisticalCalculator(float& robot_travel_speed, float& robot_rotation_speed, float& pickup_speed, float& pass_speed, float& reload_time, float& accuracy, float& field_length, float& field_width, int& type, int& cpu_count){
	
	
}


void userMenu(){
	
	int input;
	
	Start:
		userMenuString(0);
		cout<<"\n>";
		cin>>input;
		switch (input) {
			case 1:
				goto SAC_menu; //Statistical Analysis Calculator
				break;
			/*case 2:
				goto STR; //Statistical Team Ranking
				break;
			case 3:
				goto STS; //Single team statistics
				break;
			case 4:
				goto OPT; //Options
				break;*/
			default:
				exit(0);
				break;
		}

	SAC_menu:
		userMenuString(1);
		cout<<"\n>";
		cin>>input;
		switch (input) {
			case 1:
				//SAC_calculator();
				cout<<"Works\n\n";
				exit(0);
				break;
			case 2:
				goto Start;
				break;
			default:
				exit(3);
				break;
		}

	STR:
		userMenuString(2);
		cout<<"\n";
		cout<<"Works";
		exit(0);

//	STS:
//		userMenuString(3);
}

/*float readSaveFile(int ){
	ifstream savefile("stats-gen-savefile.txt");
	
}*/

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
	int cpu_count = 0; //used to determine what to print to the console.
	
	userMenu(robot_travel_speed, robot_rotation_speed, pickup_speed, pass_speed, reload_time, accuracy, field_length, field_width, type, cpu_count);
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	/*
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
		cout<<"\nFixing...";

	}
	*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
}