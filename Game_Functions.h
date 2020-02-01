void Load(int n, int* NumOfCells, int*** Map, char** types, int*** Energy_Blocks, CELL** Head) {
	FILE* fp = fopen("Energy_Blocks.txt", "r");
	if (fp == NULL) {
		printf("Cannot find the file\n");
	}
	int Energy;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (types[i][j] == '1') {
				fscanf(fp, "%d", &Energy);
				(*Energy_Blocks)[i][j] = Energy;
			}
		}
	}
	fclose(fp);
	fp = fopen("Cells.txt", "r");
	if (fp == NULL) {
		printf("Cannot find the file\n");
	}
	int NOC, x, y, energy_level;
	char name[55];
	char player[55];
	fseek(fp, 0, SEEK_END);
	fscanf(fp, "%d", &NOC);
	fseek(fp, 0, SEEK_SET);
	CELL* head = (CELL*)malloc(sizeof(CELL));
	CELL* last = (CELL*)malloc(sizeof(CELL));
	for (int i = 0; i < NOC; i++) {
		fgets(player, 55, fp);
		fgets(name, 55, fp);
		fscanf(fp, " %d %d", &x, &y);
		fscanf(fp, "%d", &energy_level);
		CELL* temp = (CELL*)malloc(sizeof(CELL));
		strcpy(temp->name, name);
		strcpy(temp->player, player);
		(*Map)[x][y] = 1;
		temp->x = x;
		temp->y = y;
		temp->energy_level = energy_level;
		if (!i) {
			temp->previous = NULL;
			temp->next = NULL;
			head = temp;
		}
		else {
			last->next = temp;
			temp->previous = last;
			temp->next = NULL;
		}
		last = temp;
	}
	fclose(fp);
	*NumOfCells = NOC;
	*Head = head;
	initwindow(window_characteristics_generator(n, SIDE_LENGTH)[0], window_characteristics_generator(n, SIDE_LENGTH)[1], "GAME");
	map_drawer(n, *Map, types, *Energy_Blocks, *Head);
}

