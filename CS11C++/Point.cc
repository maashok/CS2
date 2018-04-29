#include "Point.hh"
#include <cmath>

// Default constructor: initializes the point to (0, 0, 0).
Point::Point() {
  x_coord = 0;
  y_coord = 0;
  z_coord = 0;
}

// Initializes the point to (x, y, z).
Point::Point(double x, double y, double z) {
  x_coord = x;
  y_coord = y;
  z_coord = z;
}

// Destructor - Point allocates no dynamic resources.
Point::~Point() {
  // no-op
}

// Mutators:

void Point::setX(double val) {
  x_coord = val;
}

void Point::setY(double val) {
  y_coord = val;
}

void Point::setZ(double val) {
  z_coord = val;
}

// Accessors:

double Point::getX() const {
  return x_coord;
}

double Point::getY() const {
  return y_coord;
}

double Point::getZ() const {
  return z_coord;
}

// Distance between points:

double Point::distanceTo(const Point &pt) const {
  // distance = sqrt((x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2)
  double x_comp = pt.getX() - x_coord;
  double y_comp = pt.getY() - y_coord;
  double z_comp = pt.getZ() - z_coord;
  return sqrt(x_comp * x_comp + y_comp * y_comp + z_comp * z_comp);
} 
