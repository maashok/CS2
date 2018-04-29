/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief An example of sorting (x, y) pairs by angle.
 *
 */
#include "structs.h"
#include <vector>

#include <iostream>

using namespace std;

/**
 * Swap two elements of points and angles, given the indices to switch
 */
void swap(vector<Tuple*> &points, vector<double> &angles, int i, int j) {
	// Switch the elements at the indices of angles
	double temp1 = angles[i];
	angles[i] = angles[j];
	angles[j] = temp1;

	// Switch the elements at the indices of points
	Tuple* temp2 = points[i];
	points[i] = points[j];
	points[j] = temp2;
}

/**
 * Uses quick sort in place to sort an array of points by their angles
 * in ascending order. It takes in vectors of points and their corresponding
 * angles, with the angles pointing to the point with the same index in
 * that vector.
 */
 
void sort(vector<Tuple*> &points, vector<double> &angles, int left, int right)
{
	// Ends when size of vector is one
	if (left >= right) return;
	// Chooses the pivot to be the midpoint
	double pivot = angles[(left + right)/2];
	int i = left, j = right;
	while (i <= j) {
		// Finds the point for which the angle is greater than the
		// pivot value in the first half of the vector
		while (angles[i] < pivot) i++;
		// Finds the point for which the angle is less than the pivot
		// value in the second half of the vector
		while (angles[j] > pivot) j--;
		// As long as the first coordinate is less than the second,
		// swaps them
		if (i <= j) {
			swap(points, angles, i, j);
			i++;
			j--;
		}
	}
	// Recursively use quicksort in place to sort the two halves.
	if (left < j) sort(points, angles, left, j);
	if (i < right) sort(points, angles, i, right);
    return;
}


int main(int argc, char const *argv[])
{
    vector<double> angles {4.2, 2.8, 1.4, 5.0, 3.3};
    vector<Tuple*> points;
    // Print the initial points and angles
    for (unsigned int i = 0; i < angles.size(); ++i)
    {
        points.push_back(new Tuple(i, i));
    }
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        printf("%g\n", *i);
    }

    // Now sort them with respect to angle (points[i] corresponds to angle[i])

    /** THIS IS THE ONLY LINE OF THE MAIN LOOP YOU NEED TO MODIFY. */
    sort(points, angles, 0, angles.size() - 1);
    /** REPLACE THE LINE ABOVE WITH A CALL TO YOUR SORTING FUNCTION. */

    // and print out the new points and angles
    for (vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    {
        (*i)->printTuple();
    }
    for (vector<double>::iterator i = angles.begin(); i != angles.end(); ++i)
    {
        printf("%g\n", *i);
    }

    // Don't want to leak memory...
    // Either of the below implementations works
    // for (std::vector<Tuple*>::iterator i = points.begin(); i != points.end(); ++i)
    // {
    //     delete (*i);
    // }
    for (unsigned int i = 0; i < points.size(); ++i)
    {
        delete points[i];
    }
    return 0;
}
