// Defines the dimensions of the board as a constant 3, rather
// than having to hardcode the value
#define SIZE 3
   
/**
 * @brief Represents a tic-tac-toe game board. Allows for
 * the game to do certain actions with the board, such as placing
 * a game piece and checking who has won this board.
 */          
class Board
{
	private:
		char **squares; /**<One tic-tic-tac-toe board of the board**/
		char checkRows();
		char checkCols();
		char checkDiags();
	public:
		Board();
		~Board();
		char won; /**<Stores which player has won this board, if any **/
		char Query(int x, int y);
		bool isFull();
		bool Place(int x, int y, char piece, int row, int col);
		void CheckWin(int row, int col);  
		void printRow(int rowNum); 
};
