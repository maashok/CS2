#include "tsp-ga.hh"

// Random constructor: initializes a random path order
// for a given number of points
TSPGenome::TSPGenome(int numPoints) {
    int count = 0;
    // Start out with the simplest order of traversal --> 1st to last
    while (count < numPoints) {
        pathOrder.push_back(count);
        count += 1;
    }
    // Shuffle the path order randomly
    std::random_device rd;
    std::mt19937 g(rd());
    shuffle(pathOrder.begin(), pathOrder.end(), g);
    // Start with large circuit length
    circuitLength = 1e9;
}

// Constructor: initializes specified path order
TSPGenome::TSPGenome(const vector<int> &order) {
    // Set path order and large circuit length
    pathOrder = order;
    circuitLength = 1e9;
}

// Destructor not implemented
TSPGenome::~TSPGenome() {
    
}

// Return the path order
vector<int> TSPGenome::getOrder() const {
    return pathOrder;
}

// Calculate circuit length of a round trip of points in saved order
void TSPGenome::computeCircuitLength(const vector<Point> &points) {
    vector<int>::const_iterator it = pathOrder.begin();
    double length = 0;
    // Iterate through every point to compute distance to next point
    // and add it to a total distance
    while (it + 1 != pathOrder.end()) {
        length += points[*it].distanceTo(points[*(it + 1)]);
        it++;
    }
    
    // If there are 2 or more points, add in the distance from the last
    // point back to the first (round trip)
    if (pathOrder.size() > 1) {
        length += points[pathOrder[pathOrder.size() - 1]].
                    distanceTo(points[pathOrder[0]]);
    }
    circuitLength = length;
}

// Return the circuit length
double TSPGenome::getCircuitLength() const {
    return circuitLength;
}

// Mutate a genome by introducing a random switch into it
void TSPGenome::mutate() {
    int first = 0, second = 0;
    // Find two random indices in the path order
    while (first == second) {
        first = rand() % pathOrder.size();
        second = rand() % pathOrder.size();
    }
    // Switch the order of the points at these indices
    int temp = pathOrder[first];
    pathOrder[first] = pathOrder[second];
    pathOrder[second] = temp;
}

// Cross two genomes to generate offspring
TSPGenome crossLink(const TSPGenome &g1, const TSPGenome &g2) {
    // Initialize the orders of the parents and offspring
    vector<int> offspringOrder;
    vector<int> g1Order = g1.getOrder();
    vector<int> g2Order = g2.getOrder();
    // Create a set to store all of g2's points not added in
    set<int> g2Left(g2Order.begin(), g2Order.end());
    int i = rand() % g1Order.size();
    // Add a random number of points from g1 to the offspring and make sure
    // not to add the same from g2 later
    for (int j = 0; j < i; j ++) {
        offspringOrder.push_back(g1Order[j]);
        g2Left.erase(g1Order[j]);
    }
    // Add all points left in g2 to the offspring and create a offspring genome
    for(std::set<int>::iterator it = g2Left.begin(); it != g2Left.end(); it++)
        offspringOrder.push_back(*it);
    TSPGenome offspring (offspringOrder);
    return offspring;
}

// Finds a short path given a set of points as well as constraints to perform
// the genetic algorithm
TSPGenome findAShortPath(const vector<Point> &points,
                           int populationSize, int numGenerations,
                           int keepPopulation, int numMutations) {
    // Initialize the population with the given number of random genomes
    vector<TSPGenome> population;
    for (int i = 0; i < populationSize; i++) {
        TSPGenome random (points.size());
        population.push_back(random);
    }
    int gen = 0;
    // Iterate through given number of generations
    while (gen < numGenerations) {
        // Compute the circuit length for each genome
        for (int i = 0; i < populationSize; i++) {
            population[i].computeCircuitLength(points);
        }
        // Sort the genomes by circuit length
        sort(population.begin(), population.end(), isShorterPath);
        // Print out circuit length every 10th iteration for debugging purposes
        if (gen % 10 == 0) {
            cout << "Generation " << gen << ":  shortest path is "
                 << population[0].getCircuitLength() << endl;
        }
        // Keep the given percentage of the population
        // For the rest, replace with new offspring by crossing the fit members 
        // of the population
        for (int j = keepPopulation; j < populationSize; j++) {
            // Find two different parent indices from the population that
            // is kept due to high fitness
            int g1 = rand() % keepPopulation;
            int g2;
            do {
                g2 = rand() % keepPopulation;
            } while (g1 == g2);
            // Cross these two fit parents to get fit offspring
            population[j] = crossLink(population[g1], population[g2]);
        }
        // Create the given number of mutations
        for (int j = 0; j < numMutations; j++) {
            int mut = 1 + rand() % (populationSize - 1);
            population[mut].mutate();
        }
        gen ++;
    }
    // After going through the given number of generations, return the first
    // element of the population which is most fit
    return population[0];
}
    
    
// Find if one path is shorter than another based on their circuit lengths
bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2) {
    return g1.getCircuitLength() < g2.getCircuitLength();
}
