#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "Menues.h"

int main()
{
    CELL* head;
	char** types;
	int** map;
	int** energy_blocks;
	int n, NumOfCells, play;
	
	while (true) {
		Show_Main_Menu();
		int option;
		scanf("%d", &option);
		Main_Menu(&play, option, &n, &NumOfCells, &map, &types, &energy_blocks, &head);
	}

	return 0;
}