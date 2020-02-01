#include "MonoPlayer.h"
#include "Game_Functions.h"

void Show_Main_Menu(void) {
	printf("[1]Load\n[2]New single player game\n[3]New multiplayer game\n[4]Exit\n");
}

void Show_Play_Menu(void) {
	printf("[1]Move\n[2]Split a cell\n[3]Boost energy\n[4]Save\n[5]Exit\n");
}

void Show_Move_Menu(void) {
	printf("[1]North\n[2]South\n[3]Northeast\n[4]Northwest\n[5]Southeast\n[6]Southwest\n");
}

void Play_Menu(int x, int y, int* Play, int OPTION, int n, int* NumOfCells, int*** Map, char** types, int*** Energy_Blocks, CELL** Head, CELL** Temp) {
	/*
	1 Move
	2 Split a cell
	3 Boost energy
	4 Save
	5 Exit
	*/
	switch (OPTION) {
	case 1:
		Show_Move_Menu();
		int direction;
		scanf("%d", &direction);
		Move(n, x, y, direction, Map, types, Head, Temp);
		map_drawer(n, *Map, types, *Energy_Blocks, *Head);
		break;
	case 2:
		Split(n, x, y, Map, types, Head, Temp);
		map_drawer(n, *Map, types, *Energy_Blocks, *Head);
		break;
	case 3:
		Boost_Energy(x, y, Energy_Blocks, Head, Temp);
		map_drawer(n, *Map, types, *Energy_Blocks, *Head);
		break;
	case 4:
		Save(n, types, *Energy_Blocks, *Head);
		closegraph();
		*Play = 0;
		break;
	case 5:
		*Play = 0;
		break;
	}
}

void Main_Menu(int* Play, int option, int* N, int* NumOfCells, int*** Map, char*** Types, int*** Energy_Blocks, CELL** Head) {
	/*
	1 Load
	2 New single player game
	3 New multiplayer game
	4 Exit
	*/
	switch (option) {
	case 1:
		*N = map_initializer(N, Map, Types, Energy_Blocks);
		Load(*N, NumOfCells, Map, *Types, Energy_Blocks, Head);
		*Play = 1;
		while (*Play) {
			int x, y, Error;
			CELL* temp;
			do
			{
				Error = 0;
				printf("Enter cell coordinates:\n");
				scanf("%d %d", &x, &y);
				temp = *Head;
				while (temp->x != x || temp->y != y) {
					if (temp->next != NULL)
						temp = temp->next;
					else {
						Error = 1;
						break;
					}
				}
			} while (Error);
			Show_Play_Menu();
			int OPTION;
			scanf("%d", &OPTION);
			Play_Menu(x, y, Play, OPTION, *N, NumOfCells, Map, *Types, Energy_Blocks, Head, &temp);
		}
		break;
	case 2:
		*N = map_initializer(N, Map, Types, Energy_Blocks);
		start_with_one_player(*N, NumOfCells, Map, *Types,*Energy_Blocks,Head);
		*Play = 1;
		while (*Play) {
			int x, y, Error;
			CELL* temp;
			do
			{
				Error = 0;
				printf("Enter cell coordinates:\n");
				scanf("%d %d", &x, &y);
				temp = *Head;
				while (temp->x != x || temp->y != y) {
					if (temp->next != NULL)
						temp = temp->next;
					else {
						Error = 1;
						break;
					}
				}
			} while (Error);
			Show_Play_Menu();
			int OPTION;
			scanf("%d", &OPTION);
			Play_Menu(x, y, Play, OPTION, *N, NumOfCells, Map, *Types, Energy_Blocks, Head, &temp);
		}
		break;
	case 3:
		//start_with_two_players();
		break;
	case 4:
		exit(0);
		break;
	}
}