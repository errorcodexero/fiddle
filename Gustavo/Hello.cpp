#include <iostream> 
using namespace std; 

/*int main(){
	int x=0, y=0;
	cout<<"Enter a number:";
	cin>>x;
	cout<<"Enter a number:";
	cin>>y;
	if(x < y -5)cout<<"cat\n";
	else cout<<"dog\n";

}*/
 
int main(){
	int x=0, y=0;
	cout<<"Please put a number where you want to go:";
	//cin>>x;
	cin>>x;
	
	if(x==4)cout<<"Do nothing";
	if(x==3) cout<<"Go left";
	if(x==2)cout<<"Go two times left";
	if(x==1)cout<<"Go three times left";
	if(x==0)cout<<"Go four times left";
	if(x==5)cout<<"Go right";
	
}
 