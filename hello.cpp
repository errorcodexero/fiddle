#include<stdlib.h>
#include<iostream>
// Walls at 3,2 -1,5 2,-4 -5,-2
using namespace std;
struct point2d{
	int x,y;
	};
ostream& operator<<(ostream& o,point2d a){
	return o<<"Pt("<<a.x<<","<<a.y<<")\n";
}
	int getstruct(){
	string u;
	getline(cin,u);
	return atoi(u.c_str());
 }
int main(){
  point2d cx;
  cout<<"X:";
  cx.x=getstruct();
  cout<<"Y:";
  cx.y=getstruct();
  cout<<cx.x<<","<<cx.y<<"\n";
  if(cx.x==3&&cx.y==2){
  cout<<"Sorry you hit a wall.\n";
  void exit(int);
  }
  int currentx;
  int currenty;
  int destx;
  int desty;
 cout<<"What is your current x?\n";
  string s;
  getline(cin,s);
  currentx=atoi(s.c_str());
  cout<<"What is your current y?\n";
  string e;
  getline(cin,e);
  currenty=atoi(e.c_str());
  cout<<"What is your desired x?\n";
  string r;
  getline(cin,r);
  destx=atoi(r.c_str());
  cout<<"What is your desired y?\n";
  string j;
  getline(cin,j);
  desty=atoi(j.c_str());
  if(destx==-1&&desty>=5){
	cout<<"Sorry you hit a wall.\n";
	}
  if(destx==2&&desty<=-4){
	cout<<"Sorry you hit a wall.\n";
	}
  if(destx==-5&&desty<=-2){
	cout<<"Sorry you hit a wall.\n";
	}
  if(currentx>destx){
    cout<<"You must move left "<<currentx-destx<<".\n";
  }
  if(currentx==destx){
    cout<<"You do not need to move left or right\n";
  }
  if(currentx<destx){
    cout<<"You must move right "<<destx-currentx<<".\n";
  }
  if(currenty>desty){
    cout<<"You must move down "<<currenty-desty<<".\n";
  }
  if(currenty==desty){
    cout<<"You do not need to move up or down\n";
  }
  if(currenty<desty){
    cout<<"You must move up "<<desty-currenty<<".\n";
  }
  cout<<"\nYour slope is "<<currenty-desty<<"/"<<currentx-destx<<"\n";
  
}  