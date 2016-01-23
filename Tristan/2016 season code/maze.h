#ifndef MAZE_h
#define MAZE_H

#define MAPWIDTH 324
#define MAPLENGTH 324


struct mapstruct {
	int width;
	int length;
	bool walls[MAPWIDTH][MAPLENGTH];
};




#endif

