/**
 * @file CoordinateQueue.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 2.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Functions for queue class that stores Coordinate objects.
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
#include <cstdio>
#include "CoordinateQueue.hpp"

#define ANIMATION_DELAY     (25)

/**
 * @brief Initializes the queue.
 *
 * @param[in] app Reference to the MazeSolverApp; needed
 * to render moves.
 */
#ifndef TESTSUITE
CoordinateQueue::CoordinateQueue(class MazeSolverApp *app)
{
    this->app = app;
    init();
}
#else
CoordinateQueue::CoordinateQueue()
{
    init();
}
#endif

/**
 * @brief Initializes the queue (student-implemented).
 */
void CoordinateQueue::init()
{
	// To initialize the queue, set the front and rear node pointers
	// to null
   front = NULL;
   rear = NULL;
}

/**
 * @brief Deinitializes the queue.
 */
CoordinateQueue::~CoordinateQueue()
{
    deinit();
}

/**
 * @brief Deinitializes the queue (student-implemented).
 */
void CoordinateQueue::deinit()
{
	// If the queue is empty, there is no allocated memory we need to
	// free
	if (is_empty()) {
		return;
	}
	// Delete each node in the linked list, keeping a pointer to the
	// next node while deleting the current node
    queueitem *head = front;
    queueitem *toDel;
    while (head != NULL) {
		toDel = head;
		head = head->next;
		delete toDel;
	}
}

/**
 * @brief Enqueues an item by adding it to the bottom of the
 * queue.
 *
 * @param[in] c Coordinate to enqueue onto the queue.
 */
void CoordinateQueue::enqueue(Coordinate c)
{
    /* Do the operation. */
    do_enqueue(c);
#ifndef TESTSUITE
    /* Update the display, if necessary. */
    SDL_Delay(ANIMATION_DELAY);
    this->app->OnRender();
#endif
}

/**
 * @brief Do the actual enqueue operation (student-implemented).
 *
 * @param[in] c Coordinate to enqueue onto the queue.
 */
void CoordinateQueue::do_enqueue(Coordinate c)
{
	// If the queue is empty, the front and rear pointers need
	// to be initialized, and since there will be one element, the
	// front and rear element are the same
    if (is_empty()) {
		front = new queueitem;
		front->c = c;
		front->next = NULL;
		rear = front;
	}
	// Otherwise, intialize the new last element and connect the previous
	// rear element to the new one
	else {
		queueitem *oldLast = rear;
		rear = new queueitem;
		rear->c = c;
		rear->next = NULL;
		oldLast->next = rear;	
	}
}

/**
 * @brief Dequeues an item by removing it from the top.
 *
 * @return The dequeued Coordinate.
 */
Coordinate CoordinateQueue::dequeue()
{
    /* Do the operation. */
    return do_dequeue();
}

/**
 * @brief Do the actual dequeue operation (student-implemented).
 *
 * @return The dequeued Coordinate. If the queue is empty, return
 * the Coordinate (-1, -1).
 */
Coordinate CoordinateQueue::do_dequeue()
{
	// If the queue is empty, return the predefined coordinate (-1, -1)
    if (is_empty()) {
		return Coordinate(-1, -1);
	}    
	// Save the front coordinate to return and change the front to the
	// second node, and also deallocate the memory for the popped node
    queueitem *oldFront = front;
    Coordinate c = oldFront->c;
    front = oldFront->next;
    delete oldFront;
    return c;
}

/**
 * @brief Returns the item at the front of the queue without
 * removing it.
 *
 * @return The first Coordinate in the queue. If the queue is empty,
 * return the coordinate (-1, -1)
 */
Coordinate CoordinateQueue::peek()
{
	if (is_empty()) {
		return Coordinate(-1, -1);
	}
    return front->c;
}

/**
 * @brief Returns true is the queue is empty, false otherwise.
 *
 * @return Boolean indicating whether the queue is empty.
 */
bool CoordinateQueue::is_empty()
{
	// If the queue is empty, the front node is NULL
    return front == NULL;
}

