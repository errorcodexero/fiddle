#include <iostream>
#include <vector>

using namespace std;

struct Point {
	int x = 0;
	int y = 0;
}

int SurroundingMines(Point point, vector<Point> m) {
	int numOfMines = 0;
	Point p = point;
	
	p.x++;
	IsMine(p, m) ? numOfMines++ : numOfMines+= 0;
	
	p = point;
	p.x--;
	IsMine(p, m) ? numOfMines++ : numOfMines+= 0;

	p = point;
	p.y--;
	IsMine(p, m) ? numOfMines++ : numOfMines+= 0;

	p = point;
	p.y++;
	IsMine(p, m) ? numOfMines++ : numOfMines+= 0;

	p = point;
	p.x--;
	p.y--;
	IsMine(p, m) ? numOfMines++ : numOfMines+= 0;

	p = point;
	p.x--;
	p.y++;
	IsMine(p, m) ? numOfMines++ : numOfMines+= 0;

	p = point;
	p.x++;
	p.y--;
	IsMine(p, m) ? numOfMines++ : numOfMines+= 0;

	p = point;
	p.x++;
	p.y++;
	IsMine(p, m) ? numOfMines++ : numOfMines+= 0;
	
	
	return numOfMines;
}

bool IsMine(Point p, vector<Point> m) {
	return FindInVector(p, m);
}

bool FindInVector(Point p, vector<Point> v) {
	for(int i = 0; i < v.size; i++) {
		if (v[i] == p) {
			return true;
		}
	}
	
	return false;
}

void EndGame() {
	
}

int main() {
	vector<Point> mines,
		      visited;
	int mineNum = 0,
	    squareNum = 0;
	Point check;
	
	//ask user for field dimentions
	//ask user for mine locations
	
	//Setup Minefield
		//Display Minefield
	
	while (visited.size() > squareNum - mineNum) {
		//Ask user to check position
		if (IsMine(check, mines)) {
			EndGame();
		}
		
	
	
	
	return 0;
}
