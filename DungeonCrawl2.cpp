#include <iostream>
#include <ctime>

//constants
const int ROW = 9;
const int COL = 12;

const char BOUNDARY = '+';
const char CAUGHT = '!';
const char EMPTY = ' ';
const char ENEMY = 'E';
const char PLAYER = 'P';
const char TRAP = 'T';
const char TREASURE = 'X';


using namespace std;
//functions
void display_board(char (*ar)[ROW][COL], bool (*bar)[ROW][COL]);
void new_game(char(*ar)[ROW][COL], bool(*bar)[ROW][COL], int * player_row, int * player_col, int * treasure_row, int * treasure_col, int * trap_row, int * trap_col, int * enemy_row, int * enemy_col, char * endGame);
void move_player(char(*ar)[ROW][COL], bool(*bar)[ROW][COL], int * player_row, int * player_col, int * treasure_row, int * treasure_col, int * enemy_row, int * enemy_col);
void move_enemy(char(*ar)[ROW][COL], bool(*bar)[ROW][COL], int * player_row, int * player_col, int * treasure_row, int * treasure_col, int * enemy_row, int * enemy_col);
bool end_game(const char endGame);

//board and pieces
char game_board[ROW][COL];
char endGame;
bool b_board[ROW][COL];//false == gamefield/true = boundary
int player_row, player_col, treasure_row, treasure_col, trap_row, trap_col, enemy_row, enemy_col;

int main()
{
	new_game(&game_board, &b_board, &player_row, &player_col, &treasure_row, &treasure_col, &trap_row, &trap_col, &enemy_row, &enemy_col, &endGame);
	while (!(end_game(endGame)))
	{
		move_player(&game_board, &b_board, &player_row, &player_col, &treasure_row, &treasure_col, &enemy_row, &enemy_col);
		move_enemy(&game_board, &b_board, &player_row, &player_col, &treasure_row, &treasure_col, &enemy_row, &enemy_col);
		//display_board(&game_board, &b_board);
	}
	//display_board(&game_board, &b_board);
}

void display_board(char(*ar)[ROW][COL], bool (*bar)[ROW][COL])	//+++++++++	0
{																//+       + 1
	for (int i = 0; i < ROW; i++)								//+       + 2
	{
		for (int ii = 0; ii < COL; ii++)
			cout << (*ar)[i][ii];
		cout << endl;
	}
	cout << endl;
	/*for (int i = 0; i < ROW; i++)								//+       + 2
	{
		for (int ii = 0; ii < COL; ii++)
			cout << (*bar)[i][ii];
		cout << endl;
	}*/
}

void new_game(char(*ar)[ROW][COL], bool(*bar)[ROW][COL], int * player_row, int * player_col, int * treasure_row, int * treasure_col, int * trap_row, int * trap_col, int * enemy_row, int * enemy_col, char * endGame)
{
	//set gameboard playspace
	for (int i = 1; i < ROW - 1; i++)
		for (int ii = 1; ii < COL - 1; ii++)
		{
			game_board[i][ii] = EMPTY;
			b_board[i][ii] = false;
		}
	//set gameboard boundaries
	for (int i = 0; i < ROW; i++)
		for (int ii = 0; ii < COL; ii++)
			if (0 == i || ROW - 1 == i || 0 == ii || COL - 1 == ii)
			{
				game_board[i][ii] = BOUNDARY;
				b_board[i][ii] = true;
			}

	//set player start position
	srand((unsigned int)time(NULL));
	*player_row = 1;
	*player_col = rand() % (COL - 2) + 1;
	game_board[*player_row][*player_col] = PLAYER;

	//set treasure location
	*treasure_row = (ROW - 2);
	*treasure_col = *player_col;//for testing ONLY. DELETE THIS!!!
	//*treasure_col = rand() % (COL - 2) + 1;//ENABLE THIS!1!
	game_board[*treasure_row][*treasure_col] = TREASURE;

	//set trap locations
	int trap_count = 3;
	for (int i = 0; i < trap_count; i++)
	{
		bool isEmpty = true;
		while (isEmpty == true)
		{
			*trap_row = rand() % (ROW - 2) + 1;
			//*trap_col = *player_col;//TESTING ONLY> DELETE THIS!!!
			*trap_col = rand() % (COL - 2) + 1;
			if (game_board[*trap_row][*trap_col] != EMPTY)
				continue;
			game_board[*trap_row][*trap_col] = TRAP;
			isEmpty = false;
		}
	}

	//set enemy locations
	int enemy_count = 1;
	for (int i = 0; i < enemy_count; i++)
	{
		bool isEmpty = true;
		while (isEmpty == true)
		{
			*enemy_row = rand() % (ROW - 2) + 1;
			//*enemy_col = *player_col;//testing ONLY...DELETE
			*enemy_col = rand() % (COL - 2) + 1;
			if (game_board[*enemy_row][*enemy_col] != EMPTY)
				continue;
			game_board[*enemy_row][*enemy_col] = ENEMY;
			isEmpty = false;
		}
	}
	
	*endGame = '0';//set Game over status
	display_board(ar, bar);
}

