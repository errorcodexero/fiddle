#include<stdlib.h>
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
			cout<<"Error: ln 32, Switch case failure!
			exit(33);
			break;
	}
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
	
/*
float find_lengths_per_game(float robot_travel_speed, float field_length){
	float answer;
	
	return answer;
}

int main(){
	float robot_travel_speed;
	float robot_rotation_speed;
	float pickup_speed;
	float pass_speed;
	float reload_time;
	float accuracy;
	float field_length;
	float field_width;
	float total_game_time;
	float auto_game_time;

	string answer;
	
	field_length = 54;
	field_width = 0;
	//-----START-----
	
	system("clear");
	cout<<"Current built-in settings: \n";
	cout<<"   Field length (ft): "<<field_length;
	cout<<"\n   Field width (ft): "<<field_width;
	cout<<"\n\nDo you want to use built-in settings? (y/n): ";
	cin>>answer;
	cout<<"\n----------------------------------------------\n\n";
	cout<<"Please fill in the following: \n\n";
	
	if(answer == "n"){
		cout<<"\nField length (ft): ";
		cin>>field_length;
		cout<<"\nField width (ft): ";
		cin>>field_width;
		cout<<"\nTotal game time (sec. only): ";
		cin>>total_game_time;
		cout<<"\nAutonomus game time (sec. only): ;
		cin>>
	} else if(answer != "y"){
		cout<<"\n\nError: 'y' or 'n' not selected.\n\n";
		exit(1);
	}
	cout<<"\nTravel speed (ft/sec): ";
	cin>>robot_travel_speed;
	cout<<"\nRotation speed (rpm): ";
	cin>>robot_rotation_speed;
	cout<<"\nCollection speed (ground->robot): ";
	cin>>pickup_speed;
	cout<<"\nPass_speed (estimated ball transfer time): ";
	cin>>pass_speed;
	cout<<"\nReload_time (optional, collected->read to fire): ";
	cin>>reload_time;
	cout<<"\nAccuracy (%): ";
	cin>>accuracy;

	//find_lengths_per_game(robot_travel_speed, field_length);

		
>>>>>>> 03baf4f24f248913cdf042eccbb80a14253d4828
*/	
}
