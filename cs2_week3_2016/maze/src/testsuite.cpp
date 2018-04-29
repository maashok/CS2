/**
 * @file testsuite.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2014-2015
 * @copyright see License section
 *
 * @brief Performs tests of the CoordinateQueue and CoordinateStack classes.
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
#include "CoordinateStack.hpp"
#include "CoordinateQueue.hpp"

int main()
{
    Coordinate c;
    CoordinateQueue *queue = new CoordinateQueue();
    CoordinateStack *stack = new CoordinateStack();

	// Testing CoordinateStack operations
	printf("Testing CoordinateStack\n");
	printf("Pushing Coordinate (5, 6)\n");
    stack->push(Coordinate(5, 6));
    printf("Pushing Coordinate (3,4)\n");
    stack->push(Coordinate(3, 4));
    if (stack->is_empty()) {
		printf("The stack is empty");
	}
	printf("Peeking at Coordinate (3, 4)\n");
	c = stack->peek();
	// Note that in the testsuite, we are checking if the coordinates
	// that are returned are the dummy coordinates to see what the
	// behavior is when the stack/queue is empty. In real usage,
	// we would check if it is empty using is_empty() before even 
	// attempting to pop/dequeue/peek.
	if (c.x == -1 && c.y == -1)
		printf("The stack is empty\n");
	else
		printf("Peeked value: %d %d\n", c.x, c.y);
	printf("Popping Coordinate (3, 4)\n");
	c = stack->pop();
	if (c.x == -1 && c.y == -1)
		printf("The stack is empty\n");
	else
		printf("Popped value: %d %d\n", c.x, c.y);
	printf("Popping Coordinate (5, 6)\n");
	c = stack->pop();
	if (c.x == -1 && c.y == -1)
		printf("The stack is empty\n");
	else
		printf("Popped value: %d %d\n", c.x, c.y);
	if (stack->is_empty()) {
		printf("The stack is empty\n");
	}
	printf("Trying to pop from an empty stack.\n");
	c = stack->pop();
	if (c.x == -1 && c.y == -1) {
		printf("The stack is empty\n");
	}
	else {
		printf("Popped value: %d %d\n", c.x, c.y);
	}
	printf("Pushing Coordinate (1, 5)\n");
    stack->push(Coordinate(1, 5));
    printf("Pushing Coordinate (56, 21)\n");
    stack->push(Coordinate(56, 21));
    printf("Pushing Coordinate (2, 1)\n");
    stack->push(Coordinate(2, 1));
	
	printf("\n");
	// Testing CoordinateQueue operations
	printf("Testing CoordinateQueue\n");
	printf("Enqueuing Coordinate (5, 6)\n");
    queue->enqueue(Coordinate(5, 6));
    printf("Enqueuing Coordinate (3,4)\n");
    queue->enqueue(Coordinate(3, 4));
    if (queue->is_empty()) {
		printf("The queue is empty");
	}
	printf("Peeking at Coordinate (5, 6)\n");
	c = queue->peek();
	if (c.x == -1 && c.y == -1)
		printf("The stack is empty\n");
	else
		printf("Peeked value: %d %d\n", c.x, c.y);
	printf("Dequeuing Coordinate (5, 6)\n");
	c = queue->dequeue();
	if (c.x == -1 && c.y == -1)
		printf("The stack is empty\n");
	else
		printf("Dequeued value: %d %d\n", c.x, c.y);
	printf("Dequeuing Coordinate (3, 4)\n");
	c = queue->dequeue();
	if (c.x == -1 && c.y == -1)
		printf("The stack is empty\n");
	else
		printf("Dequeued value: %d %d\n", c.x, c.y);
	if (queue->is_empty()) {
		printf("The queue is empty\n");
	}
	printf("Trying to dequeue from an empty stack.\n");
	c = queue->dequeue();
	if (c.x == -1 && c.y == -1) {
		printf("The queue is empty\n");
	}
	else {
		printf("Dequeued value: %d %d\n", c.x, c.y);
	}
	printf("Enqueuing Coordinate (1, 5)\n");
    queue->enqueue(Coordinate(1, 5));
    printf("Enqueuing Coordinate (56, 21)\n");
    queue->enqueue(Coordinate(56, 21));
    printf("Enqueuing Coordinate (2, 1)\n");
    queue->enqueue(Coordinate(2, 1));


    delete queue;
    delete stack;
    return 0;
}