void Move(int n, int x, int y, int direction, int*** Map, char** types, CELL** Head, CELL** Temp) {
	/*
	1 North
	2 South
	3 Northeast
	4 Northwest
	5 Southeast
	6 Southwest
	*/
	CELL* temp = *Temp;
	if (x % 2) {
		switch (direction)
		{
		case 1:
			if (y + 1 < n && !(*Map)[x][y + 1] && types[x][y + 1] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->y++;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 2:
			if (y > 0 && !(*Map)[x][y - 1] && types[x][y - 1] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->y--;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 3:
			if (x + 1 < n && !(*Map)[x + 1][y] && types[x + 1][y] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->x++;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 4:
			if (x > 0 && !(*Map)[x - 1][y] && types[x - 1][y] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->x--;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 5:
			if (x + 1 < n && y > 0 && !(*Map)[x + 1][y - 1] && types[x + 1][y - 1] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->x++;
				temp->y--;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 6:
			if (x > 0 && y > 0 && !(*Map)[x - 1][y - 1] && types[x - 1][y - 1] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->x--;
				temp->y--;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		}
	}
	else {
		switch (direction)
		{
		case 1:
			if (y + 1 < n && !(*Map)[x][y + 1] && types[x][y + 1] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->y++;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 2:
			if (y > 0 && !(*Map)[x][y - 1] && types[x][y - 1] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->y--;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 3:
			if (x + 1 < n && y + 1 < n && !(*Map)[x + 1][y + 1] && types[x + 1][y + 1] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->x++;
				temp->y++;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 4:
			if (x > 0 && y + 1 < n && !(*Map)[x - 1][y + 1] && types[x - 1][y + 1] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->x--;
				temp->y++;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 5:
			if (x + 1 < n && !(*Map)[x + 1][y] && types[x + 1][y] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->x++;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		case 6:
			if (x > 0 && !(*Map)[x - 1][y] && types[x - 1][y] != '3') {
				(*Map)[temp->x][temp->y] = 0;
				temp->x--;
				(*Map)[temp->x][temp->y] = 1;
			}
			else
				temp->x += 0;
			break;
		}
	}
	while (temp->previous != NULL) {
		temp = temp->previous;
	}
	*Head = temp;
}

int check_movement(int n, int x, int y, int** map, char** types) {
	int possibilities[6] = { 0 };
	if (x % 2) {
		if (y + 1 < n && !map[x][y + 1] && types[x][y + 1] != '3')
			possibilities[0] = 1;
		else if (y > 0 && !map[x][y - 1] && types[x][y - 1] != '3')
			possibilities[1] = 1;
		else if (x + 1 < n && !map[x + 1][y] && types[x + 1][y] != '3')
			possibilities[2] = 1;
		else if (x > 0 && !map[x - 1][y] && types[x - 1][y] != '3')
			possibilities[3] = 1;
		else if (x + 1 < n && y > 0 && !map[x + 1][y - 1] && types[x + 1][y - 1] != '3')
			possibilities[4] = 1;
		else if (x > 0 && y > 0 && !map[x - 1][y - 1] && types[x - 1][y - 1] != '3')
			possibilities[5] = 1;
		else
			return 0;
	}
	else {
		if (y + 1 < n && !map[x][y + 1] && types[x][y + 1] != '3')
			possibilities[0] = 1;
		else if (y > 0 && !map[x][y - 1] && types[x][y - 1] != '3')
			possibilities[1] = 1;
		else if (x + 1 < n && y + 1 < n && !map[x + 1][y + 1] && types[x + 1][y + 1] != '3')
			possibilities[2] = 1;
		else if (x > 0 && y + 1 < n && !map[x - 1][y + 1] && types[x - 1][y + 1] != '3')
			possibilities[3] = 1;
		else if (x + 1 < n && !map[x + 1][y] && types[x + 1][y] != '3')
			possibilities[4] = 1;
		else if (x > 0 && !map[x - 1][y] && types[x - 1][y] != '3')
			possibilities[5] = 1;
		else
			return 0;
	}
	time_t t = time(NULL);
	srand(t);
	int direction;
	do
	{
		direction = rand() % 6 + 1;
	} while (!possibilities[direction - 1]);
	return direction;
}

void Split(int n, int x, int y, int*** Map, char** types, CELL** Head, CELL** Temp) {
	CELL* temp = *Temp;
	if (types[x][y] == '2' && check_movement(n, x, y, *Map, types) && temp->energy_level >= 80) {
		Move(n, x, y, check_movement(n, x, y, *Map, types), Map, types, Head, Temp);
		temp->energy_level = 40;
		printf("Enter the new cell name:\n");
		scanf("%s", temp->name);
		CELL* TEMP = (CELL*)malloc(sizeof(CELL));
		TEMP->x = x;
		TEMP->y = y;
		TEMP->energy_level = 40;
		strcpy(TEMP->player, temp->player);
		printf("Enter the new cell name:\n");
		scanf("%s", TEMP->name);
		if (temp->NumOfCells - 1) {
			temp->previous->next = TEMP;
			TEMP->previous = temp->previous;
			temp->previous = TEMP;
			TEMP->next = temp;
		}
		else {
			temp->previous = TEMP;
			TEMP->next = temp;
			TEMP->previous = NULL;
		}
		(*Map)[x][y] = 1;
	}
	while (temp->previous != NULL) {
		temp = temp->previous;
	}
	*Head = temp;
}

void Boost_Energy(int x, int y, int*** Energy_Blocks, CELL** Head, CELL** Temp) {
	CELL* temp = *Temp;
	if ((*Energy_Blocks)[x][y] >= 15 && temp->energy_level <= 85) {
		temp->energy_level += 15;
		(*Energy_Blocks)[x][y] -= 15;
	}
	else if ((*Energy_Blocks)[x][y] <= 15 && temp->energy_level + *Energy_Blocks[x][y] <= 100) {
		temp->energy_level += (*Energy_Blocks)[x][y];
		(*Energy_Blocks)[x][y] = 0;
	}
	while (temp->previous != NULL) {
		temp = temp->previous;
	}
	*Head = temp;
}

void Save(int n, char** types, int** energy_blocks, CELL* head) {
	FILE* fp = fopen("Energy_Blocks.txt", "w");
	if (fp == NULL) {
		printf("Cannot create the file\n");
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (types[i][j] == '1') {
				fprintf(fp, "%d\n", energy_blocks[i][j]);
			}
		}
	}
	fclose(fp);
	fp = fopen("Cells.txt", "w");
	if (fp == NULL) {
		printf("Cannot create the file\n");
	}
	int NOC = 0;
	for (CELL* temp = head; temp != NULL; temp = temp->next) {
		fputs(temp->player, fp);
		fprintf(fp, " ");
		fputs(temp->name, fp);
		fprintf(fp, " %d %d\n%d\n", temp->x, temp->y, temp->energy_level);
		NOC++;
	}
	fprintf(fp, "%d\n", NOC);
	fclose(fp);
}