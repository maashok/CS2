#include "metaboard.hpp"
#include <iostream>
using namespace std;

/**
 * @brief Constructs a new metaboard which is a 2-D array of Boards.
 *
 * @param None
 *
 * @return None
 */
MetaBoard::MetaBoard() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			metaboard[i][j] = new Board();
		}
	}
	// Before the active board is set, or if there are no legal moves
	// in the current active board, it is set to -1.
	activeBoardRow = -1;
	activeBoardCol = -1;
}

/**
 * @brief Destructs the game by deleting the memory allocated for
 * each of the boards in the metaboard
 *
 * @param None
 *
 * @return None
 */
MetaBoard::~MetaBoard() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			metaboard[i][j]->~Board();
		}
	}
}

/**
 * @brief Checks if either player has won a game of meta-tic-tac-toe.
 * For this to happen, either player must have a 3-in-a-row
 * of boards marked with their piece (meaning they had a 3-in-a-row
 * first in that board)
 *
 * @param None
 *
 * @return Returns which player has won. Returns 1 if player 1 (using X)
 * has won, 2 if player 2 (using O) has won, or 0 if neither player has
 * won yet
 */
int MetaBoard::CheckWin() {
	// Stores if any player has a 3-in-a-row
	char rowWin = checkRows();
	char colWin = checkCols();
	char diagWin = checkDiags();
	
	// If any of the row, col, or diag Wins was from X pieces return 1
	if (rowWin == 'X' || colWin == 'X' || diagWin == 'X')
		return 1;
	// If any of the row, col, or diag Wins was from  O pieces return 2
	else if (rowWin == 'O' || colWin == 'O' || diagWin == 'O')
		return 2;
	// If there are no legal moves left, whichever player has marked
	// more boards wins
	if (isAllFull()) {
		if (whatWhenFull() == 1) return 1;
		else if (whatWhenFull() == 2) return 2;
	}
	return 0;
}

/**
 * @brief Checks if the game of meta-tic-tac-toe has ended in a draw.
 * This happens if there are no legal moves left on any of the boards,
 * and both player have marked an equal number of boards.
 *
 * @param None
 *
 * @return Returns a boolean specifying whether the game has ended in
 * a draw.
 */
bool MetaBoard::CheckDraw() {
	if (isAllFull()) {
		if (whatWhenFull() == 0) {
			return true;
		}
	}
	return false;
}

/**
 * @brief Checks if some board of the metaboard is full and has no 
 * legal moves left.
 *
 * @param Takes in the row and col, representing which board of the 
 * metaboard we are checking is full or not.
 *
 * @return Returns a boolean representing whether than specific board
 * is full
 */
bool MetaBoard::isFull(int row, int col) {
	return metaboard[row][col]->isFull();
}

/**
 * @brief Checks if the whole metaboard is full, meaning each of the 9
 * boards is full.
 *
 * @param None
 *
 * @return Returns a boolean representing whether there are no legal
 * moves left on the entire board
 */
bool MetaBoard::isAllFull() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (!metaboard[i][j]->isFull()) return false;
		}
	}
	return true;
}

/**
 * @brief Checks what the behavior should be if the entire metaboard
 * is full. If either player has marked more boards, that player has
 * won. If neither player has marked more boards, it is a draw.
 *
 * @param None
 *
 * @return Returns an integer representing what has happened. If player
 * 1 has won, returns a 1. If player 2 has won, returns a 2. If it is a
 * draw, returns 0.
 */
int MetaBoard::whatWhenFull() {
	// Makes a count of how many boards each player has marked
	int numX = 0, numO = 0;
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (metaboard[i][j]->won == 'X') numX ++;
			if (metaboard[i][j]->won == 'O') numO ++;
		}
	}
	if (numX == numO)
		return 0;
	else if (numX > numO) 
		return 1;
	else 
		return 2;
}

/**
 * @brief Places a game piece on a specified row and column on the 
 * active board.
 *
 * @param Takes in x, y, and piece, representing the row and column
 * number (from 1 to 3) of what square to place the piece on, and what
 * piece to place itself (X or O).
 *
 * @return Returns a boolean representing whether the placing of
 * the game piece was successful. It is not successful if that specified
 * location is not already empty.
 */
 bool MetaBoard::Place(int x, int y, char piece) {
	bool worked = 
	metaboard[activeBoardRow][activeBoardCol]->Place(x, y, piece,
	activeBoardRow, activeBoardCol);
	if (!worked) return false;
	activeBoardRow = x - 1;
	activeBoardCol = y - 1;
	//If the now active board has no legal moves, change the active
	// board to unspecified, or -1.
	if (metaboard[activeBoardRow][activeBoardCol]->isFull()) {
		activeBoardRow = -1;
		activeBoardCol = -1;
	}
	return true;
}

