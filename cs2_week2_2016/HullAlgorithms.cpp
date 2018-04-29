/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (implementation).
 *
 */
#include "HullAlgorithms.h"

#define PI 3.14159265

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to HullAlgorithms.h if you write a helper function!
 *
 * Our reference implementation has four helper functions and the function(s)
 * copied over from angleSort.cpp.
 */

/**
 * 1. Start with a point we know is on the convex hull - we can use the
 * leftmost point - and add it to the convex hull
 * 2. Check all remaining points
 * 		a) Find the point which has the smallest angle between a line
 * 			connecting these two points and a vertical line going
 * 			through the starting point.
 * 		b) This point will be the next point on the convex hull	
 * 				(It will not have any points lying to the left of the 
 * 					line connecting the two points)
 * 		c) This point will now be used as the new starting point, and
 * 			start from step 1 with this point.
 * 3. End when the starting point is the same as the leftmost point.
 */
void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app)
{
	// A point that is definitely on the hull is the left most point
    unsigned int leftPt = leftMost(points);
    // Initialize a variable to check when the hull has started to move
    // in the negative x direction
	bool startNeg = false;
    app->add_to_hull(points[leftPt]);
    unsigned int startPt = leftPt;
    // Save a list of points on the hull to avoid repetition
    vector<int> onHull;
    int whereDx = -1;
    while (true) {
		// When finding the minimum angle point, we have to choose one
		// point to start with for comparisons. There are certain conditons
		// it must meet
		unsigned int smallestAngle = 0;
		while (smallestAngle < points.size() - 1) {
			// This point can't already be on the hull
			if (checkOnHull(smallestAngle, onHull)) {
				smallestAngle ++;
			}
			// This point can't be the left-most point itself
			// if we have not gone around the hull
			else if (startPt == leftPt && smallestAngle == leftPt) {
				smallestAngle ++;
			}
			// It can't move in the positive x direction if we have already
			// started moving in the negative x direction
			else if (startNeg && dxPos(points[startPt], points[smallestAngle])) {
				if (points[smallestAngle]->x - points[startPt]->x == 0) {
					whereDx = smallestAngle;
				}
				smallestAngle ++;
			}
			else break;
		}
		if (whereDx >= 0 && (startNeg && dxPos(points[startPt], points[smallestAngle]))) {
			smallestAngle = whereDx;
		}
		// Finds the size of the angle between this point that we have
		// chosen to compare other points to and the start point
		double smallAng = angle(points[startPt], points[smallestAngle]);
		// Actually finds the ppint with the smallest angle, taking into
		// account the checks from before
		for (unsigned int i = 1; i < points.size(); i++) {
			if (checkOnHull(i, onHull) || i == startPt) continue;
			if (startNeg && dxPos(points[startPt], points[i]))
				continue;
			double currentAng = angle(points[startPt], points[i]);
			if (currentAng < smallAng) {
				smallestAngle = i;
				smallAng = angle(points[startPt], points[smallestAngle]);
			}
		}
		// Adds this point to the hull
		app->add_to_hull(points[smallestAngle]);
		onHull.push_back(smallestAngle);
		// If we have started moving in the negative direction
		if (!startNeg && !dxPos(points[startPt], points[smallestAngle]))
			startNeg = true;
		// Check if the hull has ended
		if (points[smallestAngle]->x == points[leftPt]->x &&
				points[smallestAngle]->y == points[leftPt]->y) {
					return;
		}
		// Make the start point the point we just added
		startPt = smallestAngle;
	}
}

/**Check if a point is already on the hull, given the point to check
 * and the vector of indices on the hull.
 */
bool checkOnHull(int pt, vector<int> hull) {
	for (unsigned int i = 0; i < hull.size(); i++) {
		if (pt == hull[i]) return true;
	}
	return false;
}

/** Checks if going from the start point to the next point makes moving
 * in the positive (true) or negative (false) x direction.
 */
bool dxPos(Tuple *start, Tuple *next) {
	double dx = (double) (next->x - start->x);
	return dx >= 0;
}

/** Finds the left-most point in the set of points to start off the 
 * hull.
 */
int leftMost(vector<Tuple*> points) {
	int leftx = 0;
	for (unsigned int i = 1; i < points.size(); i++) {
		if (points[i]->x < points[leftx]->x) leftx = i;
	}
	return leftx;
}

/** Finds the angle between two points, looking at the angle from the 
 * positive y-axis going through the start point. Depending on what
 * axis the point is in, an amount is added, making sure the angle goes
 * from 0 to 2pi degrees.
 */
