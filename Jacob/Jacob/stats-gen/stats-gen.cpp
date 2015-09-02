#include<iostream>

using namespace std;

int main(){
	int robot_travel_speed;
	int robot_rotation_speed;
	int pickup_speed;
	int pass_speed;
	int reload_time;
	int accuracy;
	int field_length = 54;
	cout<<"\n\nTravel speed (ft/sec): ";
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
	
	
	
}
