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
	Node(Point setLoc) {
		loc = setLoc;
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
                                int pointNum = max(abs(deltaX),abs(deltaY));
				if (node.loc.x <= path.connect->loc.x && path.connect != current) {
                                        for (int i = 1; i <= pointNum; i++) {
                                                image[round(node.loc.x+i*deltaX/pointNum)][round(node.loc.y+i*deltaY/pointNum)]="-";
                                        }
                                }
                        }
                }
                for (Path path: current.paths) {
                        int deltaX = path.connect->loc.x-current.loc.x;
                        int deltaY = path.connect->loc.y-current.loc.y;
                        int pointNum = max(abs(deltaX),abs(deltaY));
                        if (current.loc.x < path.connect->loc.x) {
                                for (int i = 1; i <= pointNum; i++) {
                                        image[round(current.loc.x+i*deltaX/pointNum)][round(current.loc.y+i*deltaY/pointNum)]="•";
					if (i == round(pointNum/2)) {
						image[round(current.loc.x+i*deltaX/pointNum)-1][round(current.loc.y+i*deltaY/pointNum)]=to_string(path.cost/10);
						image[round(current.loc.x+i*deltaX/pointNum)][round(current.loc.y+i*deltaY/pointNum)]=to_string(path.cost%10);
					}
                                }
                        } else {
                                for (int i = 1; i <= pointNum; i++) {
                                        image[round(path.connect->loc.x-i*deltaX/pointNum)][round(path.connect->loc.y-i*deltaY/pointNum)]="•";
                                        if (i == round(pointNum/2)) {
                                                image[round(current.loc.x+i*deltaX/pointNum)-1][round(current.loc.y+i*deltaY/pointNum)]=to_string(path.cost/10);
						image[round(current.loc.x+i*deltaX/pointNum)][round(current.loc.y+i*deltaY/pointNum)]=to_string(path.cost%10);
                                        }

                                }

                        }
                }

                for (Node node: nodes) {
                        image[node.loc.x][node.loc.y] = "▽";
                }
                image[current.loc.x][current.loc.y] = "◈";
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

int getcost(Node a, Node b) {
	return round(ceil(pow(a.loc.x-b.loc.x,2)+pow(a.loc.y-b.loc.y,2))/15);
}

