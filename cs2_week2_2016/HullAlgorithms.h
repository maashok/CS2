/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The gift wrapping and Graham scan convex hull algorithms
 * (header file).
 *
 */

#include <vector>
#include <stack>
#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include "ConvexHullApp.h"
#include "structs.h"
#include <math.h>

using namespace std;

void DoGiftWrap(vector<Tuple*> points, ConvexHullApp *app);
int leftMost(vector<Tuple*> points);
bool checkOnHull(int pt, vector<int> hull);
bool dxPos(Tuple *start, Tuple *next);
double angle(Tuple* start, Tuple *next);
void DoGrahamScan(vector<Tuple*> points, ConvexHullApp *app);
void swap(vector<Tuple*> &points, vector<double> &angles, int i, int j);
void sort(vector<Tuple*> &points, vector<double> &angles, int left, int right);
int lowestPt(vector<Tuple*> &points);
bool rightTurn(Tuple *Pt1, Tuple *Pt2, Tuple *Pt3);
void printHull(vector<Tuple*> hull);
void addToHull(vector<Tuple*> hull, Tuple *lowest, ConvexHullApp *app);
