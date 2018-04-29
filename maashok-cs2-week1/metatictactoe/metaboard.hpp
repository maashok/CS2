#include "board.hpp"

/**
 * @brief Represents a board of meta-tic-tac-toe. Is a 3-by-3 grid
 * of normal tic-tac-toe boards, but with a specific active board
 * which is specified by row and column. Players can only place
 * pieces on this active board
 */  
class MetaBoard
{
	private:
		Board *metaboard[3][3]; /**<The game board**/
		char checkRows();
		char checkCols();
		char checkDiags();
	public:
		MetaBoard();
		~MetaBoard();
		int CheckWin();
		bool CheckDraw();
		int activeBoardRow; /**<Row of the active board**/
		int activeBoardCol; /**<Column of the active board**/
		bool isAllFull();
		bool isFull(int row, int col);
		int whatWhenFull();
		bool Place(int x, int y, char piece);
		void printBoard();
};
