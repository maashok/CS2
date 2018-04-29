#include "tictactoe.hpp"

#include <iostream>
using namespace std;

int main (int argc, char ** argv) {
	char choice;	
	// Checks if user would like to play tic tac toe, and if so
	// creates a pointer to a Game object and runs it.
	cout << "Would you like to play a game of tic-tac-toe? (Y/N)";
	cin >> choice;
	if (choice == 'Y' || choice == 'y') {
		Game *game = new Game();
		game->Run();
	}
	return 0;
}
