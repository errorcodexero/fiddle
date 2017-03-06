#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstdlib>

using namespace std;

struct Point {
	int x, y;
	
	Point(){}
	Point(int setX, int setY) {
		x = setX;
		y = setY;	
	}
};

bool operator == (Point& a, Point& b) {
	return a.x == b.x && a.y == b.y;
}

bool operator != (Point& a, Point& b) {
	return !(a == b);
}

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

bool operator == (Node* a, Node b) {
	return 	a->loc == b.loc;
}

bool operator != (Node* a, Node b) {
	return !(a == b);
}

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
                        for (Path path: node.paths) {
                                int deltaX = path.connect->loc.x-node.loc.x;
                                int deltaY = path.connect->loc.y-node.loc.y;
                                int pointNum = max(abs(deltaX-1),abs(deltaY-1));
				if (node.loc.x <= path.connect->loc.x && path.connect != current) {
                                        for (int i = 1; i < pointNum; i++) {
                                                image[round(node.loc.x+i*deltaX/pointNum)][round(node.loc.y+i*deltaY/pointNum)]="-";
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
		for (int i= 0; i < current.paths.size(); i++) {
			image[current.paths[i].connect->loc.x][current.paths[i].connect->loc.y] = to_string(i+1);
		}

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
	int width = 85;
	int height = 44;
	/*
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
	*/
	Node alpha = Node(Point(44, 5), vector<Path>()),
	      beta = Node(Point(30, 13), vector<Path>()),
	     gamma = Node(Point(30, 29), vector<Path>()),
	     delta = Node(Point(44, 37), vector<Path>()),
	   epsilon = Node(Point(58, 29), vector<Path>()),
	      zeta = Node(Point(58, 13), vector<Path>()),
	       eta = Node(Point(44, 11), vector<Path>()),
	     theta = Node(Point(35, 26), vector<Path>()),
	      iota = Node(Point(53, 26), vector<Path>());

	alpha.paths.push_back(Path(&beta, 1));
	alpha.paths.push_back(Path(&zeta, 1));
	alpha.paths.push_back(Path(&eta, 1));

	beta.paths.push_back(Path(&alpha, 1));
	beta.paths.push_back(Path(&gamma, 1));
	beta.paths.push_back(Path(&eta, 1));
	beta.paths.push_back(Path(&theta, 1));

	gamma.paths.push_back(Path(&beta, 1));
	gamma.paths.push_back(Path(&delta, 1));
	gamma.paths.push_back(Path(&theta, 1));

	delta.paths.push_back(Path(&gamma, 1));
	delta.paths.push_back(Path(&epsilon, 1));
	delta.paths.push_back(Path(&theta, 1));
	delta.paths.push_back(Path(&iota, 1));
	
	epsilon.paths.push_back(Path(&delta, 1));
	epsilon.paths.push_back(Path(&zeta, 1));
	epsilon.paths.push_back(Path(&iota, 1));

	zeta.paths.push_back(Path(&epsilon, 1));
	zeta.paths.push_back(Path(&alpha, 1));
	zeta.paths.push_back(Path(&iota, 1));
	zeta.paths.push_back(Path(&eta, 1));

	eta.paths.push_back(Path(&theta, 1));
	eta.paths.push_back(Path(&iota, 1));
	eta.paths.push_back(Path(&alpha, 1));
	eta.paths.push_back(Path(&beta, 1));
	eta.paths.push_back(Path(&zeta, 1));

	theta.paths.push_back(Path(&iota, 1));
	theta.paths.push_back(Path(&eta, 1));
	theta.paths.push_back(Path(&beta, 1));
	theta.paths.push_back(Path(&gamma, 1));
	theta.paths.push_back(Path(&delta, 1));

	iota.paths.push_back(Path(&eta, 1));
	iota.paths.push_back(Path(&theta, 1));
	iota.paths.push_back(Path(&delta, 1));
	iota.paths.push_back(Path(&epsilon, 1));
	iota.paths.push_back(Path(&zeta, 1));
	
	vector<Node> nodes;
	nodes.push_back(alpha);
	nodes.push_back(beta);
	nodes.push_back(gamma);
	nodes.push_back(delta);
	nodes.push_back(epsilon);
	nodes.push_back(zeta);
	nodes.push_back(eta);
	nodes.push_back(theta);
	nodes.push_back(iota);
	Map testMap(width, height, nodes);
	testMap.draw();
	
	int choice = -1;
	string getChoice ="";
	while (choice != 0) {
		testMap.draw();
		cout<<"Which location would you like to go to?\n";
		getline(cin, getChoice);
		choice = atoi(getChoice.c_str());
		if (choice != 0) {
			for (Node node: testMap.nodes) {
				if(testMap.current.paths[choice-1].connect == node) {
					testMap.current = node;
					break;
				}
			}
		}
	}
}
