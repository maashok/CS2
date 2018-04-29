#include <cmath>
#include <iostream>
#include "Point.hh"

using namespace std;

// Compute area of triangle in 3-D space given the three vertices
double computeArea(Point &a, Point &b, Point &c){
  // Compute side lengths of each edge
  double len1 = a.distanceTo(b);
  double len2 = b.distanceTo(c);
  double len3 = c.distanceTo(a);
  // Use Heron's formula for area of triangle
  // Area = sqrt(s(s-a)(s-b)(s-c)), s = (a+b+c)/2
  double semiperim = (len1 + len2 + len3)/2;
  return sqrt(semiperim * (semiperim - len1) * (semiperim - len2) * 
			(semiperim - len3));
}

int main(){
  // Get coordinates of each point from user and initialize
  cout << "Point 1:  ";
  double x, y, z;
  cin >> x >> y >> z;
  Point p1 = Point(x, y, z);
  cout << "Point 2:  ";
  cin >> x >> y >> z;
  Point p2 = Point(x, y, z);
  cout << "Point 3:  ";
  cin >> x >> y >> z;
  Point p3 = Point(x, y, z);
  // Compute area of triangle with entered vertices
  cout << "Area is:  " << computeArea(p1, p2, p3) << endl;
  return 0;
}
