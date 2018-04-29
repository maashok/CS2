/**
 * @file QuadtreeNode.cpp
 * @author Ellen Price <<eprice@caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright see License section
 *
 * @brief Functions for a quadtree node.
 * 
 * @section License
 * Copyright (c) 2013-2014 California Institute of Technology.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met:
 * 
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above
 *   copyright notice, this list of conditions and the following disclaimer
 *   in the documentation and/or other materials provided with the
 *   distribution.
 * * Neither the name of the  nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * The views and conclusions contained in the software and documentation are those
 * of the authors and should not be interpreted as representing official policies, 
 * either expressed or implied, of the California Institute of Technology.
 * 
 */
#include <cstdio>
#include "QuadtreeNode.h"


/**
 * @brief Initializes the quadtree node.
 *
 * @param size The size of the region this node encloses (length of
 * a side of the square).
 *
 * @param ul The coordinate of the upper-left corner of this node's
 * region.
 */
QuadtreeNode::QuadtreeNode(float size, coordinate *ul)
{
    this->size = size;
    coordinate *br = new coordinate(ul->x + size, ul->y + size);
    this->box = new rect(ul, br);
    // Start the children off as NULL, they will only be initialized
    // if there is a need for them
    NW = NULL;
	NE = NULL;
	SW = NULL;
	SE = NULL;
	// When the node is created, there is no point in it.
	point = NULL;
}


/**
 * @brief Deinitializes a quadtree node.
 */
QuadtreeNode::~QuadtreeNode()
{
    if (box)
    {
        delete box->ul;
        delete box->br;
        delete box;
    }
    // Recursively deletes the memory of the children
    if (NW) {
		delete NW;
		delete NE;
		delete SW;
		delete SE;
	}
	if (point)
		delete point;
}


/**
 * @brief Gets the rectangle associated with this node.
 *
 * @return The bounding box of this node.
 */
rect *QuadtreeNode::NodeRect()
{
    return box;
}


/**
 * @brief Inserts a point into the quadtree.
 *
 * @param c The point to insert.
 */
 void QuadtreeNode::Insert(coordinate *c)
{
	if (c == NULL) return;
	// The child will have half the side length
	float sizeOfChild = size/2;
	// If the node already has four children, place the point in the
	// correct child
    if(NW != NULL) {
		placePt(c);
	}
	// If the node does not yet have four children, but it already
	// has one point in it (which is the maximum), then we need to
	// split the node into its children
	else if(point != NULL) {
		// Initialize all 4 children
		NW = new QuadtreeNode(sizeOfChild, new coordinate(NodeRect()->ul->x, NodeRect()->ul->y));
		NE = new QuadtreeNode(sizeOfChild, new coordinate(NodeRect()->ul->x + sizeOfChild, NodeRect()->ul->y));
		SW = new QuadtreeNode(sizeOfChild, new coordinate(NodeRect()->ul->x, NodeRect()->ul->y + sizeOfChild));
		SE = new QuadtreeNode(sizeOfChild, new coordinate(NodeRect()->ul->x + sizeOfChild, NodeRect()->ul->y + sizeOfChild));
		// Place the existing point into its correct child node
		placePt(point);
		// Now, the parent node does not have any coordinates in it
		// Each node can either have children, or it can have a point
		// (or it can have neither)
		point = NULL;
		// Place the coordinate that we are trying to place in the correct
		// child node
		placePt(c);
	}
	// Otherwise, if the node has not already been split and there are
	// no other points in the node, then we can just change this node's
	// point to this coordinate. This acts as a base case for the recursive
	// insert function
	else {
		point = c;
	}		
}

/**
 * @brief Places the point in the correct child node(s).
 *
 * @param pt The point to insert.
 */
void QuadtreeNode::placePt(coordinate *pt) {
	// Checks if the point can be inserted in each of the subchildren
	// Depending on whether the point is on the edge or corner of
	// the children, it may be inserted into multiple children
	check(pt, NW);
	check(pt, NE);
	check(pt, SW);
	check(pt, SE);
}

/**
 * @brief If the point can be inserted in a child, inserts it.
 *
 * @param pt The point to insert.
 * @param quad The child node to try inserting the point in
 */
void QuadtreeNode::check(coordinate *pt, QuadtreeNode *quad) {
	// Checks if the point is within the x and y boundaries of this
	// node's rectangle
	if (quad->NodeRect()->ul->x <= pt->x && pt->x <= quad->NodeRect()->br->x) {
		if (quad->NodeRect()->ul->y <= pt->y && pt->y <= quad->NodeRect()->br->y) {
			quad->Insert(pt);
		}
	}
}

