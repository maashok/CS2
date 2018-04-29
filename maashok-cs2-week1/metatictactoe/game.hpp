#include "metaboard.hpp"

   
/**
 * @brief Represents a game of meta-tic-tac-toe. Alternates turns 
 * and changes the board based on what moves are entered by the user, until one
 * player wins or the game ends in a draw.
 */          
class Game
{
	private:
		MetaBoard * metaboard; /**<The metaboard for this game **/
		int priority; /**<Which player has priority**/
	public:
		Game();
		~Game();
		void Run();
};
