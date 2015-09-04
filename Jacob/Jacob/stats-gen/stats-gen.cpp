#include<stdlib.h>
#include<iostream>

using namespace std;

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

		
	
}
