/*Othello game*/
/*Author: Jon Skerlj*/


#include <iostream>
#include <string>

using namespace std;

int check_move(char board[6][6], char player, int row, int col);
int check_board(char board[6][6], char player);
int update_board(char board[6][6], char player, int row, int col);
void print_board(char board[6][6]);
void print_score(char board[6][6]);

int main()
{
	// setup your data
	char player = ' ';
	char opponent = ' ';
	char board[6][6];
	int move_state = 0;
	int board_state = 0;
	string str_input;
	int row;
	int col;
	
	// initialise the board
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			board[i][j] = ' ';
			
	board[2][2] = 'O';
	board[3][3] = 'O';
	board[2][3] = 'X';
	board[3][2] = 'X';
	
	// Welcome screen
	cout << endl;
	cout << "---- REVERSI ----" << endl;
	cout << endl;
	
	// Print initial board
	print_board(board);
	cout << endl;
	
	// Select the first player
	player = 'O';
	opponent = 'X';
	
	// The game begins
	do
	{
		// Ask the current player to select a position
		do
		{
			cout << " Player " << player << ", enter a row and column (eg, e3): ";
			cin >> str_input;
			
			row = int(str_input[0] - 'a');
			col = int(str_input[1] - '1');
		
			move_state = check_move(board, player, row, col);
			
			if (move_state == -1)
			{
				cout << " Disk must be placed on the board." << endl;
			}
			else if (move_state == -2)
			{
				cout << " Disk must be placed on an empty spot." << endl;
			}
			else if (move_state == -3)
			{
				cout << " Disk must be placed next to an opponent's disk." << endl;
			}
			else if (move_state == -4)
			{
				cout << " Disk must be able to flip an opponent's disk." << endl;
			}
		
		} while(move_state < 0);
		cout << endl;
		
		// Place the move and update the board
		update_board(board, player, row, col);
		
		// Print the board
		print_board(board);
		cout << endl;
		
		// Swap player
		if (player == 'O')
			player = 'X';
		else
			player = 'O';
		
		board_state = check_board(board, player);
		
		if (board_state == 1)
		{
			;
		}
		else if (board_state == 2)
		{
			cout << " Player " << player << " does not have a move to play." << endl;
			cout << endl;
			if (player == 'O')
				player = 'X';
			else
				player = 'O';
		}
	
	} while(board_state > 0);

	print_score(board);

	return 0;
}


int check_move(char board[6][6], char player, int row, int col)
// 1 : valid move
// -1: out of bounds
// -2: spot taken
// -3: disk must be placed next to an opponent's disk
// -4: disk must be able to flip an opponent's disk
{
	bool b_near_opp = false;
	bool b_flip_opp = false;
	int num_opponent_disks = 0;
	char opponent;
	
	if (player == 'O')
		opponent = 'X';
	else
		opponent = 'O';


	// (1/4) move must be within the board boundaries
	if (row >= 0 && row < 6 && col >= 0 && col < 6)
	{
		;
	}
	else
	{
		
		return -1;
	}

	// (2/4) move must be in an empty spot
	if (board[row][col] != ' ')
	{
		
		return -2;
	}
	
	// (3/4) move must adjacent to an opponent's disk
	for (int i=-1; i <= 1; i++)
	{
		if (row+i >= 0 && row+i < 6)
		{
			for (int j=-1; j <= 1; j++)
			{
				if (col+j >= 0 && col+j < 6)
				{	
					if (board[row+i][col+j] == opponent)
						b_near_opp = true;
				}
			}
		}
	}
	
	if (b_near_opp == false)
	{
		
		return -3;
	}
	
	// (4/4) player's disk should be on opposite end of the opponent's disk
	// loop through all neighbouring disks
	// if there is an opponent disk, then scan for a disk at the opposite end
	for (int i=-1; i <= 1; i++)
	{
		if (row+i >= 0 && row+i < 6)
		{
			for (int j=-1; j <= 1; j++)
			{
				if (col+j >= 0 && col+j < 6)
				{	
					if (board[row+i][col+j] == opponent)
					{
						// scan for a disk at the opposite end
						
						// if j = -1, then scan columns leftwards
						// if j = 0, then scan same column
						// if j = +1, then scan columns rightwards
						// if i = -1, then scan row upwards
						// if i = 0, then scan same row
						// if i = +1, then scan row downwards
						
						int m = i+i;
						int n = j+j;
						
						// from (row, col) add i and add j until board edge
						// or until player's piece is found
						
						while (row+m >= 0 && row+m < 6 && col+n >= 0 && col+n < 6)
						{
							
							if (board[row+m][col+n] == player)
							{
								//cout << " Opponent flippable" << endl;
								b_flip_opp = true;
								break;
							}
							else if (board[row+m][col+n] == ' ')
							{
								break;
							}
							else
							{
								m += i;
								n += j;
							}
						
						}
					}
				}
			}
		}
	}

	if (b_flip_opp == false)
	{
		
		return -4;
	}	

	return 1;
}