/**
 * @brief Checks the rows to see if either player has a 3-in-a-row
 * through a row.
 *
 * @param None
 *
 * @return Returns a char representing the player who has a 3-in-a-row
 * in a row. The char returned is 'X' if player 1 has a 3-in-a-row in
 * some row, 'O' if player 2 does, or ' ' if neither player does.
 */
char MetaBoard::checkRows() {
	for (int i = 0; i < SIZE; i++) {
		// Checks if X has marked any 3 boards in a row
		if (metaboard[i][0]->won == 'X' && metaboard[i][1]->won == 'X' 
		&& metaboard[i][2]->won == 'X') {
			return 'X';
		}
		// Checks if O has marked any 3 boards in a row
		else if(metaboard[i][0]->won == 'O' && metaboard[i][1]->won=='O'
		&& metaboard[i][2]->won == 'O') {
			return 'O';
		}
	}
	return ' ';
}

/**
 * @brief Checks the columns to see if either player has a 3-in-a-row
 * through a column.
 *
 * @param None
 *
 * @return Returns a char representing the player who has a 3-in-a-row
 * in a column. The char returned is 'X' if player 1 has a 3-in-a-row in
 * some column, 'O' if player 2 does, or ' ' if neither player does.
 */
char MetaBoard::checkCols() {
	for (int j = 0; j < SIZE; j++) {
		// Checks if X has marked any 3 boards in a column
		if (metaboard[0][j]->won == 'X' && metaboard[1][j]->won == 'X' 
		&& metaboard[2][j]->won == 'X') {
			return 'X';
		}
		// Checks if O has marked any 3 boards in a column
		else if(metaboard[0][j]->won == 'O' && metaboard[1][j]->won=='O'
		&& metaboard[2][j]->won == 'O') {
			return 'O';
		}
	}
	return ' ';
}

/**
 * @brief Checks the diagonals to see if either player has a 3-in-a-row
 * through a diagonal.
 *
 * @param None
 *
 * @return Returns a char representing the player who has a 3-in-a-row
 * in a diagonal. The char returned is 'X' if player 1 has a 3-in-a-row
 * in some diagonal, 'O' if player 2 does, or ' ' if neither player does.
 */
char MetaBoard::checkDiags() {
	// Checks diagonal from top left to bottom right
	if (metaboard[0][0]->won == 'X' && metaboard[1][1]->won == 'X' 
	&& metaboard[2][2]->won == 'X') {
		return 'X';
	}
	else if (metaboard[0][0]->won == 'O' && metaboard[1][1]->won == 'O' 
	&& metaboard[2][2]->won == 'O') {
		return 'O';
	}
	// Checks diagonal from bottom left to top right
	else if (metaboard[0][2]->won == 'X' && metaboard[1][1]->won == 'X' 
	&& metaboard[2][0]->won == 'X') {
		return 'X';
	}
	else if (metaboard[0][2]->won == 'O' && metaboard[1][1]->won == 'O' 
	&& metaboard[2][0]->won == 'O') {
		return 'O';
	}
	return ' ';
}

/**
 * @brief Prints a metaboard with correct formatting so that
 * the lines seprating the boards are bold.
 *
 * @param None
 *
 * @return None
 */
void MetaBoard::printBoard() {
	// Goes through every row of boards in the metaboard
	for (int i = 0; i < SIZE; i++) {
		// Goes through each row in the row of boards
		// That means the 1st row of the second board is printed
		// before the 2nd row of the first board
		for (int j  = 0; j < SIZE; j++) {
			metaboard[i][0]->printRow(j);
			cout << "\e[1m||\e[0m";
			metaboard[i][1]->printRow(j);
			cout << "\e[1m||\e[0m";
			metaboard[i][2]->printRow(j);
			cout << "" << endl;
			// If it is not the main separation line, don't print the
			// horizontal lines in board
			if (j < SIZE - 1) {
				cout << "---------\e[1m||\e[0m---------" <<
				"\e[1m||\e[0m----------" << endl;
			}
			// If it is the main separation line and not the last
			// row of the entire board
			else if (i < SIZE - 1)
				cout<<"\e[1m---------||---------||----------\e[0m"<<endl;
		}
		// Print another horizontal line to show greater horizontal
		// separation
		if (i < SIZE - 1) {
			cout << "\e[1m---------||---------||----------\e[0m"<<endl;
		}
	}
}
