#include "board.hpp"

#include <iostream>
using namespace std;

/**
 * @brief Constructs a new board of size 3 x 3. Each square
 * is unoccupied at first, represented by the character ' '.
 *
 * @param None
 *
 * @return None
 */

Board::Board() {
	// Creates an array of 3 char * elements
	squares = new char*[SIZE];

	for(int i = 0; i < SIZE; i++) {
		// Creates an array of chars in each array
		squares[i] = new char[SIZE];
		// Each square is initialized to be unoccupied
		for(int j = 0; j < SIZE; j++) {
			squares[i][j] = ' ';
		}
	}	
}

/**
 * @brief Destructs the Board object by freeing the memory that was
 * dynamically allocated for the squares array.
 *
 * @param None
 *
 * @return None
 */
Board::~Board() {
	// First delete the memory allocated for each array of chars
	for (int i = 0; i < SIZE; i++) {
		delete[] squares[i];
	}
	// Then delete the memory allocated for the array of array of chars
	delete[] squares;
}
	
/**
 * @brief Given board coordinates, returns a square state, either
 * unoccupied, X, or O.
 *
 * @param The board position is given by x and y, which are the
 * row and column number (starting from 1) for the squares array, 
 * respectively. This specifies where we are checking the square state 
 * for.
 *
 * @return A char representing what is the game piece at the board
 * position. 'X' is returned for the piece of player 1, who uses X.
 * 'O' is returned for the piece of player 2, who uses Y.
 * ' ' can also be returned if that position is currently empty.
 */
char Board::Query(int x, int y) {
	// Just returns the char representing the state of that position
	// in the board
	return squares[x-1][y-1];	
}

/**
 * @brief Finds out if the board is full, or there are no unoccupied
 * spaces.
 *
 * @param None
 *
 * @return Returns a boolean representing whether the board is full.
 * Returns true if there are no unoccupied spaces and false if there is
 * at least one unoccupied space.
 */
bool Board::isFull() {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (squares[i][j] == ' ')
				return false;
		}
	}
	return true;	
}

/**
 * @brief Given board coordinates and a piece type, places the piece
 * on the specified position.
 *
 * @param The board position is given by x and y, which are the
 * row and column number (starting from 1) for the squares array, 
 * respectively. This specifies where we are going to place the piece.
 * What piece to place is specified by piece, which is either 'X', 'O', 
 * depending on whether player 1 or player 2 is playing., respectively.
 *
 * @return Returns whether the operation was successful. Returns true
 * if the position that we are placing the piece on is initially
 * unoccupied. Returns false otherwise.
 */
bool Board::Place(int x, int y, char piece) {
	// Checks if this position is already occupied and if so,
	//returns false
	if (Query(x, y) != ' ')
		return false;
	squares[x-1][y-1] = piece;	
	return true;
}

/**
 * @brief Checks if one of the players has won, if any.
 *
 * @param None
 *
 * @return Returns an integer representing which player has won, if
 * any. Returns 1 if player 1 (who uses X) won, returns 2 if player 2
 * (who uses O) won, and returns 0 if neither player has won yet.
 */
int Board::CheckWin() {
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
	// Otherwise, neither player has won
	else
		return 0;
}

/**
 * @brief Checks the rows to see if either player has a 3-in-a-row.
 *
 * @param None
 *
 * @return Returns a char representing the player who has a 3-in-a-row
 * in a row. The char returned is 'X' if player 1 has a 3-in-a-row in
 * some row, 'O' if player 2 does, or ' ' if neither player does.
 */
char Board::checkRows() {
	for (int i = 0; i < SIZE; i++) {
		// Checks if X has 3 in any row
		if (squares[i][0] == 'X' && squares[i][1] == 'X' 
		&& squares[i][2] == 'X') {
			return 'X';
		}
		// Checks if O has 3 in any row
		else if (squares[i][0] == 'O' && squares[i][1] == 'O' 
		&& squares[i][2] == 'O') {
			return 'O';
		}
	}
	return ' ';
}

/**
 * @brief Checks the columns to see if either player has a 3-in-a-row.
 *
 * @param None
 *
 * @return Returns a char representing the player who has a 3-in-a-row
 * in a column. The char returned is 'X' if player 1 has a 3-in-a-row in
 * some column, 'O' if player 2 does, or ' ' if neither player does.
 */
char Board::checkCols() {
	for (int j = 0; j < SIZE; j++) {
		// Checks if X has 3 in any column
		if (squares[0][j] == 'X' && squares[1][j] == 'X' 
		&& squares[2][j] == 'X') {
			return 'X';
		}
		// Checks if O has 3 in any column
		else if (squares[0][j] == 'O' && squares[1][j] == 'O' 
		&& squares[2][j] == 'O') {
			return 'O';
		}
	}
	return ' ';
}

/**
 * @brief Checks the diagonals to see if either player has a 3-in-a-row.
 *
 * @param None
 *
 * @return Returns a char representing the player who has a 3-in-a-row
 * in a diagonal. The char returned is 'X' if player 1 has a 3-in-a-row
 * in some diagonal, 'O' if player 2 does, or ' ' if neither player does.
 */
char Board::checkDiags() {
	// Checks diagonal from top left to bottom right
	if (squares[0][0] == 'X' && squares[1][1] == 'X' 
	&& squares[2][2] == 'X') {
		return 'X';
	}
	else if (squares[0][0] == 'O' && squares[1][1] == 'O' 
	&& squares[2][2] == 'O') {
		return 'O';
	}
	// Checks diagonal from bottom left to top right
	else if (squares[0][2] == 'X' && squares[1][1] == 'X' 
	&& squares[2][0] == 'X') {
		return 'X';
	}
	else if (squares[0][2] == 'O' && squares[1][1] == 'O' 
	&& squares[2][0] == 'O') {
		return 'O';
	}
	return ' ';
}

/**
 * @brief Checks if the game has ended in a draw.
 *
 * @param None
 *
 * @return Returns a boolean representing whether the game has ended in
 * a draw. Returns true if the game is a draw and false if the game
 * is not a draw.
 */
bool Board::CheckDraw() {
	// If the board is not completely full, then the game has not
	// even ended yet and is not a draw.
	if (!isFull())
		return false;
	// Otherwise, we just need to check whether neither player has won,
	// which causes 0 to be returned from CheckWin function.
	return CheckWin() == 0;	
}

/**
 * @brief Prints the board to the terminal for the players to view.
 *
 * @param None
 *
 * @return None
 */
void Board::print() {
	for(int i = 0; i < SIZE; i++) {
		cout << squares[i][0] << " | " << squares[i][1] << " | " <<
		squares[i][2] << endl;
		if (i < SIZE - 1) cout << "-- -- --" << endl;
	}
}
