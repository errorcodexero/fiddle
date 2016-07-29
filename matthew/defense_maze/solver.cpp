#include <iostream>
#include <vector>

#define WIDTH 4
#define HEIGHT 3

enum Object {NONE, BLOCK};

struct Point {
	int x, y;
};

struct PointPair {
	Point location, previous;
	bool visited;
};

bool operator==(Point p1, Point p2) { return p1.x == p2.x && p1.y == p2.y; }
bool operator!=(Point p1, Point p2) { return !(p1 == p2); }

std::vector<Point> getAccessiblePoints(int maze[HEIGHT][WIDTH], Point p) {
	std::vector<Point> accessible;
	for (int i = 0; i < 4; i++) {
		Point newP = {p.x + (i == 0 ? 1 : (i == 2 ? -1 : 0)), p.y + (i==1 ? 1 : (i==3 ? -1 : 0))};
		if (newP.x >= 0 && newP.y >= 0 && newP.x < WIDTH && newP.y < HEIGHT && maze[newP.y][newP.x] == NONE) accessible.push_back(newP);
	}
	return accessible;
}

int pointIndex(std::vector<PointPair> point_list, Point p) {
	for (unsigned i = 0; i < point_list.size(); i++) if (point_list[i].location == p) return i;
	return -1;
}

bool containsVisitedPoint(std::vector<PointPair> point_list, Point p) {
	return pointIndex(point_list, p) != -1;
}

bool visit(Point current, Point end, std::vector<PointPair> &point_list, int maze[HEIGHT][WIDTH]) {
	if (current == end) return true;
	point_list[pointIndex(point_list, current)].visited = true;
	std::vector<Point> accessible = getAccessiblePoints(maze, current);
	for (unsigned i = 0; i < accessible.size(); i++) {
		if (!containsVisitedPoint(point_list, accessible[i])) {
			point_list.push_back({accessible[i], current, false});
			if (visit(accessible[i], end, point_list, maze)) return true;
		}
	}
	return false;
}

int main() {
	int maze[HEIGHT][WIDTH] = {{NONE, BLOCK, BLOCK, NONE},
	                           {NONE, BLOCK, BLOCK, NONE},
	                           {NONE, NONE, NONE, NONE}};
	Point start = {0, 0}, end = {3, 0};
	std::vector<PointPair> point_list;
	point_list.push_back({start, start, false});
	visit(start, end, point_list, maze);
	std::vector<Point> path;
	Point current = end;
	path.push_back(current);
	while (current != start) {
		current = point_list[pointIndex(point_list, current)].previous;
		path.push_back(current);
	}
	for (int i = path.size() - 1; i >= 0; i--) {
		std::cout<<"Step "<<path.size() - i<<": ("<<path[i].x<<", "<<path[i].y<<")"<<std::endl;
	}
	return 0;
}
