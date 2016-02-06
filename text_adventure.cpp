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
	int action;	
};

void print_charecter_stats(charecter hero){
	cout<<hero.name<<":"<<"\n-health : "<<hero.health<<"\n-armour : "<<hero.armour<<"\n-strength : "<<hero.strength<<"\n-inteligence : "<<hero.inteligence<<"\n-gold : "<<hero.gold<<"\n";
}

struct creature {
	int health;
	int armour;
	int strength;
	string name;
};

void print_creature_stats(charecter hero){
	cout<<hero.name<<":"<<"\n-health : "<<hero.health<<"\n-armour : "<<hero.armour<<"\n-strength : "<<hero.strength<<"\n";
};

creature create_creature(int difficulty);
	creature monster;
	monster.health = rand() % (5*difficulty) + (5*difficulty);
	monster.armour = rand() % (5*difficulty) + (5*difficulty);
	monster.strength = rand() % (5*difficulty) + (5*difficulty);
	return monster;
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
	print_charecter_stats(hero);
	creature monster = create_creature();
	monster.name = "Troll";
	cout<<"You come across a troll.\n";
	print_creature_stats(monster);
}




