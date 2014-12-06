#include<iostream>
#include<math.h>

using namespace std;

void tableOne(float rwtheta, float rwspeed, float lwtheta, float lwspeed, float bwtheta, float bwspeed){
	int count = 10;
	cout<<"Table 1 -individual wheel information intake";
	cout<<"\n";
	cout<<"Left Theta"<<"	"<<"Left Speed"<<"	"<<"Right theta"<<"	"<<"Right Speed"<<"	"<<"Back Theta"<<"	"<<"Back Speed";
	cout<<"\n";
	while(count != 0){
		cout<<lwtheta<<"	"<<lwspeed<<"	"<<rwtheta<<"	"<<rwspeed<<"	"<<bwtheta<<"	"<<bwspeed;
		count--;
	}
}

void tableTwo(float rwtheta, float rwspeed, float lwtheta, float lwspeed, float bwtheta, float bwspeed){
	float rmd; //Robot Movement Direction
	float rrs; //Robot Rotation Speed
	float rstd; //Robot 
	float lx = lwspeed*(cos(lwtheta));
	float llx = float pow(float lx, float 2);
	float ly = lwspeed*(sin(lwtheta));
	float rx = rwspeed*(cos(rwtheta));
	float ry = rwspeed*(sin(rwtheta));
	float bx = bwspeed*(cos(bwtheta));
	float by = bwspeed*(sin(bwtheta));
	float ux = sqrt(lx+rx+bx;
	float uy = ly+ry+by;
	float utheta;
	
	
	
	
	cout<<"Table 2 -Robot calculated response";
	cout<<"\n";
	cout<<"Robot's movement direction"<<"	"<<"Robot's rotation speed"<<"	"<<"Robot's speed towards direction";
	cout<<"\n";
	
	
}

void simulator(float rwtheta, float rwspeed, float lwtheta, float lwspeed, float bwtheta, float bwspeed){
	cout<<"\n\n\n";
	cout<<"Robot Simulator -Swerve drive";
	cout<<"\n\n";
	tableOne(rwtheta, rwspeed, lwtheta, lwspeed, bwtheta, bwspeed);
	cout<<"\n\n\n";
	
}


int main(){
	float rwtheta;
	float rwspeed;
	float lwtheta;
	float lwspeed;
	float bwtheta;
	float bwspeed;
	
}