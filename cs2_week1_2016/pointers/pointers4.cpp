/**
 * @file pointers4.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2015
 * @copyright This code is in the public domain.
 *
 * @brief Pointer-fu Exercise 4: Typecasting vs. address-of
 */

#include <cstdlib>
#include <iostream>

using namespace std;

/**
 * @brief performs type castings
 */
int main(int argc, char *argv[])
{
	// There were two errors made, in making b point to a, and getting
	// the address of the array into b. First, if we want b to point to 
	// a, we should use the & operator that returns the address of
	// a variable, and then save this address in b. Thus, just doing 
	// b = &a is enough. What was done before is not possible, since
	// it does not make sense to cast an int to type pointer to int.
	//
	// The second error is in getting the address of the array. malloc
	// returns a pointer to the location of memory allocated, so c is
	// of type pointer. Getting the address of this pointer c, will 
	// give a pointer of type void ** which is not the point of this 
	// operation and also can't be type casted to type int *. We want
	// to get the address of the array, which is stored in the pointer
	// c itself. All we need to do is type-cast c to type int *. This
	// is done by b = (int *) c;
    int a = 5, *b;
    void *c;

    // Now make `b` point to `a`.
    b = &a;

    /***** CHANGE NOTHING BELOW THIS LINE *****/
    cout << "The value pointed by `b` is " << *b;
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    // Allocate an array of 10 ints.
    c = malloc(10 * sizeof(int));

    // Get the address of the array.
    b = (int *) c;

    /***** CHANGE NOTHING BELOW THIS LINE *****/
    b[2] = 5;
    /***** CHANGE NOTHING ABOVE THIS LINE *****/

    return 0;
}
