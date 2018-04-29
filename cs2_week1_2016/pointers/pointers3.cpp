/**
 * @file pointers3.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2015
 * @copyright This code is in the public domain.
 *
 * @brief Pointer-fu Exercise 3: "Entangled" pointers
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * @brief Set two pointers to the same memory and free them.
 */
int main(int argc, char *argv[])
{
	// The error was that the same location in memory (that a and b
	// were both pointing to) was freed twice. After it was freed 
	// using free(a) this location in memory was taken off the heap.
	// Thus, when trying to free b, which does not point to any location
	// in memory anymore, we get an error. Since a and b both point
	// to the same spot, chanigng the location of one also changes the
	// location of the other. This can be fixed by removing the second
	// free statement since the same location in memory doesn't need to
	// and can't be freed twice.
	
    int *a, *b;

    // Allocate an array of 10 ints.
    a = (int *) malloc(10 * sizeof(int));

    // Now `b` points to the same array of ints.
    b = a;

    free(a);

    return 0;
}