int main() {
	int width = 85;
	int height = 44; 
	Node a = Node(Point(24, 5)),
	     b = Node(Point(10, 13)),
	     c = Node(Point(10, 29)),
	     d = Node(Point(24, 37)),
	     e = Node(Point(38, 29)),
	     f = Node(Point(38, 13)),
	     g = Node(Point(24, 11)),
	     h = Node(Point(15, 26)),
	     i = Node(Point(33, 26)),

	     j = Node(Point(64, 5)),
             k = Node(Point(50, 13)),
             l = Node(Point(50, 29)),
             m = Node(Point(64, 37)),
             n = Node(Point(78, 29)),
             o = Node(Point(78, 13)),
             p = Node(Point(64, 11)),
             q = Node(Point(55, 26)),
             r = Node(Point(73, 26)),

	     s = Node(Point(44, 21));

	
	a.paths = vector<Path>{Path(&b, getcost(a, b)), Path(&g, getcost(a, g)), Path(&f, getcost(a, f))};
	b.paths = vector<Path>{Path(&a, getcost(b, a)), Path(&g, getcost(b, g)), Path(&h, getcost(b, h)), Path(&c, getcost(b, c))};
	c.paths = vector<Path>{Path(&b, getcost(c, b)), Path(&h, getcost(c, h)), Path(&d, getcost(c, d))};
	d.paths = vector<Path>{Path(&c, getcost(d, c)), Path(&h, getcost(d, h)), Path(&i, getcost(d, i)), Path(&e, getcost(d, e))};
	e.paths = vector<Path>{Path(&d, getcost(e, d)), Path(&i, getcost(e, i)), Path(&f, getcost(e, f)), Path(&s, getcost(e, s)), Path(&l, getcost(e, l))};
	f.paths = vector<Path>{Path(&a, getcost(f, a)), Path(&g, getcost(f, g)), Path(&i, getcost(f, i)), Path(&e, getcost(f, e)), Path(&s, getcost(f, s)), Path(&k, getcost(f, k))};
	g.paths = vector<Path>{Path(&a, getcost(g, a)), Path(&b, getcost(g, b)), Path(&h, getcost(g, h)), Path(&i, getcost(g, i)), Path(&f, getcost(g, f))};
	h.paths = vector<Path>{Path(&b, getcost(h, b)), Path(&c, getcost(h, c)), Path(&d, getcost(h, d)), Path(&i, getcost(h, i)), Path(&g, getcost(h, g))};
	i.paths = vector<Path>{Path(&g, getcost(i, g)), Path(&h, getcost(i, h)), Path(&d, getcost(i, d)), Path(&e, getcost(i, e)), Path(&f, getcost(i, f))};

	j.paths = vector<Path>{Path(&k, getcost(j, k)), Path(&p, getcost(j, p)), Path(&o, getcost(j, o))};
        k.paths = vector<Path>{Path(&f, getcost(k, f)), Path(&j, getcost(k, j)), Path(&p, getcost(k, p)), Path(&q, getcost(k, q)), Path(&l, getcost(k, l)), Path(&s, getcost(k, s))};
        l.paths = vector<Path>{Path(&e, getcost(l, e)), Path(&s, getcost(l, s)), Path(&k, getcost(l, k)), Path(&q, getcost(l, q)), Path(&m, getcost(l, m))};
        m.paths = vector<Path>{Path(&l, getcost(m, l)), Path(&q, getcost(m, q)), Path(&r, getcost(m, r)), Path(&n, getcost(m, n))};
        n.paths = vector<Path>{Path(&m, getcost(n, m)), Path(&r, getcost(n, r)), Path(&o, getcost(n, o))};
        o.paths = vector<Path>{Path(&j, getcost(o, j)), Path(&p, getcost(o, p)), Path(&r, getcost(o, r)), Path(&n, getcost(o, n))};
        p.paths = vector<Path>{Path(&j, getcost(p, j)), Path(&k, getcost(p, k)), Path(&q, getcost(p, q)), Path(&r, getcost(p, r)), Path(&o, getcost(p, o))};
        q.paths = vector<Path>{Path(&k, getcost(q, k)), Path(&l, getcost(q, l)), Path(&m, getcost(q, m)), Path(&r, getcost(q, r)), Path(&p, getcost(q, p))};
        r.paths = vector<Path>{Path(&p, getcost(r, p)), Path(&q, getcost(r, q)), Path(&m, getcost(r, m)), Path(&n, getcost(r, n)), Path(&o, getcost(r, o))};

	s.paths = vector<Path>{Path(&e, getcost(s, e)), Path(&f, getcost(s, f)), Path(&k, getcost(s, k)), Path(&l, getcost(s, l))};

	Map testMap(width, height, vector<Node>{a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p, q, r, s});
	testMap.draw();
	
	int choice = -1;
	string getChoice ="";
	int fuel = 50;
	string error = "";
	bool isInt;
	string allInts = "0123456789";
	while (choice != 0) {
		testMap.draw();
		cout<<error<<"Fuel Level: "<<fuel<<"\nWhich location would you like to go to?\n";
		getline(cin, getChoice);
		for (int i = 0; i < getChoice.size(); i++) {
			isInt = false;
			for (int j = 0; j < allInts.size(); j++) {
				if (getChoice[i] == allInts[j]) {
					isInt = true;
					break;
				}
			}
			if (!isInt) break;
		}
		if (isInt) choice = atoi(getChoice.c_str());
		if (!isInt) {
			error = "Invalid input: Input must be an integer\n";
		} else if (choice > testMap.current.paths.size() || choice < 0) {
			error = "Invalid input: Input must be within range of options shown on map\n";
		} else if (choice > 0) {
			if (testMap.current.paths[choice-1].cost > fuel) {
				error = "Error: Insufficient fuel\n";
			} else {
				error = "";
				fuel -= testMap.current.paths[choice-1].cost;
				for (Node node: testMap.nodes) {
					if(testMap.current.paths[choice-1].connect == node) {
						testMap.current = node;
						break;
					}
				}
			}
		}
	}
}
