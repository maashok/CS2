/**
 * @file BreadthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements breadth-first search.
 *
 * @section License
 * Copyright (c) 2014-2015 California Institute of Technology.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 *
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies,
 * either expressed or implied, of the California Institute of Technology.
 *
 */

#include "BreadthFirstSolver.hpp"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
BreadthFirstSolver::BreadthFirstSolver(class MazeSolverApp *app)
{
    queue = new CoordinateQueue(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void BreadthFirstSolver::init()
{
	// Set the visited parameter for each of the coordinates to false
    for(int i = 0; i < WIDTH; i++) {
		for(int j = 0; j < HEIGHT; j++) {
			visited[i][j].visited = false;
		}
	}	
}

/**
 * @brief Deinitializes the solver.
 */
BreadthFirstSolver::~BreadthFirstSolver()
{
    delete queue;
    deinit();
}

/**
 * @brief Deinitializes the solver (student-implemented).
 */
void BreadthFirstSolver::deinit()
{
    // Nothing needs to be done here
}

/**
 * @brief Solve the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void BreadthFirstSolver::solve(MazeGrid *maze)
{
	// Add the start point of the maze to the queue
	visited[MAZE_START_X][MAZE_START_Y].visited = true;
	visited[MAZE_START_X][MAZE_START_Y].from = Coordinate(-1, -1);
    queue->enqueue(Coordinate(MAZE_START_X, MAZE_START_Y));
    // We should save what was the coordinate we went from to get
    // to each point, and this point will be stored in before.
    // To know what was the start point, the from parameter of the
    // starting coordinate is (-1, -1)
    Coordinate before = Coordinate(-1, -1);
    while(!queue->is_empty()) {
		// Peek at the coordinate in the front of the queue
		Coordinate c = queue->peek();
		visited[c.x][c.y].visited = true;
		before = c;
		// If this coordinate is the end point fo the maze, we are done
		if (c.x == MAZE_END_X && c.y == MAZE_END_Y) {
			printf("COMPLETED THE MAZE!!!\n");
			return;
		}
		else {
			// Get all the possible moves and check if this includes
			// north, south, west, east. If each of this directions is
			// ok, the coordinate that goes in that direction is
			// enqueued to be checked later.
			int dir = maze->get_possible_moves(c.x, c.y);
			if ((dir & N) && !(visited[c.x][c.y-1].visited)) {
				visited[c.x][c.y-1].from = before;
				queue->enqueue(Coordinate(c.x, c.y - 1));
			}
			if ((dir & S) && !(visited[c.x][c.y+1].visited)) {
				visited[c.x][c.y+1].from = before;
				queue->enqueue(Coordinate(c.x, c.y + 1));
			}
			if ((dir & E) && !(visited[c.x+1][c.y].visited)) {
				visited[c.x+1][c.y].from = before;
				queue->enqueue(Coordinate(c.x + 1, c.y));
			}
			if ((dir & W) && !(visited[c.x-1][c.y].visited)) {
				visited[c.x-1][c.y].from = before;
				queue->enqueue(Coordinate(c.x - 1, c.y));
			}
		}
		// Dequeue the coordinate we were just looking at
		c = queue->dequeue();


	}
}
/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> BreadthFirstSolver::get_path()
{
    vector<Coordinate> list;
    Coordinate top = queue->peek();
	// Goes to the from coordinate of each coordinate from the top of
	// the queue to get the path taken to get to that point
	while (top.x != -1 && top.y != -1) {
		list.push_back(top);
		top = visited[top.x][top.y].from;
	}
    return list;
}

