# include <iostream>
# include <cstdlib>
using namespace std;
main(){
srand(time(NULL));
int number = rand()%10+1;
int guess;
while(guess != number){
	cout<<"guess my number\n";
	cin>>guess;
	//get guess
	if (guess>number){
	cout<<"Too big, try again loser...\n";
	// Nah
	}else if(guess<number){
	cout<<"Too small, try again loser...\n";
	// Nah
	}
}
	cout<<"You did that thing you were supposed to do!\n";
	// you did it
}
