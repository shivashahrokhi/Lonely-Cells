#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Main_Functions.h"

void start_with_one_player(int n, int* NumOfCells, int*** Map, char** types, int** energy_blocks, CELL** Head) {
    printf("Have many cells do you want to have?\n");
    scanf("%d", NumOfCells);
    int NOC = *NumOfCells;
    CELL* last = (CELL*)malloc(sizeof(CELL));
    time_t Time = time(NULL);
    srand(Time);
    int x, y;
    for (int i = 0; i < NOC; i++) {
        do {
            x = rand() % n;
            y = rand() % n;
        } while ((*Map)[x][y] == 1 || types[x][y] == '3');
        (*Map)[x][y] = 1;
        CELL* temp = (CELL*)malloc(sizeof(CELL));
        temp->x = x;
        temp->y = y;
        temp->NumOfCells = NOC;
        temp->energy_level = 0;
        strcpy(temp->player, "A");
        printf("Enter the new cell name:\n");
        scanf("%s", temp->name);
        if (!i) {
            temp->previous = NULL;
            temp->next = NULL;
            *Head = temp;
        }
        else {
            last->next = temp;
            temp->previous = last;
            temp->next = NULL;
        }
        last = temp;
    }
    initwindow(window_characteristics_generator(n,SIDE_LENGTH)[0], window_characteristics_generator(n, SIDE_LENGTH)[1], "GAME");
    map_drawer(n, *Map, types, energy_blocks, *Head);
}
