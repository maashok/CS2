#include "board.hpp"
   
/**
 * @brief Represents a game of tic-tac-toe. Alternates turns and changes
 * the board based on what moves are entered by the user, until one
 * player wins or the game ends in a draw.
 */          
class Game
{
	private:
		Board * board; /**<The board for this game**/
		int turn; /**<Which player's turn it is**/
	public:
		Game();
		~Game();
		void Run();
};