void move_player(char(*ar)[ROW][COL], bool(*bar)[ROW][COL], int * player_row, int * player_col, int * treasure_row, int * treasure_col, int * enemy_row, int * enemy_col)
{
	char move = '0';
	cout << "Please make a move\n";
	cin.get(move);//only one move at a time
	cin.clear();
	while (cin.get() != '\n')
		continue;

	switch (move)
	{
	case 'W':
	case 'w':
		if ((*bar)[*player_row - 1][*player_col] == false)
		{
			game_board[*player_row][*player_col] = EMPTY;
			*player_row -= 1;
			break;
		}
		else
		{
			move_player(&game_board, &b_board, player_row, player_col, treasure_row, treasure_col, enemy_row, enemy_col);
			break;
		}
	case 'S':
	case 's'://down
		if ((*bar)[*player_row + 1][*player_col] == false)
		{
			game_board[*player_row][*player_col] = EMPTY;
			*player_row += 1;
			break;
		}
		else
		{
			move_player(&game_board, &b_board, player_row, player_col, treasure_row, treasure_col, enemy_row, enemy_col);
			break;
		}
	case 'A':
	case 'a':
		if ((*bar)[*player_row][*player_col - 1] == false)
		{
			game_board[*player_row][*player_col] = EMPTY;
			*player_col -= 1;
			break;
		}
		else
		{
			move_player(&game_board, &b_board, player_row, player_col, treasure_row, treasure_col, enemy_row, enemy_col);
			break;
		}
	case 'D':
	case 'd':
		if ((*bar)[*player_row][*player_col + 1] == false)
		{
			game_board[*player_row][*player_col] = EMPTY;
			*player_col += 1;
			break;
		}
		else
		{
			move_player(&game_board, &b_board, player_row, player_col, treasure_row, treasure_col, enemy_row, enemy_col);
			break;
		}
	}
	
	//check if player moved into the treasure or some other obstacle
	switch (game_board[*player_row][*player_col])
	{
	case ENEMY:
		game_board[*player_row][*player_col] = CAUGHT;
		endGame = ENEMY;
		break;
	case TRAP: 
		game_board[*player_row][*player_col] = CAUGHT;
		endGame = TRAP;
		break;
	case TREASURE:
		game_board[*player_row][*player_col] = 'W';
		endGame = TREASURE;
		break;
	default:
		game_board[*player_row][*player_col] = PLAYER;
	}
	
	display_board(&game_board, &b_board);
}

void move_enemy(char(*ar)[ROW][COL], bool(*bar)[ROW][COL], int * player_row, int * player_col, int * treasure_row, int * treasure_col, int * enemy_row, int * enemy_col)
{
	cout << "Enemy Move\n";
	bool enemy_moved = false;
	while (enemy_moved == false)
	{
		srand((unsigned int)time(NULL));
		int enemy_move = rand() % 4 + 1;
		switch (enemy_move)
		{
		case 1://up
			if ((*bar)[*enemy_row - 1][*enemy_col] == false && (game_board[*enemy_row - 1][*enemy_col] == PLAYER || game_board[*enemy_row - 1][*enemy_col] == EMPTY))
			{
				game_board[*enemy_row][*enemy_col] = EMPTY;
				*enemy_row -= 1;
				enemy_moved = true;
				break;
			}
			else continue;
		case 2://down
			if ((*bar)[*enemy_row + 1][*enemy_col] == false && (game_board[*enemy_row + 1][*enemy_col] == PLAYER || game_board[*enemy_row + 1][*enemy_col] == EMPTY))
			{
				game_board[*enemy_row][*enemy_col] = EMPTY;
				*enemy_row += 1;
				enemy_moved = true;
				break;
			}
			else continue;
		case 3://left
			if ((*bar)[*enemy_row][*enemy_col - 1] == false && (game_board[*enemy_row][*enemy_col - 1] == PLAYER || game_board[*enemy_row][*enemy_col - 1] == EMPTY))
			{
				game_board[*enemy_row][*enemy_col] = EMPTY;
				*enemy_col -= 1;
				enemy_moved = true;
				break;
			}
			else continue;
		case 4://right
			if ((*bar)[*enemy_row][*enemy_col + 1] == false && (game_board[*enemy_row][*enemy_col + 1] == PLAYER || game_board[*enemy_row][*enemy_col + 1] == EMPTY))
			{
				game_board[*enemy_row][*enemy_col] = EMPTY;
				*enemy_col += 1;
				enemy_moved = true;
				break;
			}
			else continue;
		}
	}
	game_board[*enemy_row][*enemy_col] = ENEMY;
	if (game_board[*enemy_row][*enemy_col] == PLAYER)
	{
		game_board[*enemy_row][*enemy_col] = CAUGHT;
		end_game(ENEMY);
	}
	display_board(&game_board, &b_board);
}

bool end_game(const char endGame)
{
	switch (endGame)
	{
	case ENEMY:
		cout << "\aYou were caught by an enemy!\nGAME OVER\n";
		return true;
	case TRAP: 
		cout << "\aYou were caught in a trap!\nGAME OVER\n";
		return true;
	case TREASURE:
		cout << "\aYou found the treasure!\n";
		return true;
	default: 
		return false;
	}
}