#include "maze.hh"



// Returns the number of rows in the maze
int Maze::getNumRows() const {
	return numRows;
}

// Returns the number of columns in the maze
int Maze::getNumCols() const {
	return numCols;
}


// Returns the starting point in the maze
Location Maze::getStart() const {
	return start;
}

// Sets the starting point in the maze    
void Maze::setStart(int row, int col) {
	assert(row >= 0 && row < numRows);
	assert(col >= 0 && col < numCols);
	start = Location(row, col);
}


// Returns the ending point in the maze    
Location Maze::getEnd() const {
	return end;
}

// Sets the ending point in the maze
void Maze::setEnd(int row, int col) {
	assert(row >= 0 && row < numRows);
	assert(col >= 0 && col < numCols);
	end = Location(row, col);
}

// Get maze cell at specific index of the 1-D array
MazeCell Maze::getArrayVal(int index) const {
	assert(index >= 0 && index < (2 * numRows + 1) * (2 * numCols + 1));
	return cells[index];
}

// Initialize a new maze of size rows x cols
Maze::Maze(int rows, int cols) {
	// Set the size
	numRows = rows;
	numCols = cols;
	int size = (2 * rows + 1) * (2 * cols + 1);
	cells = new MazeCell[size];
	// Start out the maze all empty
	for (int i = 0; i < size; i++) {
		cells[i] = MazeCell::EMPTY;
	}
}

// Make a copy of an existing maze object
Maze::Maze(const Maze &m) {
	// Copy over the size and other parameters
	numRows = m.getNumRows();
	numCols = m.getNumCols();
	start = m.getStart();
	end = m.getEnd();
	int size = (2 * numRows + 1) * (2 * numCols + 1);
	// Copy the actual cells of the maze
	cells = new MazeCell[size];
	for (int i = 0; i < size; i++) {
		cells[i] = m.getArrayVal(i);
	}
}

// Maze destructor
Maze::~Maze() {
	delete [] cells;
}

// Maze assignment operator
Maze & Maze::operator=(const Maze &m) {
	// If self assignment, just return the argument (no need to copy)
	if (&m == this)
		return *this;
	// Otherwise perform same operations as copy constructor
	numRows = m.getNumRows();
	numCols = m.getNumCols();
	start = m.getStart();
	end = m.getEnd();
	int size = (2 * numRows + 1) * (2 * numCols + 1);
	cells = new MazeCell[size];
	for (int i = 0; i < size; i++) {
		cells[i] = m.getArrayVal(i);
	}
	// Return newly created maze
	return *this;
}    
    
// Take 2D expanded coordinates and compute the corresponding 1D array index
int Maze::getArrayIndex(const Location &loc) const {
	return loc.row * (2 * numCols + 1) + loc.col;
}

// Returns the expanded coordinates of the specified cell coordinates
Location Maze::getCellArrayCoord(int cellRow, int cellCol) const {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	return Location(2 * cellRow + 1, 2 * cellCol + 1);
}

// Returns the expanded coordinates of the wall on a specific side of
// a cell given in cell coordinates
Location Maze::getWallArrayCoord(int cellRow, int cellCol, Direction direction) 
	const {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	// Get the expanded coordinates of the given cell
	Location expanded = getCellArrayCoord(cellRow, cellCol);
	// Based on the direction get the new cell coordinates
	// get the wall in the right direction
	if (direction == Direction::NORTH) 
		return Location(expanded.row - 1, expanded.col);
	if (direction == Direction::SOUTH)
		return Location(expanded.row + 1, expanded.col);
	if (direction == Direction::EAST)
		return Location(expanded.row, expanded.col + 1);
	if (direction == Direction::WEST)
		return Location(expanded.row, expanded.col - 1);
	return expanded;
}

// Sets all cells and walls to be empty, so that the maze is
// completely cleared
void Maze::clear() {
	for (int i = 0; i < (2 * numRows + 1) * (2 * numCols + 1); i ++) {
		cells[i] = MazeCell::EMPTY;
	}
}

// Places a wall at every location that can be a wall in the maze
void Maze::setAllWalls() {
	// Set the vertical walls on every other cell in expanded coordinates
	for (int i = 0; i < 2 * numRows + 1; i += 2) {
		for (int j = 1; j < 2 * numCols + 1; j += 2) {
			cells[i * (2 * numCols + 1) + j] = MazeCell::WALL;
		}
	}
	// Set the horizontal walls on every other cell in expanded coordinates
	for (int i = 1; i < 2 * numRows + 1; i += 2) {
		for (int j = 0; j < 2 * numCols + 1; j += 2) {
			cells[i * (2 * numCols + 1) + j] = MazeCell::WALL;
		}
	}
}


