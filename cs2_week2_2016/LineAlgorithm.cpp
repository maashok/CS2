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
	/** INITIAL SUBMISSION _ DOESN'T CONSIDER ALL OCTANTS */
/**	// Stores the points on the line
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
    // Go through every integer x coordinate from x0 to y0
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
 */
	/** VERSION USING WIKIPEDIA ALGORITHM  - works for all 8 octants*/
	
	// Vector to hold all points to be plotted to form line
	vector <Tuple> plot;
	// Find what octant the line will be in and convert the endpoints to
	// be in the first octant (this is where Bresenham's Line Algorithm
	// works) rather than the current octant
	int octantNum = findOctant(p1, p2);
	p1 = switchToOctantZero(octantNum, p1.x, p1.y);
	p2 = switchToOctantZero(octantNum, p2.x, p2.y);
	
	// Find the absolute value of the slope based on the new first octant version
	double slope = abs((double)(p2.y - p1.y) / (double)(p2.x - p1.x));
	
	// The error starts at the slope - 0.5 (The error always ranges from -0.5 to 0.5)
	// Since slope is between 0 and 0.5, the error will start out in the bottom
	// half of this range
	double error = slope - 0.5;
	// Start out with point p1
	int yPt = p1.y;
	int xPt = p1.x;
	// Go through all the x coordinates from p1 to p2
	while (xPt <= p2.x) {
		// Plot the corrected octant point that is part of the line
		// between p1 and p2
		plot.push_back(switchFromOctantZero(octantNum, xPt, yPt));
		// Add the slope (extra y distance) from going 1 unit to the right
		// to the error that is accumulating for y direction (we can only
		// plot integer y coordinates so can't plot slope directly)
		error += slope;
		// If the error is past the maximum, increment the y coordinate
		// to move the line up (in the first octant), and adjust the error
		// to account for this amount being taken care of
		if (error >= 0.5) {
			yPt ++;
			error --;
		}
		// Move to next x coordinate between p1 and p2
		xPt ++;
	}
	// Plot the points
	return plot;
		
}	

/** This function finds out what octant the line between p1 and p2 is
 *  in based on the relative sizes and signs of the x and y coordinate
 *  differences
 * 
 */
int findOctant(Tuple p1, Tuple p2) {
	int octantNum;
	// Distance to travel in y and x directions to get from p1 to p2
	int delY = p2.y - p1.y;
	int delX = p2.x - p1.x;
	// Go through each of possibilities for x and y signs and relative sizes
	// Assign octant number based on the line orientation in the following
	// coordinate axis
	/** \2|1/
	  	3\|/0
	 	-----
	 	4/|\7
	 	/5|6\
	*/
	
	if (delX < 0) {
		if (delY > 0) {
			if (abs(delY) < abs(delX))
				octantNum = 3;
			else
				octantNum = 2;
		}
		else {
			if (abs(delY) < abs(delX))
				octantNum = 4;
			else
				octantNum = 5;
		}
	}
	else {
		if (delY > 0) {
			if (abs(delY) < abs(delX))
				octantNum = 0;
			else
				octantNum = 1;
		}
		else {
			if (abs(delY) < abs(delX))
				octantNum = 7;
			else
				octantNum = 6;
		}
	}
	return octantNum;
}

/** Convert a point in the coordinate axis to a point in the first octant
 *  Used as input for single-octant drawer
 */
Tuple switchToOctantZero(int octant, int x, int y) {
	// Depending on what octant it is, adjust x and y coordinates to
	// both be positive and for x > y
	switch(octant) {
		case 0: return Tuple(x, y);
		case 1: return Tuple(y, x);
		case 2: return Tuple(y, -x);
		case 3: return Tuple(-x, y);
		case 4: return Tuple(-x, -y);
		case 5: return Tuple(-y, -x);
		case 6: return Tuple(-y, x);
		case 7: return Tuple(x, -y);
	}
	return Tuple(x, y);
}

/** Convert a point in the first octant to a point in some other named
 *  octant. Used on output of single-octant drawer
 */
Tuple switchFromOctantZero(int octant, int x, int y) {
	// Depending on what octant the point is originally in, adjust the
	// x and y coordinates to be the correct signs and relative sizes
	switch(octant) {
		case 0: return Tuple(x, y);
		case 1: return Tuple(y, x);
		case 2: return Tuple(-y, x);
		case 3: return Tuple(-x, y);
		case 4: return Tuple(-x, -y);
		case 5: return Tuple(-y, -x);
		case 6: return Tuple(y, -x);
		case 7: return Tuple(x, -y);
	}
	return Tuple(x, y);
}
