// Defines the dimensions of the board as a constant 3, rather
// than having to hardcode the value
#define SIZE 3
   
/**
 * @brief Represents a tic-tac-toe game board. Allows for
 * the game to do certain actions with the board, such as placing
 * a game piece and checking who has won.
 */          
class Board
{
	private:
		char **squares; /**<The game board **/
		char checkRows();
		char checkCols();
		char checkDiags();
	public:
		Board();
		~Board();
		char Query(int x, int y);
		bool isFull();
		bool Place(int x, int y, char piece);
		int CheckWin();
		bool CheckDraw();
		void print();
};
