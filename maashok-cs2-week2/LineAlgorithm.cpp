/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief Student implementation of line algorithm.
 *
 */
#include "LineAlgorithm.h"

/**
 * Bresenham's line algorithm draws an integer path between two points,
 * such that all points drawn in between are adjacent and have integer
 * coordinates
 */
vector<Tuple> line(Tuple p1, Tuple p2)
{
	// Stores the points on the line
    vector<Tuple> v;
    // If p2 is to the left of p1, swap them so that two cases of 
    // traversing through the points on the line need not be considered
    if (p2.x < p1.x) {
		Tuple temp = p1;
		p1 = p2;
		p2 = temp;
	}
	// Store the x and y coordinates of the two points
    int x0 = p1.x;
    int y0 = p1.y;
    int x1 = p2.x;
    int y1 = p2.y;
    // If the line is vertical, slope will be infinity. To avoid
    // the unpredictable behavior associated with that, we can just
    // draw points with varying y coordinates to connect the two points
    // if they have the same x coordinate
    if (x0 == x1) {
		for(int y = y0; y < y1; y++) {
			struct Tuple vertPt(x0, y);
			v.push_back(vertPt);
		}
	}
	// Calculate the slope of the perfect line between the two points
    double slope = (double)(y1 - y0)/(double)(x1 - x0);
    // Variable to accumulate error. If error passes its range of 
    // -0.5 to 0.5, the next point will be moved up or down an integer
    // y coordinate accordingly, to adjust for this accumulation of
    // error from previous points
    double error = 0.0;
    // Go through every integer x coordinate from x0 to x1
    for (int x = x0; x <=x1; x++) {
		// Where the point actually should be, but this is rounded since
		// we can only plot integer coordinates
		double actualPt = (slope)*(x - x0) + y0;
		int rounded = round(actualPt);
		error += (actualPt-rounded);
		// Account for accumulation of error
		if (error >= 0.5) {
			rounded++;
		}
		else if(error <= 0.5) {
			rounded--;
		}
		// Add the integer point to the set of points to be plotted
		struct Tuple newPt(x, rounded);
		v.push_back(newPt);
	}
		
    return v;
}
