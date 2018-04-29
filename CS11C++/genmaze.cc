#include "maze.hh"
#include <vector>
#include <cstdlib>
#include <ctime>


// Get all unvisited possible directions to travel to from current location
vector<Direction> getPossDirections(const Maze &maze, const Location &current);

// If the cell in the direction from the current is valid, add it to the list
void addDirectionOption(const Maze &maze, const Location &current,
                        Direction dir, vector<Direction> &v);

// Usage statement - if any errors in arguments
void usage(const char *progName) {
    cout << "usage:  " << progName << " numRows numCols" << endl;
    cout << "\tnumRows is the number of rows in the maze" << endl;
    cout << "\tnumCols is the number of columns in the maze" << endl;
}

int main(int argc, char **argv) {
	if (argc != 3) {
        usage(argv[0]);
        return 1;
    }
    
    // Get the user defined number of rows and columns
    int numRows = atoi(argv[1]);
    int numCols = atoi(argv[2]);
    
    // Seed the random number generator
    srand(time(NULL));
    
    // Create a maze and path through the maze
    Maze maze = Maze(numRows, numCols);
    vector<Location> path;
    
    // Start out with an empty maze with all possible walls set
    maze.clear();
    maze.setAllWalls();
    
    // Start at top left corner and end at the bottom right corner
    maze.setStart(0, 0);
    maze.setEnd(numRows - 1, numCols - 1);
    
    // Set the start as visited and add it to the path
    maze.setVisited(maze.getStart().row, maze.getStart().col);
    path.push_back(maze.getStart());
    
    // While there are still options int he path
    while (!path.empty()) {
		// Get the current location as the last location in the path
		Location current = path.back();

		// If this location is the end, remove it from the path and move on
		if (current == maze.getEnd()) {
			path.pop_back();
			continue;
		}
		// Get the possible directions to travel to from the current
		vector<Direction> options = getPossDirections(maze, current);
		// If there are none, remove this current position from the path
		// and backtrack
		if (options.empty()) {
			path.pop_back();
			continue;
		}
		// Choose a random direction to travel in the possible ones
		// Remove the wall in this direction to allow travelling in this
		// direction in the path
		Direction dir = options[rand() % options.size()];
		maze.clearWall(current.row, current.col, dir);
		// Get the neighboring cell in that direction and add it to the path
		// after marking it as visited (so there are no loops in the path)
		Location next = maze.getNeighborCell(current.row, current.col, dir);
		maze.setVisited(next.row, next.col);
		path.push_back(next);
	}
	// Print out the maze to solve!
	maze.print(cout);
	return 0;
}

// Get all unvisited possible directions to travel to from current location
vector<Direction> getPossDirections(const Maze &maze, const Location &current) {
	vector<Direction> options;
	// If it is possible to travel in any direction without travelling out
	// of bounds, try adding that direction to the possibilities
	if (current.row > 0)
		addDirectionOption(maze, current, Direction::NORTH, options);
	if (current.row < maze.getNumRows() - 1)
		addDirectionOption(maze, current, Direction::SOUTH, options);
	if (current.col > 0)
		addDirectionOption(maze, current, Direction::WEST, options);
	if (current.col < maze.getNumCols() - 1)
		addDirectionOption(maze, current, Direction::EAST, options);
	return options;
}

// If the cell in the direction from the current is valid, add it to the list
void addDirectionOption(const Maze &maze, const Location &current,
                        Direction dir, vector<Direction> &v) {
	// Get the neighboring cell in a direction
	Location neighbor = maze.getNeighborCell(current.row, current.col, dir);
	// If it isn't visited, add it to the possibilities
	if (!maze.isVisited(neighbor.row, neighbor.col)) 
		v.push_back(dir);
}
