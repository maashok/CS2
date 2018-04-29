#include <algorithm>
#include <random>
#include <cstdlib>
#include <set>
#include "Point.hh"
#include <vector>
#include <iostream>
using namespace std;

// Genome class that solves the Travelling Salesman Problem
class TSPGenome {

private:
  vector<int> pathOrder;
  double circuitLength;

public:
  // Constructors
  TSPGenome(int numPoints);                      // random initialize constructor
  TSPGenome(const vector<int> &order);          // specified order constructor

  // Destructor
  ~TSPGenome();

  // Accessor methods
  vector<int> getOrder() const;
  double getCircuitLength() const;
  
  // Compute circuit length
  void computeCircuitLength(const vector<Point> &points);
  
  // Mutate the genome
  void mutate();
};

// Cross link two genomes together
TSPGenome crossLink(const TSPGenome &g1, const TSPGenome &g2);

// Find a short path between the points through the genetic algorithm
TSPGenome findAShortPath(const vector<Point> &points,
                           int populationSize, int numGenerations,
                           int keepPopulation, int numMutations);
                           
// Helper function to decide if path of one genome is shorter
bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2);
