/**
 * @file fileio.cpp
 * @author The CS2 TA Team <<cs2tas@caltech.edu>>
 * @version 1.0
 * @date 2013-2015
 * @copyright This code is in the public domain.
 *
 * @brief A brief example of file input (implementation).
 */

#include "fileio.h"

/**
 * @brief Reads the integers in file and fills nums with these integers.
 *
 * @param file: File containing integers, one per line.
 * @param nums: Vector to fill with the integers in file.
 *
 * Notice that the vector is passed by reference, so you should fill the vector
 * and not return anything from this function.
 */
void readFile(char const *file, std::vector<int> &nums)
{
	// To store each line of the file
    string num;
    // Open the file for input
    fstream myfile;
    myfile.open(file);
    // Check if the file is open
    if (myfile.is_open()) {
		while (getline(myfile, num)){
			// Convert the line to an integer and add it to the vector
			nums.push_back(atoi(num.c_str()));
		}
		myfile.close();
	}
	else cout << "Unable to open file!";

}
