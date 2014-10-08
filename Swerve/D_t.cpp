#include<iostream>
#include<vector>
#include<math.h>
#include<sstream>

using namespace std;


string f(float f){
	stringstream ss;
	ss<<f;
	return ss.str().substr(0,7);
}


void tableDisplay(){
	int count = 0;
	float time = 0;
	float ldistance = 0;
	float rdistance = 0;
	float stepsize = .25;
	float ltotal = 0;
	float rtotal = 0;
	cout<<"Time"<<"		"<<"LDistance"<<"	"<<"LVelocity"<<"	"<<"LTotal"<<"			"<<"RDistance"<<"	"<<"RVelocity"<<"	"<<"RTotal"<<"\n";
	while(count != 20){
		float lvelocity = sin(time);
		float rvelocity = cos(time);
		ldistance += stepsize *lvelocity;
		rdistance += stepsize * rvelocity;
		ltotal += fabs(stepsize *lvelocity);
		rtotal += fabs(stepsize *rvelocity);
		cout<<f(time)<<"		"<<f(ldistance)<<"		"<<f(lvelocity)<<"		"<<f(ltotal)<<"			"<<f(rdistance)<<"		"<<f(rvelocity)<<"		"<<f(rtotal)<<"\n";
		time=time+stepsize;
		count++;
	}
}


int main(){
	float f;
	tableDisplay();
}