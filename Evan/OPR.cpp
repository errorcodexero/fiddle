#include<iostream>
#include<stdlib.h>
using namespace std;
int main(int argc,char**argv){
/*	for(int i=0;i<argc;i++){
		cout<<i<<" "<<argv[i]<<"\n";
	}*/
	int startx=0;
	if(argc==5){startx=atoi(argv[1]);}
	int finishx=5;
	if(argc==5){finishx=atoi(argv[2]);}
	int starty=0;
	if(argc==5){starty=atoi(argv[3]);}
	int finishy=5;
	if(argc==5){finishy=atoi(argv[4]);}
	cout<<"Start="<<"("<<startx<<","<<starty<<")"<<"\n";
	cout<<"Finish="<<"("<<finishx<<","<<finishy<<")"<<"\n";	
	while(startx>finishx){
		cout<<"you moved left to position "<<","<<startx-1<<","<<starty<<")"<<"\n";
		startx--;
	}
	while(startx<finishx){
		cout<<"you moved right to position " <<"("<<startx+1<<","<<starty<<")"<<"\n";
		startx++;
	}
	while(starty>finishy){
		cout<<"you moved down to position " <<"("<<startx<<","<<starty-1<<")"<<"\n";
		starty--;
	}
	while(starty<finishy){
		cout<<"you moved up to position " <<"("<<startx<<","<<starty+1<<")"<<"\n";
		starty++;	


		if(startx==finishx){
			if(starty==finishy){
				cout<<"You did it!"<<"\n";
			
			}
		}
	}
}


