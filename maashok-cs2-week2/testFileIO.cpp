/**
 * @file testFileIO.cpp
 * @author The CS2 TA Team <<cs2tas@caltech.edu>>
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input.
 */

#include "fileio.h"

/**
 * @brief Read the file input and print out its contents
 *
 * Assumes that the file contains one integer per line.
 */
int main(int argc, char const *argv[])
{
	// There must be 2 arguments, the name of this program and the name
	// of the file
	if (argc != 2) return -1;
	char const * file = argv[1];
	// Instantiate a vector
    vector<int> nums;
    // Read the numbers of the file into the vector
	readFile(file, nums);
	// Print the vector
	print_vector(nums);
    return 0;
}