double angle(Tuple* start, Tuple*next) {
	// Finds the dx and dy corresponding to these two points
	double dx = (double) (next->x - start->x);
	double dy = (double) (next->y - start->y);
	
	// If it is the same point, then consider the angle as being really
	// large so it is not considered as a small angle
	double angle = 3*PI;	
	// First quadrant point
	if (dx >= 0 && dy < 0) {
		angle = atan(abs(dx/dy));
	}
	// Fourth quadrant point
	else if (dx > 0 && dy >= 0) {
		angle = PI/2 + atan(abs(dy/dx));
	}
	// Third quadrant point
	else if (dx <= 0 && dy > 0) {
		angle = PI + atan(abs(dx/dy));
	}
	// Second quadrant point
	else if (dx < 0 && dy <= 0) {
		angle = 3*PI/2 + atan(abs(dy/dx));
	}	
	return angle;
}


 /**
 * Steps to Graham Scan
 * 1. Find the lowest point in a set of points - point P
 * 			This point must be on convex hull.
 * 2. Sort the other points with respect to the angle formed by
 * the horizontal line crossing P and the line joining P at each point.
 * 3. Consider points in the sorted list in sequence. 
 * 4. Each of these points onto the convex hull, making sure that the
 *    last three points make a left turn. If they do, keep going by
 *    adding the next point. Otherwise, remove the last points from
 *    the hull until there is a left turn again, and move on to the 
 *    next point to try.
 * 5. Stop when the last point added is the starting point
 */
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app)
{
	// Start with the lowest point which will be on the hull
	int lowIndex = lowestPt(points);
	Tuple *lowest = points[lowIndex];
	// We don't want to consider this point anymore
	points.erase(points.begin() + lowIndex);
	vector<Tuple*> onHull;
	onHull.push_back(lowest);
	// Find the angle that each point makes with the lowest point, and
	// sort the points in ascending angle order
	vector<double> angles;
	for (unsigned int i = 0; i < points.size(); i++)
		angles.push_back(points[i]->angle_wrt_pt(lowest));
	sort(points, angles, 0, points.size() - 1);
	onHull.push_back(points[0]);
	// To go through the hull, use indices indexH to iterate through
	// the points on the hull, and indexP to iterate through all of
	// the points
	int indexH = 2;
	unsigned int indexP = 1;
	while(indexP < points.size()) {
		// If there is a right turn, we must take out the second to last
		// point added
		while (indexP < points.size() && indexH >=2 && rightTurn(onHull[indexH-2], onHull[indexH-1], points[indexP])){
			onHull.pop_back();
			onHull.push_back(points[indexP]);
			indexH--;
			// If there are still right turns, more backtracking is necessary
			while (rightTurn(onHull[indexH-2], onHull[indexH - 1], onHull[indexH])) {
				indexH--;
				Tuple *top = onHull[onHull.size()-1];
				onHull.pop_back();
				onHull.pop_back();
				onHull.push_back(top);
			}
			// Check if the last point on the hull is the one with
			// the largest angle, in which case we are done, and can 
			// add all the points to the hull on the GUI
			if (onHull[onHull.size() - 1]->x == points[points.size() - 1]->x
			&& onHull[onHull.size() - 1]->y == points[points.size() - 1]->y) {
				addToHull(onHull, lowest, app);
				return;
			}
			// Reset indexH to the number of points on the hull
			indexH = onHull.size();
			indexP++;
		}
		// Add a point to the hull if it causes a left turn
		if (points[indexP] != onHull[onHull.size() - 1]) onHull.push_back(points[indexP]);
		// Check again if we are done with the hull, and draw it if done
		if (points[indexP]->x == points[points.size() - 1]->x
		&& points[indexP]->y == points[points.size() - 1]->y) {
			addToHull(onHull, lowest, app);
			return;
		}
		indexH++;
		indexP ++;
	}
	// At the end, if all points have been checked, draw it
	addToHull(onHull, lowest, app);
}

/** Find the lowest point in a set of points. If the lowest points
 * share the same y-coordinate, then the one with the lower x-coordinate
 * is used.
 */
int lowestPt(vector<Tuple*> &points) {
	int lowy = 0;
	for (unsigned int i = 1; i < points.size(); i++) {
		if (points[i]->y > points[lowy]->y) lowy = i;
		else if (points[i]->y == points[lowy]->y) {
			if (points[i]->x < points[lowy]->x)
				lowy = i;
		}
	}
	return lowy;
} 

/** Check if the three points create a right turn, using the cross
 * product.
 */
bool rightTurn(Tuple *Pt1, Tuple *Pt2, Tuple *Pt3) {	
	int zCoord = (Pt2->x- Pt1->x)*(Pt3->y-Pt1->y) - (Pt2->y-Pt1->y)*(Pt3->x-Pt1->x);
	return zCoord > 0;
}

/** Swap two points and their corresponding angles as part of the
 * quick sort in place algorithm
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

/** Use quick sort in place to sort all the points by their angles.
 */
void sort(vector<Tuple*> &points, vector<double> &angles, int left, int right)
{
	// End recursion when the list is only one element long
	if (left >= right) return;
	// The pivot is the middle point
	double pivot = angles[(left + right)/2];
	int i = left, j = right;
	while (i <= j) {
		// Goes through and finds points that are not on the side of
		// the pivot they should be on, and swaps them if it can
		while (angles[i] < pivot) i++;
		while (angles[j] > pivot) j--;
		if (i <= j) {
			swap(points, angles, i, j);
			i++;
			j--;
		}
	}
	// Recursiely call quicksort on these two lists.
	if (left < j) sort(points, angles, left, j);
	if (i < right) sort(points, angles, i, right);
    return;
}

/** Prints the points on the hull for debugging purposes
 */
void printHull(vector<Tuple*> hull) {
	std::cout <<"Printing hull";
	for (unsigned int i = 0; i < hull.size(); i++) {
		std::cout << "(" << hull[i]->x << "," << hull[i]->y << ")   ";
	}
	std::cout << std::endl;
}

/** Adds all the points to the ConvexHullApp for the GUI when the hull
 *is ended
 */
void addToHull(vector<Tuple*> hull, Tuple *lowest, ConvexHullApp *app) {
	for (unsigned int i = 0; i < hull.size(); i++)
		app->add_to_hull(hull[i]);
	app->add_to_hull(lowest);
}
