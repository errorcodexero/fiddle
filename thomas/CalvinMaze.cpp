#include <iostream>
#include <stdlib.h>
#include <vector>
#include <unistd.h>
using namespace std;

struct point {
	int x;
	int y;	
};

int getPoint(string message){
	string getPoint;
	cout<<message;
	getline(cin,getPoint);
	return atoi(getPoint.c_str());
}

int main(){
	point player;
	player.x=getPoint("Where does the player start horizontally?\n");
	player.y=getPoint("Where does the player start vertically?\n");

	point goal;
	goal.x=getPoint("Where is the goal horizontally?\n");
	goal.y=getPoint("Where is the goal vertically?\n");

	vector<vector<int>> maze{
		{0,0,1,0},
		{0,0,1,0},
		{0,0,0,0}
	};
	
	int moveX;
	int moveY;
	int lastMove;

	int xMax=3;
	int yMax=2;

	int desprate;

	bool finished=false;

	while(!finished){
		if(player.x>goal.x){
			moveX = -1;
		}else 	if(player.x<goal.x){
			moveX = 1;
		}else {
			moveX = 0;
		}

		if(player.y>goal.y){
			moveY = -1;
		}else 	if(player.y<goal.y){
			moveY = 1;
		}else {
			moveY = 0;
		}
	
		if(moveX==-1 && (maze[player.y])[player.x-1]==0 && player.x!=0){
			if(lastMove!=1){
				player.x--;
				cout<<"Move left\n";
				lastMove = 3;
			}else{
				player.x++;
				cout<<"Move right\n";
			}
		}else if(moveX==1 && (maze[player.y])[player.x+1]==0 && player.x!=xMax){
			if(lastMove!=3){
				player.x++;
				cout<<"Move right\n";
				lastMove = 1;
			}else{
				player.x--;
				cout<<"Move left\n";
			}
		}else if(moveY==-1 && (maze[player.y-1])[player.x]==0 && player.y!=0){
			if(lastMove!=2){
				player.y--;
				cout<<"Move up\n";
				lastMove = 0;
			}else{
				player.y++;
				cout<<"Move down\n";
			}
		}else if(moveY==1 && (maze[player.y+1])[player.x]==0 && player.y!=yMax){
			if(lastMove!=0){
				player.y++;
				cout<<"Move down\n";
				lastMove = 2;
			}else{
				player.y--;
				cout<<"Move up\n";
			}
		}else if(moveX==-1 && (maze[player.y])[player.x-1]==1){
			if(lastMove==0 && player.y!=0 && (maze[player.y-1])[player.x]==0){
				player.y--;
				cout<<"Move up\n";
			}else if(lastMove==2 && player.y!=yMax && (maze[player.y+1])[player.x]==0){
				player.y++;
				cout<<"Move down\n";
			}else if(player.y!=0 && (maze[player.y-1])[player.x]==0){
				player.y--;
				cout<<"Move up\n";
				lastMove=0;
			}else if(player.y!=2 && (maze[player.y+1])[player.x]==0){
				player.y++;
				cout<<"Move down\n";
				lastMove=2;
			}else{
				player.x++;
				cout<<"Move right\n";
				lastMove=1;
			}
		}else if(moveX==1 && (maze[player.y])[player.x+1]==1){
			if(lastMove==0 && player.y!=0 && (maze[player.y-1])[player.x]==0){
				player.y--;
				cout<<"Move up\n";
			}else if(lastMove==2 && player.y!=yMax && (maze[player.y+1])[player.x]==0){
				player.y++;
				cout<<"Move down\n";
			}else if(player.y!=0 && (maze[player.y-1])[player.x]==0){
				player.y--;
				cout<<"Move up\n";
				lastMove=0;
			}else if(player.y!=2 && (maze[player.y+1])[player.x]==0){
				player.y++;
				cout<<"Move down\n";
				lastMove=2;
			}else{
				player.x--;
				cout<<"Move left\n";
				lastMove=3;
			}
		}else if(moveY==-1 && (maze[player.y-1])[player.x]==1){
			if(lastMove==1 && player.x!=xMax && (maze[player.y])[player.x+1]==0){
				player.x++;
				cout<<"Move right\n";
			}else if(lastMove==3 && player.x!=0 && (maze[player.y])[player.x-1]==0){
				player.x--;
				cout<<"Move left\n";
			}else if(player.x!=0 && (maze[player.y])[player.x-1]==0){
				player.x--;
				cout<<"Move left\n";
				lastMove=3;
			}else if(player.x!=3 && (maze[player.y])[player.x+1]==0){
				player.x++;
				cout<<"Move right\n";
				lastMove=1;
			}else{
				player.y++;
				cout<<"Move down\n";
				lastMove=2;
			}
		}else if(moveY==1 && (maze[player.y+1])[player.x]==1){
			if(lastMove==1 && player.x!=3 && (maze[player.y])[player.x+1]==0){
				player.x++;
				cout<<"Move right\n";
			}else if(lastMove==3 && player.x!=0 && (maze[player.y])[player.x-1]==0){
				player.x--;
				cout<<"Move left\n";
			}else if(player.x!=0 && (maze[player.y])[player.x-1]==0){
				player.x--;
				cout<<"Move left\n";
				lastMove=3;
			}else if(player.x!=3 && (maze[player.y])[player.x+1]==0){
				player.x++;
				cout<<"Move right\n";
				lastMove=1;
			}else{
				player.y--;
				cout<<"Move up\n";
				lastMove=0;
			}
		}else if(player.x==goal.x && player.y==goal.y){
			cout<<"End :)\n";
			finished=true;
		}else{
			while(true){			
				desprate = rand()%4;
				
			}
			/*cout<<"I give up :(\n";
			finished=true;*/
		}
	}
}
