#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Point {
	int x, y;
	
	Point(){}
	Point(int setX, int setY) {
		x = setX;
		y = setY;	
	}
};

struct Node;

struct Path {
	Node *connect;
	int cost;
	
	Path(){}
	Path(Node* setConnect, int setCost) {
		connect = setConnect;
		cost = setCost;
	}
}; 

struct Node {
	Point loc;
	vector<Path> paths;
	
	Node(){}
	Node(Point setLoc, vector<Path> setPaths) {
		loc = setLoc;
		paths = setPaths;
	}
};

struct Map {
	int width, height;
	vector<Node> nodes;
	vector<vector<string>> image;
	Node current;

	Map(){}
	Map(int setWidth, int setHeight, vector<Node> setNodes) {
		width = setWidth;
		height = setHeight;
		nodes = setNodes;
		current = nodes[0];
		image = vector<vector<string>>(width, vector<string>(height, " "));
	}
	
	void draw() {
		system("reset");
                vector<vector<string>> image = vector<vector<string>>(width, vector<string>(height, " "));
		for (Node node: nodes) {
			bool exit = false;
                        for (Path path: node.paths) {
                                int deltaX = path.connect->loc.x-node.loc.x;
                                int deltaY = path.connect->loc.y-node.loc.y;
                                int pointNum = max(abs(deltaX-1),abs(deltaY-1));
				if (node.loc.x < path.connect->loc.xi) {
                                        for (int i = 1; i < pointNum; i++) {
                                                image[round(node.loc.x+i*deltaX/pointNum)][round(node.loc.y+i*deltaY/pointNum)]="◦";
                                        }
                                }
                        }
                }
                for (Path path: current.paths) {
                        int deltaX = path.connect->loc.x-current.loc.x;
                        int deltaY = path.connect->loc.y-current.loc.y;
                        int pointNum = max(abs(deltaX-1),abs(deltaY-1));
                        if (current.loc.x < path.connect->loc.x) {
                                for (int i = 1; i < pointNum; i++) {
                                        image[round(current.loc.x+i*deltaX/pointNum)][round(current.loc.y+i*deltaY/pointNum)]="•";
                                }
                        } else {
                                for (int i = 1; i < pointNum; i++) {
                                        image[round(path.connect->loc.x-i*deltaX/pointNum)][round(path.connect->loc.y-i*deltaY/pointNum)]="•";
                                }

                        }
                }

                for (Node node: nodes) {
                        image[node.loc.x][node.loc.y] = "✖";
                }
                image[current.loc.x][current.loc.y] = "✈️️";

		cout<<"╔═";
		for (int i = 0; i < image.size(); i++) {
			cout<<"══";
		}
		cout<<"╗\n";
                for (int y = 0; y < image[0].size(); y++) {
			cout<<"║ ";
                        for(int x = 0; x < image.size(); x++) {
                                cout<<image[x][y]<<" ";
                        }
                        cout<<"║\n";
                }
		cout<<"╚═";
                for (int i = 0; i < image.size(); i++) {
                        cout<<"══";
                }
                cout<<"╝\n";

        }

};

int randBetween(int min, int max) {
	return rand()%max+min;
}

int main() {
	int width = 90;
	int height = 44;

	srand(time(0));
	int ax = randBetween(0, width);
	int ay = randBetween(0, height);
	int bx = randBetween(0, width);
	int by = randBetween(0, height);
	int gx = randBetween(0, width);
	int gy = randBetween(0, height);
	int dx = randBetween(0, width);
	int dy = randBetween(0, height);
	int ex = randBetween(0, width);
	int ey = randBetween(0, height);
	Node alpha = Node(Point(ax, ay), vector<Path>()),
	      beta = Node(Point(bx, by), vector<Path>()),
	     gamma = Node(Point(gx, gy), vector<Path>()),
	     delta = Node(Point(dx, dy), vector<Path>()),
	   epsilon = Node(Point(ex, ey), vector<Path>());

	alpha.paths.push_back(Path(&beta, 1));
	alpha.paths.push_back(Path(&gamma, 1));
	alpha.paths.push_back(Path(&delta, 1));

	beta.paths.push_back(Path(&alpha, 1));
	beta.paths.push_back(Path(&gamma, 1));
	beta.paths.push_back(Path(&delta, 1));
	beta.paths.push_back(Path(&epsilon, 1));

	gamma.paths.push_back(Path(&alpha, 1));
	gamma.paths.push_back(Path(&beta, 1));
	gamma.paths.push_back(Path(&epsilon, 1));

	delta.paths.push_back(Path(&alpha, 1));
	delta.paths.push_back(Path(&beta, 1));
	
	epsilon.paths.push_back(Path(&beta, 1));
	epsilon.paths.push_back(Path(&gamma, 1));
	
	vector<Node> nodes;
	nodes.push_back(alpha);
	nodes.push_back(beta);
	nodes.push_back(gamma);
	nodes.push_back(delta);
	nodes.push_back(epsilon);
	Map testMap(width, height, nodes);
	testMap.draw();
}

