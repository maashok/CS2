/**
 * @file arrays1.cpp
 * @author The CS2 TA Team <cs2tas@caltech.edu>
 * @date 2014-2015
 * @copyright This code is in the public domain.
 *
 * @brief An array example.
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

#define TEST_SIZE 60

using namespace std;

int arrayMax(int arr[], int n) {
	// Start by assuming the first element is the maximum.
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		// Checks if each element is greater than current max.
		// If it is, that element becomes current max.
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}

double arrayMean(int arr[], int n) {
	int sum = 0;
	// If there are no elements, the mean is zero.
	if (n == 0) return 0;
	// First sum together all the elements.
	for (int i = 0; i < n; i++) {
		sum += arr[i];
	}
	// Then divides by the number of elements
	return (((double) sum) / ((double) n));
}

void ascendingSeq(int arr[], int n) {
	// Since this for loop goes through an 
	// ascending sequence of indices, we can just
	// set the array elements equal to the index.
	for (int i = 0; i < n; i++) {
		arr[i] = i;
	}
}		

/**
 * @brief Sets up and runs an array example.
 */
int main(int argc, char ** argv)
{

    /*-------- CHANGE NOTHING BELOW THIS LINE FOR PART 1 --------*/
    int test_values[TEST_SIZE];
    int real_size;

    // seed the PRNG
    srand(time(nullptr));

    // initialize the test array to garbage
    for (int i = 0; i < TEST_SIZE; i++)
    {
        test_values[i] = rand();
    }

    // determine a real size
    real_size = TEST_SIZE - (rand() % 20);

    // initialize the meaningful part of the test array to random numbers
    // all of which are less than one million
    for (int i = 0; i < real_size; i++)
    {
        test_values[i] = rand() % 1000000;
    }
    /*-------- CHANGE NOTHING ABOVE THIS LINE FOR PART 1 --------*/

    for (int i = 0; i < real_size; i++) {
		cout << " " << test_values[i] << endl;
	}
	cout << "Max value: " << arrayMax(test_values, real_size) << endl;
	cout << "Mean: " << arrayMean(test_values, real_size) << endl;
	ascendingSeq(test_values, real_size);
	cout << "A new ascending sequence: " << endl;
	for (int i = 0; i < real_size; i++) {
		cout << " " << test_values[i] << endl;
	}
}
