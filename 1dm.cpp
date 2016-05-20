#include <stdlib.h>
#include<iostream>
using namespace std;
int main(){
	int y; 
	int x;
	cout<<"Hello. Where are you now?\n";
	int i=0;
	while(i<6){
		cout<<i<<"\n";
		i++;
	}
	string currentlocation;
	getline(cin,currentlocation);
	y=atoi(currentlocation.c_str());
	cout<<"Where would you like to go?\n";
	int f=0;
	while(f<6){
		cout<<f<<"\n";
		f++;
	}
	string destination;
	getline(cin,destination);
	x=atoi(destination.c_str());
	if(y==4){
		if(x==0){
			cout<<"Go left four spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==1){
			cout<<"Go left three spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==2){
			cout<<"Go left two spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==3){
			cout<<"Go left one space.\n";
			cout<<"You're welcome.\n";
		}
		if(x==4){
			cout<<"You are already there.\n";
			cout<<"You're welcome.\n";
			}
		if(x==5){
			cout<<"Go right one space.\n";
			cout<<"You're welcome.\n";
		}
	}
	if(y==5){
		if(x==0){
			cout<<"Go left five spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==1){
			cout<<"Go left four spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==2){
			cout<<"Go left three spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==3){
			cout<<"Go left two space.\n";
			cout<<"You're welcome.\n";
		}
		if(x==4){
			cout<<"Go left one space.\n";
			cout<<"You're welcome.\n";
			}
		if(x==5){
			cout<<"You are already there.\n";
			cout<<"You're welcome.\n";
		}
	}
	if(y==3){
		if(x==0){
			cout<<"Go left three spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==1){
			cout<<"Go left two spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==2){
			cout<<"Go left one space.\n";
			cout<<"You're welcome.\n";
		}
		if(x==3){
			cout<<"You are already there.\n";
			cout<<"You're welcome.\n";
		}
		if(x==4){
			cout<<"Go right one space.\n";
			cout<<"You're welcome.\n";
			}
		if(x==5){
			cout<<"Go right two space.\n";
			cout<<"You're welcome.\n";
		}
	}
	if(y==2){
		if(x==0){
			cout<<"Go left two spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==1){
			cout<<"Go left one space.\n";
			cout<<"You're welcome.\n";
		}
		if(x==2){
			cout<<"You are already there.\n";
			cout<<"You're welcome.\n";
		}
		if(x==3){
			cout<<"Go right one space.\n";
			cout<<"You're welcome.\n";
		}
		if(x==4){
			cout<<"Go right two spaces.\n";
			cout<<"You're welcome.\n";
			}
		if(x==5){
			cout<<"Go right three spaces.\n";
			cout<<"You're welcome.\n";
		}
	}
	if(y==1){
		if(x==0){
			cout<<"Go left one space.\n";
			cout<<"You're welcome.\n";
		}
		if(x==1){
			cout<<"You are already there.\n";
			cout<<"You're welcome.\n";
		}
		if(x==2){
			cout<<"Go right one space.\n";
			cout<<"You're welcome.\n";
		}
		if(x==3){
			cout<<"Go right two spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==4){
			cout<<"Go right three spaces.\n";
			cout<<"You're welcome.\n";
			}
		if(x==5){
			cout<<"Go right four spaces.\n";
			cout<<"You're welcome.\n";
		}
	}
	if(y==0){
		if(x==0){
			cout<<"You are already there.\n";
			cout<<"You're welcome.\n";
		}
		if(x==1){
			cout<<"Go right one space.\n";
			cout<<"You're welcome.\n";
		}
		if(x==2){
			cout<<"Go right two spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==3){
			cout<<"Go right three spaces.\n";
			cout<<"You're welcome.\n";
		}
		if(x==4){
			cout<<"Go right four spaces.\n";
			cout<<"You're welcome.\n";
			}
		if(x==5){
			cout<<"Go right five spaces.\n";
			cout<<"You're welcome.\n";
		}
	}
}