/**
 * @brief Gets the list of all rectangles associated with this node and
 * its children.
 *
 * @return A `std::vector` containing all rectangles in the tree.
 */
vector<rect*> QuadtreeNode::ListRectangles()
{
    vector<rect*> boxes;
    // The rectangle of this node itself is associated with the node
	boxes.push_back(box);
	// If this node has children, get the rectangles of the children
	// and add those to the list of rectangles. This will work
	// recursively.
	if (NW != NULL) {
		vector<rect*> NWboxes = NW->ListRectangles();
		vector<rect*> NEboxes = NE->ListRectangles();
		vector<rect*> SWboxes = SW->ListRectangles();
		vector<rect*> SEboxes = SE->ListRectangles();
		boxes.insert(boxes.end(), NWboxes.begin(), NWboxes.end());
		boxes.insert(boxes.end(), NEboxes.begin(), NEboxes.end());
		boxes.insert(boxes.end(), SWboxes.begin(), SWboxes.end());
		boxes.insert(boxes.end(), SEboxes.begin(), SEboxes.end());
	}
    return boxes;
}


/**
 * @brief Gets the list of all points stored in this node and its
 * children.
 *
 * @return A `std::vector` containing all points in the tree.
 */
vector<coordinate*> QuadtreeNode::ListPoints()
{
    vector<coordinate*> points;
    // If there is a point in this node, then that is added to the list,
    // and we don't have to check the children, since there will be none
	if (point != NULL) {
		points.push_back(point);
		return points;
	}
	// Recurseively check the subchildren for their list of points
	// and add them to the list of points
	else if (NW != NULL) {
		vector<coordinate*> NWpoints = NW->ListPoints();
		vector<coordinate*> NEpoints = NE->ListPoints();
		vector<coordinate*> SWpoints = SW->ListPoints();
		vector<coordinate*> SEpoints = SE->ListPoints();
		points.insert(points.end(), NWpoints.begin(), NWpoints.end());
		points.insert(points.end(), NEpoints.begin(), NEpoints.end());
		points.insert(points.end(), SWpoints.begin(), SWpoints.end());
		points.insert(points.end(), SEpoints.begin(), SEpoints.end());
	}
    return points;
}


/**
 * @brief Queries for all points and rectangles that intersect a square
 * region centered on `center` of radius `radius`, in this node and
 * its children.
 *
 * @param center The center of the query region.
 *
 * @param radius The radius of the query region.
 *
 * @return A `query` object encapsulating the results of this query.
 */
query *QuadtreeNode::Query(coordinate *center, float radius)
{
    vector<coordinate*> points;
    vector<rect*> boxes;
    // Gets the list of all points associated with this node and its children
	vector<coordinate*> allPts = ListPoints();
	// Gets the list of all rectangles associated with this node and its children
	vector<rect*> allRects = ListRectangles();
	// For each of the points, checks if the point is within the radius
	// of the center we are checking
	for (unsigned int i = 0; i < allPts.size(); i++) {
		if (isInside(allPts[i], *center, radius)){
			points.push_back(allPts[i]);
			// For each of the points within the radius, find the
			// rectangle it belongs to, by checking if that point
			// is within the radius covered by each rectangle
			for (unsigned int j = 0; j < allRects.size(); j++) {
				float rad = (allRects[j]->br->x - allRects[j]->ul->x)/2;
				coordinate c(allRects[j]->ul->x + rad, allRects[j]->ul->y + rad);
				if(isInside(allPts[i], c, rad))
					boxes.push_back(allRects[j]);
			}
		}
	}
    query *ret = new query(points, boxes);
    return ret;
}

/**
 * @brief Checks if a point is within a given region.
 *
 * @param pt The point to check the region for
 * 
 * @param center The center of the region to check the point in
 * 
 * @param radius The radius (or half the side length) of the square
 * to check in
 */
bool QuadtreeNode::isInside(coordinate *pt, coordinate center, float radius)
{
	// Finds the left, right, top, and bottom edge coordinates of
	// the specified region
	float left = center.x - radius;
	float right = center.x + radius;
	float top = center.y - radius;
	float bottom = center.y + radius;
	// Check if the point's coordinates are within this region
	if (pt->x < right && pt->x > left && pt->y < bottom && pt->y > top)
		return true;
	else return false;
}
