#include "tictactoe.hpp"

#include <iostream>
using namespace std;

int main (int argc, char ** argv) {
	char choice;
	// Checks if user would like to play tic tac toe, and if so
	// creates a pointer to a Game object and runs it after displaying
	// the instructions.	
	cout << "Would you like to play a game of meta-tic-tac-toe? (Y/N)";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') { 
		printRules();
		Game *game = new Game();
		game->Run();
	}
	return 0;
}

/**
 * @brief Prints the rules of meta-tic-tac-toe.
 *
 * @param None
 *
 * @return None
 */
void printRules() {
	cout << "These are the rules of Meta-Tic-Tac-Toe" << endl;
	cout << "This is a 2 player game, and the player with X goes first."
	<< endl;
	cout << "The player whose turn it is places one of their pieces "
	<< "on an open square on the active board. Then the active board "
	<< "is switched to the board corresponding to the square on which "
	<< "the symbol was placed." << endl;
	cout << "For example, if the O player places an O on the top right "
	 << "square of any board, then the top-right board becomes the "
	 << "active board." << endl;
	 
	cout << "If the active board has not been chosen yet or it has no "
	<< "legal moves, you may choose to play anywhere." << endl;
	cout << "If you get a 3-in-a-row on any individual board, that "
	<< "board is marked with your symbol. You can still make moves on "
	<< "that board, but only one person can mark that board as won." <<
	"The player who has marked 3-in-a-row boards, wins.";
} 	
