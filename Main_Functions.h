#define _CRT_SECURE_NO_WARNINGS
#define SIDE_LENGTH 35
#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"
#include "Cell.h"

int map_initializer(int* N, int*** Map, char*** Types, int*** Energy_Blocks) {
    FILE* fp = fopen("map.bin", "rb");
    if (fp == NULL) {
        printf("Cannot find the file\n");
        return -1;
    }
    fread(N, sizeof(int), 1, fp);
    int n = *N;

    *Map = (int**)malloc(n * sizeof(int*));
    for (int i = 0; i < n; i++) {
        (*Map)[i] = (int*)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            (*Map)[i][j] = 0;
        }
    }

    *Types = (char**)malloc(n * sizeof(char*));
    for (int i = 0; i < n; i++) {
        (*Types)[i] = (char*)malloc(n * sizeof(char));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fread(&((*Types)[i][j]), sizeof(char), 1, fp);
        }
    }

	*Energy_Blocks = (int**)malloc(n * sizeof(int*));
	for (int i = 0; i < n; i++) {
		(*Energy_Blocks)[i] = (int*)malloc(n * sizeof(int));
		for (int j = 0; j < n; j++) {
			if ((*Types)[i][j] == '1')
				(*Energy_Blocks)[i][j] = 100;
			else
				(*Energy_Blocks)[i][j] = 0;
		}
	}

    return n;
}

int* window_characteristics_generator(int n, int side_length) {
	int* window = (int*)malloc(2 * sizeof(int));
	window[0] = (int)(300 + side_length * (2 * (n + 1) - (float)(n - 1) / 2));
	window[1] = side_length * (2 * n + 3);
	return window;
}

int* hexagon_center_generator(int* window_characteristics, int x, int y, int side_length) {
	int* center = (int*)malloc(2 * sizeof(int));
	center[0] = (int)((2 * (x + 1) - (float)(x) / 2) * side_length);
	if (x % 2) {
		center[1] = window_characteristics[1] - (2 * (y + 1)) * side_length;
	}
	else {
		center[1] = window_characteristics[1] - (2 * y + 3) * side_length;
	}
	return center;
}

int* hexagon_vertices_generator(int* points, int* center, int side_length) {
	for (int i = 0; i < 2; i++) {
		points[2 * i] = points[2 * (6 - i)] = (int)(center[0] + ((float)(i) / 2 - 1) * side_length);
	}
	for (int i = 2; i < 4; i++) {
		points[2 * i] = points[2 * (6 - i)] = (int)(center[0] + ((float)(i - 1) / 2) * side_length);
	}
	for (int i = 0; i < 7; i += 3) {
		points[2 * i + 1] = center[1];
	}
	for (int i = 1; i < 3; i++) {
		points[2 * i + 1] = center[1] - side_length;
	}
	for (int i = 4; i < 6; i++) {
		points[2 * i + 1] = center[1] + side_length;
	}
	return points;
}

void hint_drawer(int* window) {
	circle(window[0] - 175, SIDE_LENGTH + 9, 15);
	setfillstyle(SOLID_FILL, GREEN);
	floodfill(window[0] - 175, SIDE_LENGTH + 9, WHITE);
	outtextxy(window[0] - 150, SIDE_LENGTH, "ENERGY");

	circle(window[0] - 175, 2 * SIDE_LENGTH + 9, 15);
	setfillstyle(SOLID_FILL, RED);
	floodfill(window[0] - 175, 2 * SIDE_LENGTH + 9, WHITE);
	outtextxy(window[0] - 150, 2 * SIDE_LENGTH, "MITOSIS");

	circle(window[0] - 175, 3 * SIDE_LENGTH + 9, 15);
	setfillstyle(SOLID_FILL, WHITE);
	floodfill(window[0] - 175, 3 * SIDE_LENGTH + 9, WHITE);
	outtextxy(window[0] - 150, 3 * SIDE_LENGTH, "FORBIDDEN");

	circle(window[0] - 175, 4 * SIDE_LENGTH + 9, 15);
	outtextxy(window[0] - 150, 4 * SIDE_LENGTH, "NORMAL");
}

void map_drawer(int n, int** map, char** types, int** energy_blocks, CELL* head) {

	cleardevice();

	setfillstyle(SOLID_FILL, BLACK);
	hint_drawer(window_characteristics_generator(n, SIDE_LENGTH));

	int color;
	int arr[14];
	int* window_characteristics = window_characteristics_generator(n, SIDE_LENGTH);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int* center = hexagon_center_generator(window_characteristics, i, j, SIDE_LENGTH);
			drawpoly(7, hexagon_vertices_generator(arr, center, SIDE_LENGTH));
			int energy = 0;
			switch (types[i][j])
			{
			case '1':
				color = GREEN;
				energy = 1;
				break;
			case '2':
				color = RED;
				break;
			case '3':
				color = WHITE;
				break;
			default:
				color = BLACK;
				break;
			}
			setfillstyle(SOLID_FILL, color);
			floodfill(center[0], center[1], WHITE);
			char energy_level[30];
			if (energy) {
				setbkcolor(color);
				outtextxy(center[0] - SIDE_LENGTH / 2, center[1] + SIDE_LENGTH / 3, itoa(energy_blocks[i][j], energy_level, 10));
			}
			if (map[i][j]) {
				CELL* temp = head;
				while (temp->x != i || temp->y != j) {
					temp = temp->next;
				}
				setbkcolor(color);
				outtextxy(center[0] - SIDE_LENGTH / 2, center[1] - 2 * SIDE_LENGTH / 3, temp->player);
				outtextxy(center[0], center[1] - 2 * SIDE_LENGTH / 3, itoa(temp->energy_level, energy_level, 10));
			}
			setbkcolor(BLACK);
		}
	}
}