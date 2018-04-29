#include <vector>
#include <algorithm>
#include <iostream>
#include "Point.hh"

using namespace std;

// Computes the total length of the path when travelling the given points
// in the specified order. Length is calculated for a complete round trip.
double circuitLength(const vector<Point> &points, const vector<int> &order) {
	vector<int>::const_iterator it = order.begin();
	double length = 0;
	// Iterate through every point to compute distance to next point
	// and add it to a total distance
	while (it + 1 != order.end()) {
		length += points[*it].distanceTo(points[*(it + 1)]);
		it++;
	}
	
	// If there are 2 or more points, add in the distance from the last
	// point back to the first (round trip)
	if (order.size() > 1) {
		length += points[order[order.size() - 1]].distanceTo(points[order[0]]);
	}
	return length;
}

// Finds the shortest path to visit all the given points in a round trip
// when visiting each point once. Uses brute force to solve the Traveling
// Salesman Problem.
vector<int> findShortestPath(const vector<Point> &points) {
	vector<int> order;
	unsigned int count = 0;
	// Start out with the simplest order of traversal --> 1st to last
	while (count < points.size()) {
		order.push_back(count);
		count += 1;
	}
	
	// Find the round trip distance of this traversal and make it the best
	// order for now
	double shortestDistance = circuitLength(points, order);
	vector<int> bestPath = order;
	
	// Iterate through all permutations of the order
	do {
		// For each order get the round trip distance and check if it
		// is smaller than the current shortest distance
		double dist = circuitLength(points, order);
		if (dist < shortestDistance) {
			shortestDistance = dist;
			bestPath = order;
		}
	} while(next_permutation(order.begin(), order.end()));
	return bestPath;
}

int main () {
	int x, y, z;
	// Get user input on the number of points and the x,y,and z coordinates
	// of the points
	unsigned int numPoints;
	cout << "How many points?  ";
	cin >> numPoints;
	vector<Point> points;
	for (unsigned int i = 0; i < numPoints; i++) {
		cout << endl << "Point " << i << ":  ";
		cin >> x >> y >> z;
		points.push_back(Point(x, y, z));
	}
	
	// Find the shortest path to travel through all the points in a round
	// trip
	vector<int> path = findShortestPath(points);
	
	// Output the shortest path order and distance to the user
	cout << endl << "Best order:  [";
	for (unsigned int i = 0; i < path.size(); i++) {
		cout << path[i];
		if (i != path.size() - 1)
			cout << " ";
		else
			cout << "]" << endl;
	}
	cout << "Shortest distance:  " << circuitLength(points, path) << endl;
	return 0;
}
