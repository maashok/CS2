#include "tsp-ga.hh"
#include <ctime>

using namespace std;

// Usage statement - if any errors in arguments
void usage(const char *progName) {
    cout << "usage:  " << progName << " pop gen keep mut" << endl;
    cout << "\tpop is positive integer" << endl;
    cout << "\tgen is positive integer" << endl;
    cout << "\tkeep is floating point between 0 and 1" << endl;
    cout << "\tmut is nonnegative floating point value" << endl;
}


int main (int argc, char **argv) {
	// Check if correct number of arguments are passed in
    if (argc != 5) {
        usage(argv[0]);
        return 1;
    }
    int population, generations, keep, mutate;
    // Convert command line arguments to integers/floats
    // If out of correct range, print usage message and quit
    if (atoi(argv[1]) > 0)
        population = atoi(argv[1]);
    else {
		usage(argv[0]);
        return 1;
    }
    if (atoi(argv[2]) > 0)
        generations = atoi(argv[2]);
    else {
		usage(argv[0]);
        return 1;
    }
    if (atof(argv[3]) <= 1 && atof(argv[3]) >= 0)
        keep = atof(argv[3]) * population;
    else {
		usage(argv[0]);
        return 1;
    }
    if (atof(argv[4]) >= 0)
        mutate = atof(argv[4]) * population;
    else {
		usage(argv[0]);
        return 1;
    }
    

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
    
    srand(time(nullptr));
    
    // Find the shortest path to travel through all the points in a round
    // trip
    TSPGenome shortest = findAShortPath(points, population, generations, 
				keep, mutate);
    vector<int> path = shortest.getOrder();
    // Output the shortest path order and distance to the user
    cout << endl << "Best order:  [";
    for (unsigned int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i != path.size() - 1)
            cout << " ";
        else
            cout << "]" << endl;
    }
    cout << "Shortest distance:  " << shortest.getCircuitLength() << endl;
    return 0;
}
