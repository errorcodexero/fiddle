#include <iostream>

using namespace std;

const int robotspeed=156; // in in/sec

int traveltime(int from,int to){
	int distance=from-to;
	int time=distance/robotspeed;
	return time;
}
int main(){
	//Balls
	int startballs=1;
	int centerballs=6;
	int ballscores=0;
	
	//Field in inches
	const int fieldlength=624;
	const int startpos=fieldlength/2;
	int defense=fieldlength/4;
	int centervalue=fieldlength/2;
	
	//Time in seconds
	int gametime=150; 
	int scoretime=2;
	
	for(gametime>0;startballs>0||centerballs>0;){
		if(startballs>0){
			gametime=gametime-traveltime(fieldlength,startpos);
			gametime=gametime-scoretime*startballs;
			if(gametime>0)ballscores++;
			startballs=startballs-1;
			cout<<gametime<<" a"<<endl;
		}
		if(centerballs>0){
			gametime=gametime-traveltime(fieldlength,startpos)*2;
			gametime=gametime-scoretime;
			if(gametime>0)ballscores++;
			centerballs=centerballs-1;
			cout<<gametime<<" b"<<endl;
		}		
	}
	
	while(gametime>0){
		gametime=gametime-traveltime(fieldlength,defense*3)*2;
		gametime=gametime-scoretime;
		if(gametime>0){
			ballscores++;
			cout<<gametime<<" c"<<endl;
		}
	}
	cout<<"Game Time="<<150<<endl<<"Remaining Time="<<gametime<<endl<<"Ball Scores="<<ballscores<<endl;
	
	
	

	return 0;
}

