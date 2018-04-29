/**
 * @file pointers2.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2015
 * @copyright This code is in the public domain.
 *
 * @brief Pointer-fu Exercise 2: Uninitialized pointers
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * @brief Allocates and frees an array of 10 ints if timestamp is odd.
 */
int main(int argc, char *argv[])
{
	// This code assumes that if a pointer is declared but not
	// initialized, then the value is nullptr. However, it is undefined
	// and does not definitely have to be nullptr. So, just checking
	// if a is not nullptr is not enough before freeing the pointer 
	// since an allocation might not have been attempted if the
	// timestamp was even. Thus, before attempting to free it (which
	// may cause a seg fault for uninitialized values), we should check
	// again if the timestamp was odd, and only then free the pointer
	// if it is not nullptr. This was fixed by nesting the existing
	// conditional statement to free a inside a conditional statement
	// with condition (t % 2).
	
	/** Changed based on submission feedback */
    int *a = nullptr;
    time_t t = time(nullptr); // Get the current Unix timestamp

    /***** CHANGE NOTHING BELOW THIS LINE *****/
    if (t % 2)
    {
        // Allocate an array of 10 ints if the timestamp is an odd number.
        // This is a contrived way to conditionally allocate some memory.
        a = (int *) malloc(10 * sizeof(int));
        cout << "allocating some memory!\n";
    }
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    // If we allocated memory, free it!
    /** Changed based on submission feedback **/
    if (a)
		free(a);
	
    return 0;
}
