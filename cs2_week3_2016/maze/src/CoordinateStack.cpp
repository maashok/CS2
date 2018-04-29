/**
 * @file CoordinateStack.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for stack class that stores Coordinate objects.
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

#include "CoordinateStack.hpp"
#include <cstdio>

#define ANIMATION_DELAY     (25)

/**
 * @brief Initializes the stack.
 *
 * @param[in] app Reference to the MazeSolverApp; needed
 * to render moves.
 */
#ifndef TESTSUITE
CoordinateStack::CoordinateStack(class MazeSolverApp *app)
{
    this->app = app;
    init();
}
#else
CoordinateStack::CoordinateStack()
{
    init();
}
#endif

/**
 * @brief Initializes the stack (student-implemented).
 */
void CoordinateStack::init()
{
	// We only need to initialize the top node to NULL, as there are 
	// no elements
    top = NULL;
}

/**
 * @brief Deinitializes the stack.
 */
CoordinateStack::~CoordinateStack()
{
    deinit();
}

/**
 * @brief Deinitializes the stack (student-implemented).
 */
void CoordinateStack::deinit()
{
	// If the stack is empty, there is no memory that has been
	// allocated that still needs to be freed
    if (is_empty()) {
		return;
	}
 	// Delete each node in the linked list, keeping a pointer to the
	// next node while deleting the current node
    stackitem *head = top;
    stackitem *toDel;
	while (head != NULL) {
		toDel = head;
		head = head->next;
		delete toDel;
	}
}

/**
 * @brief Pushes an item onto the stack.
 *
 * @param[in] c Coordinate to push onto the stack.
 */
void CoordinateStack::push(Coordinate c)
{
    /* Do the operation. */
    do_push(c);

#ifndef TESTSUITE
    /* Update the display. */
    SDL_Delay(ANIMATION_DELAY);
    this->app->OnRender();
#endif
}

/**
 * @brief Do the actual push operation (student-implemented).
 *
 * @param[in] c Coordinate to push onto the stack.
 */
void CoordinateStack::do_push(Coordinate c)
{
	// If the array is empty, the top node needs to be initialized
    if (is_empty()) {
		top = new stackitem;
		top->next = NULL;
		top->c = c;
	}
	// Otherwise, this new coordinate becomes the top node and the old
	// top node is connected to the new top
	else {
		stackitem *oldFirst = new stackitem;
		oldFirst->c = top->c;
		oldFirst->next = top->next;
		top->c = c;
		top->next = oldFirst;
	}
}

/**
 * @brief Pops an item off the stack.
 *
 * @return The popped Coordinate.
 */
Coordinate CoordinateStack::pop()
{
    /* Do the operation. */
    Coordinate c = do_pop();

#ifndef TESTSUITE
    /* Update the display. */
    SDL_Delay(ANIMATION_DELAY);
    this->app->OnRender();
#endif

    return c;
}

/**
 * @brief Do the actual pop operation (student-implemented).
 *
 * @return The popped Coordinate. If the stack is empty, returns the
 * Coordinate (-1, -1).
 */
Coordinate CoordinateStack::do_pop()
{
	// If the stack is empty, return a pre-defined coordinate (-1, -1)
	if (is_empty()) {	
		Coordinate c(-1, -1);
		return c;
	}
	// Save the top coordinate to return and change the top to the
	// second node, and also deallocate the memory for the popped node
	stackitem *oldFirst = top;
    Coordinate c = oldFirst->c;
    top = oldFirst->next;
    delete oldFirst;
    return c;
}

/**
 * @brief Returns the top item of the stack without removing it.
 *
 * @return The Coordinate at the top of the stack. If the stack is empty
 * returns coordinate (-1, -1)
 */
Coordinate CoordinateStack::peek()
{
	if (is_empty()) {
		return Coordinate(-1, -1);
	}
    return top->c;
}

/**
 * @brief Returns true if stack is empty, false otherwise.
 *
 * @return Boolean indicating whether the stack is empty.
 */
bool CoordinateStack::is_empty()
{
	// If the top node is null, there are no nodes in the stack
    return top == NULL;
}

/**
 * @brief Go through the stack and store the contents in a vector for
 * easier usage.
 *
 * @param[in] list Vector in which to store the coordinates.
 */
void CoordinateStack::traverse(vector<Coordinate> &list) {
	// Create another pointer to the top of the stack so the top pointer
	// is not moved
	stackitem *head = top;
	while(head != NULL) {
		list.push_back(head->c);
		head = head->next;
	}
}
