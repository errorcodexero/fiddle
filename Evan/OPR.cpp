#include<iostream>
using namespace std;
int main(int argc,char**argv){
/*	for(int i=0;i<argc;i++){
		cout<<i<<" "<<argv[i]<<"\n";
	}*/
	int start=3;
	int finish=5;
	cout<<"Start="<<start<<"\n";
	cout<<"Finish="<<finish<<"\n";
	while(start!=finish){
		cout<<"you moved right to position "<<start<<"\n";
		start++;
	}
	if(start==finish){
		cout<<"You did it!"<<"\n";
			
	}
}