// Returns the value of the specified cell
MazeCell Maze::getCell(int cellRow, int cellCol) const {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	return cells[getArrayIndex(getCellArrayCoord(cellRow, cellCol))];
}

// Set the value of the specified cell to the given value
void Maze::setCell(int cellRow, int cellCol, MazeCell val) {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	cells[getArrayIndex(getCellArrayCoord(cellRow, cellCol))] = val;
}


// Returns the cell-coordinates of the neighboring cell in the specified
// direction.  Trips an assertion if the given cell has no neighbor in the
// specified direction (e.g. the NORTH neighbor of cell (0,5)).
Location Maze::getNeighborCell(int cellRow, int cellCol,
						 Direction direction) const {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	// Get the new row and column of the location of the neighboring cell
	if (direction == Direction::NORTH) 
		cellRow -= 1;
	if (direction == Direction::SOUTH)
		cellRow += 1;
	if (direction == Direction::EAST)
		cellCol += 1;
	if (direction == Direction::WEST)
		cellCol -= 1;
	// Check that the neighboring cell is valid
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	return Location(cellRow, cellCol);
}


// Returns true if there is a wall in the specified direction from the
// given cell, false otherwise
bool Maze::hasWall(int cellRow, int cellCol, Direction direction) const {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	return cells[getArrayIndex(getWallArrayCoord(cellRow, cellCol, 
		direction))] == MazeCell::WALL;
}

// Puts a wall on the specified side of the given cell
void Maze::setWall(int cellRow, int cellCol, Direction direction) {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	cells[getArrayIndex(getWallArrayCoord(cellRow, cellCol, direction))] = 
		MazeCell::WALL;
}

// Removes a wall on the specified side of the given cell
void Maze::clearWall(int cellRow, int cellCol, Direction direction) {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	cells[getArrayIndex(getWallArrayCoord(cellRow, cellCol, direction))] = 
		MazeCell::EMPTY;
}

// Returns true if the specified maze cell has been visited.
bool Maze::isVisited(int cellRow, int cellCol) const {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	return cells[getArrayIndex(getCellArrayCoord(cellRow, cellCol))] == 
		MazeCell::VISITED;
}

// Changes the cell's value to VISITED
void Maze::setVisited(int cellRow, int cellCol) {
	assert(cellRow >= 0 && cellRow < numRows);
	assert(cellCol >= 0 && cellCol < numCols);
	cells[getArrayIndex(getCellArrayCoord(cellRow, cellCol))] = 
		MazeCell::VISITED;
}


// Outputs the maze using simple ASCII-art to the specified output stream.
// The output format is as follows, using the example maze from the
// assignment write-up.  (The text to the right of the maze is purely
// explanatory, and you don't need to output it.)
//
// 3 4                 (# of rows and then # of columns)
// +---+---+---+---+   (each cell is 3 spaces wide, with a + at each corner)
// | S     |       |   (walls indicated by --- or |)
// +---+   +   +   +   (start indicated by S, end indicated by E)
// |   |   |   |   |
// +   +   +   +   +
// |           | E |
// +---+---+---+---+
void Maze::print(ostream &os) const {
	// Print number of rows and columns
	cout << numRows << " " << numCols << endl;
	// Go through the rows of the maze
	for (int i = 0; i < numRows; i++) {
		// Start the maze in the left corner of the top wall
		cout << "+";
		// For every column add a wall or blank spot above the cell
		for (int j = 0; j < numCols; j++) {
			if(hasWall(i, j, Direction::NORTH))
				cout << "---+";
			else
				cout << "   +";
		}
		cout << endl;
		// Then add the wall or blank spot to the west of the cell
		for (int j = 0; j < numCols; j++) {
			if (hasWall(i, j, Direction::WEST))
				cout << "| ";
			else
				cout << "  ";
			// If the cell is start or end mark it accordingly
			// Otherwise leave it blank
			if (getStart() == Location(i, j))
				cout << "S ";
			else if (getEnd() == Location(i, j))
				cout << "E ";
			else
				cout << "  ";
		}
		// End the row with a wall
		cout << "|" << endl;
	}
	// Output the walls below last row
	for (int j = 0; j < numCols; j++) {
		cout << "+---";
	}
	cout << "+" << endl;
}
