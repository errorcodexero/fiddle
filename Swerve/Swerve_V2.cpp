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
	float bdistance = 0;
	float stepsize = 1; //Time interval
	float ltotal = 0;
	float rtotal = 0;
	float btotal = 0;
	float ltheta = 0; //degree of left wheel
	float rtheta = 0; //degree of right wheel
	float btheta = 0; //degree of back wheel
	float x_coord = 0;
	float y_coord = 0;
	cout<<"Time"<</*"		"<<"LDistance"<<*/"		"<<"LVelocity"<</*"	"<<"LTotal"<<*/"	"<<"LTheta"<</*"		"<<"RDistance"<<*/"		"<<"RVelocity"<</*"	"<<"RTotal"<<*/"	"<<"RTheta"<</*"		"<<"BDistance"<<*/"		"<<"BVelocity"<</*"	"<<"BTotal"<<*/"	"<<"BTheta"<<"\n";
	while(count != 20){
		float lvelocity = 10; 
		float rvelocity = 10; 
		float bvelocity = 10; 
		ldistance += stepsize * lvelocity;
		rdistance += stepsize * rvelocity;
		bdistance += stepsize * bvelocity;
		ltotal += fabs(stepsize *lvelocity);
		rtotal += fabs(stepsize *rvelocity);
		btotal += fabs(stepsize *bvelocity);
		float lvector_x = (sin(ltheta))*ldistance;
		float lvector_y = (cos(ltheta))*ldistance;
		float rvector_x = (sin(rtheta))*rdistance;
		float rvector_y = (cos(rtheta))*rdistance;
		float bvector_x = (sin(btheta))*bdistance;
		float bvector_y = (cos(btheta))*bdistance;
		float uvector_x = lvector_x + rvector_x + bvector_x;
		float uvector_y = lvector_y + rvector_y + bvector_y;
		
		
		
		
		cout<<f(time)<</*"		"<<f(ldistance)<<*/"		"<<f(lvelocity)<</*"		"<<f(ltotal)<<*/"		"<<f(ltheta)<</*"		"<<f(rdistance)<<*/"		"<<f(rvelocity)<</*"		"<<f(rtotal)<<*/"		"<<f(rtheta)<</*"		"<<f(bdistance)<<*/"		"<<f(bvelocity)<</*"		"<<f(btotal)<<*/"		"<<f(btheta)<<"\n";
		time=time+stepsize;
		count++;
	}
}




int main(){
	float f;
	tableDisplay();
	
}