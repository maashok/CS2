#include "game.hpp"
#include <stdlib.h>
#include <cstring>
#include <string>

#include <iostream>
using namespace std;

/**
 * @brief Constructs a new game with a board and ready for player 1
 * to start.
 *
 * @param None
 *
 * @return None
 */
Game::Game() {
	board = new Board();
	turn = 1;	
}
/**
 * @brief Destructs the game by deleting the memory allocated for the
 * board
 *
 * @param None
 *
 * @return None
 */
Game::~Game() {
	// Calls the destructor of the board. Nothing else dynamically
	// allocated.
	board->~Board();
}

/**
 * @brief Sets up and plays a single session of Tic-Tac-Toe, giving
 * each player turns.
 *
 * @param None
 *
 * @return None
 */
void Game::Run() {
	// Start with instructions
	cout << "Pick which player each person is. The person who is " <<
	"Player 1 uses the X game piece, and Player 2 uses O" << endl;
	cout << "Take turns to place your game piece on one square " <<
	", after prompted to do so. May the best player win!" << endl;
	board->print();
	while (true) {
		// Keeps iterating until one player wins or there is a draw
		string row, col;
		cout << "Player "<< turn <<": Please enter the row you" <<
		" want to enter your piece in" << endl;
		cin >> row;
		cout << "Player "<< turn <<": Please enter the column you"<<
		" want to enter your piece in" << endl;
		cin >> col;
		int irow, icol;
		irow = atoi(row.c_str());
		icol = atoi(col.c_str());
		// Check if user input is valid
		if (irow < 1 || irow > 3) {
				cout << "Row number must be 1, 2, or 3." << endl;
				continue;
			}
		else if (icol < 1 || icol > 3) {
			cout << "Column number must be 1, 2, or 3." << endl;
			continue;
		}
		bool worked;
		if (turn == 1)
			worked = board->Place(irow, icol, 'X');
		else if (turn == 2)
			worked = board->Place(irow, icol, 'O');
		// If the space was not initially empty, the placing will
		// not have worked. This moves on to the next iteration,
		// without changing to the next player's turn.
		if (!worked) {
			cout << "That space is not empty" << endl;
			continue;
		}
		if (turn == 1) turn = 2;
		else if (turn == 2) turn = 1;
		board->print();

		// If the value returned from CheckWin is not zero, it means
		// either player 1 or 2 won.
		if (board->CheckWin() != 0) {
			cout << "Player " << board->CheckWin() << " won!" << endl;
			return;
		}
		else if (board->CheckDraw()) {
			cout << "The game has ended in a draw" << endl;
			return;
		}
	}
}
