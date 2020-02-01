#ifndef CELL_H
#define CEEL_H

struct cell {
	char player[10];
	char name[55];
	int x;
	int y;
	int NumOfCells;
	int energy_level;
	struct cell* previous;
	struct cell* next;
};
typedef struct cell CELL;

#endif