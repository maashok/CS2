/**
 * @file DepthFirstSolver.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for maze solver that implements depth-first search.
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

#include "DepthFirstSolver.hpp"

/**
 * @brief Initializes the solver.
 *
 * @param[in] app Pointer to the main MazeSolverApp class.
 */
DepthFirstSolver::DepthFirstSolver(class MazeSolverApp *app)
{
    stack = new CoordinateStack(app);
    init();
}

/**
 * @brief Initializes the solver (student-implemented).
 */
void DepthFirstSolver::init()
{
	// Initialize each coordinate in the visited array to not visited
    for (int i = 0; i < WIDTH; i++) {
		for (int j = 0; j < HEIGHT; j++) {
			visited[i][j] = false;
		}
	}
}

/**
 * @brief Deinitializes the solver.
 */
DepthFirstSolver::~DepthFirstSolver()
{
	delete stack;
    deinit();
}


/**
 * @brief Deinitializes the solver (student-implemented).
 */
void DepthFirstSolver::deinit()
{
	// Nothing needs to be done here
}

/**
 * @brief Solves the maze given by `maze`.
 *
 * @param[in] maze MazeGrid object that stores the maze to be
 * solved.
 */
void DepthFirstSolver::solve(MazeGrid *maze)
{
	// Push the first starting point onto the stack
	stack->push(Coordinate(MAZE_START_X, MAZE_START_Y));
	while(!stack->is_empty()) {
		// Peek at the top coordinate of the stack
		Coordinate c = stack->peek();
		visited[c.x][c.y] = true;
		// If this coordinate is the end point, then we are done
		if (c.x == MAZE_END_X && c.y == MAZE_END_Y) {
			printf("COMPLETED THE MAZE!!!\n");
			return;
		}
		else {
			// Get all the directions we can move in and push the 
			// coordinates of these movements onto the stack
			int dir = maze->get_possible_moves(c.x, c.y);
			bool canMove = false;
			
			/** FIXED VISUALIZATION ISSUE WITH DFS MAZE WHERE SOME DIAGONALS
			 *  AND WEIRD PATHS WERE SHOWN BY CHANGING A SEQUENCE OF FOUR
			 *  IF STATEMENTS FOR EACH CARDINAL DIRECTION TO AN IF ELSE 
			 *  STATEMENT - THIS ISSUE WAS BECAUSE THEN SOMETIMES, GOING 
			 *  FROM SOUTH TO WEST FOR EXAMPLE WAS A VALID PATH - THE WAY OF
			 *  4 CONSECUTIVE IFS INSTEAD OF IF ELSES MADE IT MORE OF A 
			 *  BFS METHOD WHERE ALL POSSIBLE CHOICES FROM ONE LOCATION WERE
			 *  STORED - HOWEVER, BFS MAKES IT SO THAT THESE ARE CONSIDERED
			 *  FROM ONE TO ANOTHER, LEADING TO WEIRD DIAGONALS OR MOVING
			 *  NORTH/SOUTH RIGHT AFTER EACH OTHER
			 */
			if ((dir & N) && !visited[c.x][c.y-1]) {
				stack->push(Coordinate(c.x, c.y - 1));
				canMove = true;
			}
			else if ((dir & S) && !visited[c.x][c.y+1]) {
				stack->push(Coordinate(c.x, c.y + 1));
				canMove = true;
			}
			else if ((dir & E) && !visited[c.x+1][c.y]) {
				stack->push(Coordinate(c.x + 1, c.y));
				canMove = true;
			}
			else if ((dir & W) && !visited[c.x-1][c.y]) {
				stack->push(Coordinate(c.x - 1, c.y));
				canMove = true;
			}
			// If we have reached a dead end, pop the top off the stack
			// essentially backtracking
			if (!canMove) {
				stack->pop();
			}
		}
	}
}

/**
 * @brief Retrieves the current path through the maze.
 *
 * @return Vector storing the current path through the maze.
 */
vector<Coordinate> DepthFirstSolver::get_path()
{
    vector<Coordinate> list;
    stack->traverse(list);
    return list;
}

