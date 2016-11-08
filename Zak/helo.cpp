#include<iostream>
using namespace std;
int bop(){
	string d;
	d=" In Call of Duty: Black Ops 2, Frank Woods has a rivalry and long time hatred for whom?";
	cout<<d;
	cout<<"\n";
	getline(cin,d);
	if(d=="Raul Menendez"){
		cout<<" Correct answer, for now...\n";
	}else{
		cout<<" MENENDEZ!\n";
	return(0);
	}
	string e;
		e=" In Halo, what is Master Chief's Spartan number?";
	cout<<e;
	cout<<"\n";		
	getline(cin,e);
	if(e=="117"){
		cout<<" *Chief silently gives you a thumbs up*.\n";
	}else{
		cout<<" *Chief Silently gives you a thumbs down*.\n";
	}
	string f;
		f=" In the web series, Red vs Blue, Who says 'Bow Chicka Bow Wow'?";
	cout<<f;
	cout<<"\n";		
	getline(cin,f);
	if(f=="Tucker"){
		cout<<" Honk Chicka Honk Honk!\n";
	}else{
		cout<<" You failed, might as well get in the 'Puma'.\n";
	}
	string g;
		g=" In the game Dishonered, what is the main characters name?";
	cout<<g;
	cout<<"\n";		
	getline(cin,g);
	if(g=="Corvo Attano"){
		cout<<" The Outsider sees your victory.\n";
	}else{
		cout<<" The Outsider sees your failure.\n";
	}
	string h;
		h=" In Call of Duty Zombies, What are the four main characters names?(The ones they are most commonly called by)( Blank, Blank, Blank, and Blank)(Wrong order will be marked wrong)";
	cout<<h;
	cout<<"\n";		
	getline(cin,h);
	if(h=="Dempsey, Takeo, Nikolai, and Richtofen"){
		cout<<" You must play real games, good job!\n";
	}else{
		cout<<" You clearly haven't had any good zombie experiences.\n";
	}
	string i;
		i=" In D&D, is a Nat. 20 Good, or Bad? ";
	cout<<i;
	cout<<"\n";		
	getline(cin,i);
	if(i=="Good"){
		cout<<" I cast Firebolt and roll a Nat 20! Sucess!\n";
	}else{
		cout<<" You are not a very good geek...\n";
	}
	string j;
		j="Now, is this quiz good? ";
	cout<<j;
	cout<<"\n";		
	getline(cin,j);
	if(j=="Yes"){
		cout<<" You've got good taste!\n";
	}else{
		cout<<" Everyone's a critic...\n";
	}
}
int main(){
	bop();
}