int check_board(char board[6][6], char player)
// 2: player can't move, hand over to opponent (ie., swap player)
// 1: player's move
// 0: game over
{
	bool b_spot_empty = false;
	bool b_valid_move = false;
	char opponent = ' ';
	
	if (player == 'O')
		opponent = 'X';
	else
		opponent = 'O';

	// check whether the board is full - if full, game over
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			if (board[i][j] == ' ')
				b_spot_empty = true;
	
			
	// check whether there is a valid move for the player - if no, check whether there is a valid move for the opponent
	if (b_spot_empty == true)
	{
	
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
			{
				if (check_move(board, player, i, j) > 0)
				{
					b_valid_move = true;
					return 1;
				}
			}
	
		for (int i = 0; i < 6; i++)
			for (int j = 0; j < 6; j++)
			{
				if (check_move(board, opponent, i, j) > 0)
				{
					b_valid_move = true;
					return 2;
				}
			}
	}
	
	return 0;
}

int update_board(char board[6][6], char player, int row, int col)
{
	bool b_flip_opp = false;

	char opponent;
	
	if (player == 'O')
		opponent = 'X';
	else
		opponent = 'O';
		
		
	board[row][col] = player;

	for (int i=-1; i <= 1; i++)
	{
		if (row+i >= 0 && row+i < 6)
		{
			for (int j=-1; j <= 1; j++)
			{
				if (col+j >= 0 && col+j < 6)
				{	
					if (board[row+i][col+j] == opponent)
					{
						// scan for a disk at the opposite end
						
						int m = i+i;
						int n = j+j;
						
						b_flip_opp = false;
						
						// from (row, col) add i and add j until board edge
						// or until player's piece is found
						
						while (row+m >= 0 && row+m < 6 && col+n >= 0 && col+n < 6)
						{
							
							if (board[row+m][col+n] == player)
							{
								//cout << " Opponent flippable" << endl;
								b_flip_opp = true;
								break;
							}
							else if (board[row+m][col+n] == ' ')
							{
								break;
							}
							else
							{
								m += i;
								n += j;
							}
						
						}
						
						if (b_flip_opp == true)
						{
							m = i;
							n = j;
						
							do
							{
								board[row+m][col+n] = player;
								m += i;
								n += j;
							} while (board[row+m][col+n] != player);	
						}
						
					}
				}
			}
		}
	}


	return 0;	// 0: game continues, 1: player O wins, 2: player 2 wins, -1: tie
}

void print_board(char board[6][6])
{
	cout << "   1 2 3 4 5 6" << endl;
	for (int i = 0; i < 6; i++)
	{
		cout << "  -------------" << endl;
		cout << (char)('a' + i) << ' ';
		for (int j = 0; j < 6; j++)
			cout << '|' << board[i][j];
		cout << '|' << endl;
	}
	cout << "  -------------" << endl;
}

void print_score(char board[6][6])
{
	int pO_score = 0;
	int pX_score = 0;

	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++)
			if (board[i][j] == 'O')
				pO_score++;
			else if (board[i][j] == 'X')
				pX_score++;

	if (pO_score > pX_score)
	{
		cout << " Player O wins! " << endl;
	}
	else if (pO_score < pX_score)
	{
		cout << " Player X wins! " << endl;
	}
	else if (pO_score == pX_score)
	{
		cout << " Game tied! " << endl;
	}
	
	cout << endl;
	cout << "----- SCORE -----" << endl;
	cout << " Player O: " << pO_score << endl;
	cout << " Player X: " << pX_score << endl;
	cout << endl;

}
