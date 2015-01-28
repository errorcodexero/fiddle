#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

struct charecter {
	int health;
	int armour;
	int strength;
	int inteligence;
	int gold;
	int difficulty;
	string name;	
};

void print_stats(charecter hero){
	cout<<hero.name<<":"<<"\n-health : "<<hero.health<<"\n-armour : "<<hero.armour<<"\n-strength : "<<hero.strength<<"\n-inteligence : "<<hero.inteligence<<"\n-gold : "<<hero.gold<<"\n";
}


charecter create_charecter(){
	charecter hero;
	hero.health = rand() % 5 + 5;
	hero.armour = 0;
	hero.strength = rand() % 5 + 5;
	hero.inteligence = rand() % 5 + 5;
	hero.gold = 20;
	hero.difficulty = 1;
	cout<<"What is your name?\n";
	getline(cin,hero.name);
	return hero;
}

int main(){
	charecter hero = create_charecter();
	print_stats(hero);
}
