#include<iostream>

using namespace std;

int main()                            
{
    string answer;                          
	while (1) {
    cout << "Do you like yams?\n"; 
   
		getline (cin, answer);
								// ( "%d", &answer );     
		if ( answer == "y" )                   
        cout << "Good for you!\n" ; 
    
		else if ( answer == "n" )           
        cout << "Shame on you!\n";       
    
		else 
        cout << "Try again...\n" ;     
    }
  return 0;
}