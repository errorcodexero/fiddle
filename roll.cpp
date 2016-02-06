#include<stdlib.h>
#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;
struct dice{ // Create data structure dice
	int die; // Initialize variable die
};
struct player{ // Create data structure for player
	int pp;
};	// Initialize variable player position
int main(){ // Initialize main
	dice a; // Initialize a.die
	dice b; //Initialize b.die for lottery roll
	player one; // Initialize player position 1
	player two; // Initialize player position 2
	string s; // Declares string s
	string r;//Declares string q
	int m;
	int q;
	int guess; // Initialize Guessing string
	int ready; //Initialize ready command
	srand (time(NULL)); //Allow random number generation
	one.pp = 0; // Player position 1 starts at spot 0s
	two.pp = 0; //Player position 2 starts at spot 0
	do{ // Loop
		cout<<"Enter anything when you are ready to roll."; // Outputs a message
		getline(cin,s); // Pauses until user is ready
		ready=atoi(s.c_str());
		a.die = rand() % 6 + 1; // Randomly generate a die roll 1 to 6
		cout<<"You rolled a "<<a.die<<".\n"; // Out puts a message
		one.pp = one.pp + a.die; // Adds the die roll  to the position of player one
		cout<<"You moved to spot "<<one.pp<<"\n";
		if(one.pp == 1||two.pp == 1){ // If player one or player two move to spot 1
			cout<<"You eat a sandwich.\n"; // Output message
		}
		if(one.pp == 2||two.pp == 2){ // If player one or player two move to spot 2
			cout<<"Quick sand!!!! Move back one spot.\n"; // Output message
		}
		if(one.pp == 2){ // if player one is on spot 2
			one.pp = 1; // set player one back to spot one
		}
		if(two.pp == 2){// if player two is on spot 2
			two.pp = 1;// set player two back to spot one
		}
		if(one.pp == 3){ // If player one moves to spot 3
			cout<<"You found running shoes!!! Move forward 3 spots.\n"; // Output message
			one.pp = 6; //Player one moves to spot 6
		}
		if(two.pp == 3){ // If player two moves to spot 3
			cout<<"You found running shoes!!! Move forward 3 spots.\n"; //Output message
			two.pp = 6; //Player two moves to spot 6
		}
		if(one.pp == 4){ //If player one moves to spot 4
			cout<<"You get bored and fall asleep.\n"; //Output message
		}
		if(one.pp == 5){ // If player one moves to spot 5
			cout<<"You run out of food go back to the start.\n"; //Output message
			one.pp = 0; //Moves the player back to the start
		}
		if(one.pp == 6){ // if player one moves to spot 6
			cout<<"You see a sign, it says resting point.\nYou begin to question reality itself.\n"; //Output message
		}
		if(one.pp == 7){ // if player one moves to spot 7
			cout<<"Random fact Saudi Arabia imports camels from Australia.\n";
		}
		if(one.pp == 8){ // if player one moves to spot 8
			b.die = rand () % 2 + 1; //  roll a die to see if they win or lose the poker game
		}
		if(b.die == 1){ // if the die is negative aka 1
			cout<<"You bet on a poker game you lost.\nmove back to the start.\n"; //output message
			one.pp = 0; //move back to the start
			b.die = 0; // reset the die
		}
		if(b.die == 2){//if the die is positive aka 2
			cout<<"You bet on a poker game...YOU WON!!!!.\nMOVE AHEAD 10 SPACES!!!!!!!!\n";
			one.pp = one.pp + 10; //move 10 spaces up
			b.die = 0; //reset the die
		}
		if(one.pp == 9){//if player one moves to spot 9
			cout<<"Do you like pancakes?\n"; //Output message
		}
		if(one.pp == 10){ // if player one is at spot 10
			cout<<"Lucky TEN!!!!!!! ROLL AGAIN!!!!\n"; //output message
			a.die = rand() % 6 + 1; // roll the die again
			one.pp = one.pp + a.die; // move according to the die
			cout<<"You rolled a "<<a.die<<".\n"; //output message
			cout<<"You moved to spot "<<one.pp<<".\n"; //output message
		}
		if(one.pp == 11){ // if player one is at spot 11
			cout<<"Some people say video games are a waste of time. Who cares?\n";
		}
		if(one.pp == 12){ // if player is at spot 12
			cout<<"You hear some scary noises\n";
		}
		if(one.pp == 13){ // if player is at spot 13
			cout<<"A giant mouse chases you back move back to spot 11\n";
			one.pp = 11;
		}
		if(one.pp == 14){ //If player one is at spot 14
			cout<<"Pick a number between 1 and 100\n"; // Output message
			b.die = rand() % 100 + 1; //Roll a die from 1 to 100
			getline(cin,s); // Get a line
			guess=atoi(s.c_str()); // Change variable type
		}
		if(one.pp == 14 && guess == b.die){ // If player is at spot 14 and guesses right
			cout<<"Amazing!!!! You guessed the correct number Move to spot 100!!\n";//Output message
			one.pp = 100;//Set player one to spot 100 winning the game!!
		}
		if(one.pp == 14 && guess!=b.die){//If player is at spot 14 and guesses wrong
			cout<<"Sorry you guessed wrong move back to spot one.\n"; //output message
			one.pp = 0;//Set player to spot 0
			b.die = 0;//reset die
		}
		if(one.pp ==15){//If player one is at spot 15
			cout<<"You've run into a wall...Go back to where you came from\n"; //Output a message
			one.pp = one.pp - a.die; //Go back by subtracting the current postion by the previous die roll.
		}
		if(one.pp == 16){//If player is at spot 16
			cout<<"You've entered the next area!!!\n";//Output message
			one.pp == 20;//Move the player to spot 20
		}
		if(one.pp == 17){//If player one is at spot 17
			cout<<"Do you want to gamble???\n";//Ask question
			cout<<"Enter y/n\n";//Ask question
			getline(cin,s);//Get answer
			m=atoi(s.c_str());//Convert variable type
		}
		if(s == "y"){//If player wants to bet
			cout<<"Ok here we go....Guess odd or even.o/e\n";//Output message
			b.die = rand() % 4 +1;//Roll from 1 to 4
			getline(cin,r);//Get answer string r
			q=atoi(s.c_str()); //convert variable type
			s= "zero"; //Reset string s
		}
		if(r == "o" && b.die == 1 || b.die == 3){//If player one guess odd and die is odd
			cout<<"You won!! Congrats\n";
			cout<<"Move ahead 20 spaces\n";
			one.pp = 37;
			b.die = 0;
			r= "zero";//Reset string r
		}
		if(r == "o" && b.die == 2 || b.die == 4){//If player one guess odd and die is even
			cout<<"You lost... Move back to the start\n";//Output message
			one.pp = 0;//Reset position back to start
			b.die = 0;//Reset die
			r = "zero";//Reset string r
		}
		if( r == "e" && b.die ==2 || b.die == 4){//If player one guesses even and die is even
			cout<<"You win!! Congrats\n";//Output message
			cout<<"Move ahead 20 spaces\n";//Output message
			one.pp = 37;//Move player twenty spots ahead
			b.die = 0;//Reset Die
			r = "zero";//Reset string r
		}
		if( r == "e" && b.die == 1 || b.die ==3){//If player one guesses even and die is odd
			cout<<"You lost... Move back to the start\n";//Output message
			one.pp = 0;//Reset position
			b.die = 0;//Reset die
			r = "zero";//Reset string r
		}
		if(one.pp == 18){//If player one is on spot 18
			cout<<"Nothing happens...\n";//output message
			cout<<"...\n";//output message
			cout<<"...\n";//output message
			cout<<"...\n";//output message
			cout<<"...\n";//output message
			cout<<"...\n";//output message
			cout<<"...\n";//output message
		}
		if(one.pp == 19){
			cout<<"You earned a cookie good job!\n";
		}
		if(one.pp == 20){
			cout<<"Welcome to the next zone!!\n";
		}
		if(one.pp == 21){
			cout<<"Oh no pit fall!!!\n";
			cout<<"Move back 7 spaces :(\n";
			one.pp == 14;
		}
		
		if(one.pp >= 100){
			cout<<"Congratulations player one!!!\n";
			cout<<"You have beaten the game, you rock!!!\n";
			return 0;
		}
		if(two.pp >= 100){
			cout<<"Congratulations player two!!!\n";
			cout<<"You have beaten the game, you rock!!!\n";
			return 0;
		}
		
			
			
	}while(one.pp < 100 || two.pp < 100) ; // While player one and two are not at the end of the game continue the game.
		
}