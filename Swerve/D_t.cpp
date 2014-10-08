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
	float theta = 0; //angle of turn
	float delta_theta = 0; //angle increase in turn
	float delta_y; //difference in distance travelled between wheels
	float distance_between_wheels = 3; //example: 3ft between left and right wheels
	float x_coord = 0;
	float y_coord = 0;
	cout<<"Time"<<"		"<<"LDistance"<<"	"<<"LVelocity"<<"	"<<"LTotal"<<"			"<<"RDistance"<<"	"<<"RVelocity"<<"	"<<"RTotal"<<"		"<<"Theta"<<"		"<<"coordinates"<<"\n";
	while(count != 20){
		float lvelocity = sin(time);
		float rvelocity = cos(time);
		ldistance += stepsize *lvelocity;
		rdistance += stepsize * rvelocity;
		ltotal += fabs(stepsize *lvelocity);
		rtotal += fabs(stepsize *rvelocity);
		delta_y = ltotal - rtotal;
		delta_theta = atan2(delta_y, distance_between_wheels);
		theta += delta_theta;
		float h = (ltotal + rtotal)/2;
		x_coord = (sin(theta))*h;
		y_coord = (cos(theta))*h;
		
		
		
		
		cout<<f(time)<<"		"<<f(ldistance)<<"		"<<f(lvelocity)<<"		"<<f(ltotal)<<"			"<<f(rdistance)<<"		"<<f(rvelocity)<<"		"<<f(rtotal)<<"		"<<f(theta)<<"		"<<f(x_coord)<<", "<<f(y_coord)<<"\n";
		time=time+stepsize;
		count++;
	}
}




int main(){
	float f;
	tableDisplay();
}