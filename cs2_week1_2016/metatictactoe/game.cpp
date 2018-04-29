#include "game.hpp"
#include <stdlib.h>
#include <cstring>
#include <string>

#include <iostream>
using namespace std;

/**
 * @brief Constructs a new game with a metaboard and ready for player 1
 * to start.
 * 
 * @param None
 *
 * @return None
 */
Game::Game() {
	metaboard = new MetaBoard();
	priority = 1;	
}
/**
 * @brief Destructs the game by deleting the memory allocated for the
 * metaboard
 *
 * @param None
 *
 * @return None
 */
Game::~Game() {
	// Calls the destructor of the metaboard. Nothing else dynamically
	// allocated.
	metaboard->~MetaBoard();
}


void Game::Run() {
	// Start with instructions
	cout << "Pick which player each person is. The person who is " <<
	"Player 1 uses the X game piece, and Player 2 uses O" << endl;
	cout << "Take turns to place your game piece on one square " <<
	", after prompted to do so. May the best player win!" << endl;
	metaboard->printBoard();
	while (true) {
		// Keeps iterating until one player wins or there is a draw
		string row, col;
		// If the player can choose the active board (1st turn
		// or no legal moves in current active board)
		if (metaboard->activeBoardRow == -1 && 
		metaboard->activeBoardCol == -1) {
			string activeRow, activeCol;
			int arow, acol;
			cout << "Player " << priority << ": You may choose the "
			"active board to play on. Please enter the row number of it" 
			<< endl;
			cin >> activeRow;
			cout << "Please enter column number of the active board"
			<< endl;
			cin >> activeCol;
			arow = atoi(activeRow.c_str());
			acol = atoi(activeCol.c_str());
			// Check user input of active board coordinates
			if (arow < 1 || arow > 3) {
				cout << "Row number must be 1, 2, or 3." << endl;
				continue;
			}
			else if (acol < 1 || acol > 3) {
				cout << "Column number must be 1, 2, or 3." << endl;
				continue;
			}
			// Set the new active board's coordinates
			metaboard->activeBoardRow = arow - 1;
			metaboard->activeBoardCol = acol - 1;
			int row = metaboard->activeBoardRow;
			int col = metaboard->activeBoardCol;
			// Checks if the chosen board also has no legal moves
			if (metaboard->isFull(row, col)) {
				metaboard->activeBoardRow = -1;
				metaboard->activeBoardCol = -1;
				cout << "This board is not legal." << endl;
				continue;
			}
		}
		cout << "The active board is ("<< metaboard->activeBoardRow
		+ 1 << ", " << metaboard->activeBoardCol + 1 << ")" << endl;	
		cout << "Player " << priority << ": Please enter the row you" <<
		" want to enter your piece in" << endl;
		cin >> row;
		cout << "Player " << priority << ": Please enter the column you" 
		<< " want to enter your piece in" << endl;
		cin >> col;	
		int irow, icol;
		irow = atoi(row.c_str());
		icol = atoi(col.c_str());
		
		// Check user input
		if (irow < 1 || irow > 3) {
				cout << "Row number must be 1, 2, or 3." << endl;
				continue;
			}
		else if (icol < 1 || icol > 3) {
			cout << "Column number must be 1, 2, or 3." << endl;
			continue;
		}
		// Tries to place a game piece at the specified location on
		// the active board
		bool worked = false;		
		if (priority == 1)
			worked = metaboard->Place(irow, icol, 'X');
		else if (priority == 2)
			worked = metaboard->Place(irow, icol, 'O');
		// If the space was not initially empty, the placing will
		// not have worked. This moves on to the next iteration,
		// without changing to the next player's turn.
		if (!worked) {
			cout << "That space is not empty" << endl;
			continue;
		}
		if (priority == 1) priority = 2;
		else if (priority == 2) priority = 1;
		metaboard->printBoard();
		
		// If the value returned from CheckWin is not zero, it means
		// either player 1 or 2 won.
		if (metaboard->CheckWin() != 0) {
			cout << "Player " << metaboard->CheckWin()<<" won!" << endl;
			return;
		}
		else if (metaboard->CheckDraw()) {
			cout << "The game has ended in a draw" << endl;
			return;
		}
	}
}
