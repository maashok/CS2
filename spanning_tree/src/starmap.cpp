/**
* @file starmap.cpp
* @author Ben Yuan <<byuan@caltech.edu>>
* @version 1.0
* @date 2012-2013
* @copyright see License section
*
* @brief Defines a starmap and its associated capabilities.
*
* @section License
* Copyright (c) 2012-2013 California Institute of Technology.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice, this
*    list of conditions and the following disclaimer.
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
* The views and conclusions contained in the software and documentation are those
* of the authors and should not be interpreted as representing official policies,
* either expressed or implied, of the California Institute of Technology.
*
*/

#include "starmap.hpp"

/**
 * @brief Calculates the shortest path to the destination star.
 *
 * This calculates the shortest path to the destination star based on
 * the metrics provided in the CostSpec.
 *
 * @attention This is a student-written function.
 * Student may implement any shortest-path algorithm.
 * Remember: if implementing A*, don't overestimate the distance to goal.
 *
 * @param[in] src the origin point from which to find a path.
 * @param[in] dest the destination to find a path to.
 * @param[in] costs a cost specification for this calculation.
 *
 * @return a list of stars from the origin to the destination inclusive,
 * along the shortest path available.
 */
 
 
 /**
  * Outline
  * 1) Start at the Source Node
  * 2) Set the shortest distance from the source node to the source
  * node as 0, and the distance from all the other nodes to the source 
  * node as infinity
  * 3) Add all of the stars to a list of stars left to be checked
  * 
  * WHILE list of stars not empty
  * 	Look at star with shortest distance to source
  * 	IF this star = destination star: end WHILE
  * 	Remove this star from list
  * 
  * 	FOR each of neighbors
  * 		Calculate distance if went through current star
  * 		IF this distance less than the distance stored in
  * 			the neighbor to source
  * 				Change distance to this alternate distance
  * 				Change previous star to the current star
  *			END IF
  *		END FOR
  * END WHILE
  * 
  * Start with destination star
  * Save a pointer to that star
  * WHILE star pointing to is not source star
  * 	Add star pointing to to list of shortest path
  * 	Change star pointing to its previous star
  * END WHILE
  * 
  * THIS GIVES US THE SHORTEST PATH USING DIJKSTRA's ALGORITHM 
  */
std::list<Star*> Starmap::shortestPath(Star * src, Star * dest, CostSpec costs)
{

    std::list<Star*> ret;

	//vectorShortestPath(src, dest, costs);
	bHeapShortestPath(src, dest, costs);
	
	
	ret.push_front(dest);
	double cost = 0;
	// Backtrack through the stars to see which one was chosen
	// before in the shortest path
	Star *bt = dest;
	while(bt != src) {
		cost += bt->cartesianDistanceTo(bt->previous);
		bt = bt->previous;
		ret.push_front(bt);
	}
	INFO("Cost: %f", cost);
    return ret;
    
}	

/**
 * @brief Calculates the shortest path to the destination star using
 * a vector to store the list of stars yet to have been seen.
 *
 * @param[in] src the origin point from which to find a path.
 * @param[in] dest the destination to find a path to.
 * @param[in] costs a cost specification for this calculation.
 */
void Starmap::vectorShortestPath(Star *src, Star *dest, CostSpec costs) {
	// Store the list of stars yet to be checked
	std::vector<Star*> options;

	// Set the distance of the source to the source to be zero
	src->distance = 0;
	src->previous = NULL;

	// The distance of all other sources to the star is initially
	// set to infinity
	std::map<int, Star *>::iterator i;
	for (i = stars.begin(); i != stars.end(); i++) {
		Star *curr = i->second;
		if (curr->getID() != src->getID()) {
			curr->distance = std::numeric_limits<double>::infinity();
			curr->previous = NULL;
		}
		options.push_back(curr);
	}
	// While we haven't checked all the stars
	while (!options.empty()) {
		// First start with the star that thinks it is the
		// closest to the source star
		int shortest = minDist(src, options);
		Star *curr = options[shortest];
		// If the star we are checking on this iteration is
		// the destination, we are done
		if (curr->getID() == dest->getID()) break;
		options.erase(options.begin() + shortest);
		
		// For each of the neighbors of the star we are looking at
		for (int j = 0; j < curr->edges.size(); j++) {
			// Calculate what the security and MST multipliers are
			// based on whether an MST edge exists or not, and whether
			// it is enabled, and how dangerous the star is
			double security, costMult;
			if (curr->edges[j]->sec_stat < 0.5) 
				security = costs.lowSecCostMult;
			else security = costs.highSecCostMult;
			if (costs.MSTEnabled && 
					MSTExists(curr->edges[j], curr->mst_edges))
				costMult = costs.costPerMSTEdge;
			else
				costMult = costs.costPerNormalEdge;
				
			// Checks the alternate distance by going through
			// the current star and from there to the neighbor star
			// to see if it is less than the neighbor's star's currrent
			// distance to the source star. If so, we change that
			// distance and save that star's previous star as the
			// current one
			double altDist = curr->distance + 
				curr->cartesianDistanceTo(curr->edges[j])*costMult*security;
			if (altDist < curr->edges[j]->distance) {
				curr->edges[j]->distance = altDist;
				curr->edges[j]->previous = curr;
			}
		}
	}
}

/**
 * @brief Calculates the shortest path to the destination star using
 * a binary min heap to store the list of stars yet to have been seen
 * so the star with smallest distance to the source is at the top.
 *
 * @param[in] src the origin point from which to find a path.
 * @param[in] dest the destination to find a path to.
 * @param[in] costs a cost specification for this calculation.
 */
void Starmap::bHeapShortestPath(Star *src, Star *dest, CostSpec costs) {
	// Store the list of stars yet to be checked
	BHeap *options = new BHeap(stars, src);

	// While we haven't checked all the stars
	while (!options->empty()) {
		// First start with the star that thinks it is the
		// closest to the source star
		Star *curr = options->remove();
		// If the star we are checking on this iteration is
		// the destination, we are done
		if (curr->getID() == dest->getID()) break;
		// For each of the neighbors of the star we are looking at
		for (int j = 0; j < curr->edges.size(); j++) {
			// Calculate what the security and MST multipliers are
			// based on whether an MST edge exists or not, and whether
			// it is enabled, and how dangerous the star is
			double security, costMult;
			if (curr->edges[j]->sec_stat < 0.5) 
				security = costs.lowSecCostMult;
			else security = costs.highSecCostMult;

			if (costs.MSTEnabled && 
					MSTExists(curr->edges[j], curr->mst_edges))
				costMult = costs.costPerMSTEdge;
			else
				costMult = costs.costPerNormalEdge;
				
			// Checks the alternate distance by going through
			// the current star and from there to the neighbor star
			// to see if it is less than the neighbor's star's currrent
			// distance to the source star. If so, we change that
			// distance and save that star's previous star as the
			// current one
			double altDist = curr->distance + 
				curr->cartesianDistanceTo(curr->edges[j])*costMult*security;
			if (altDist < curr->edges[j]->distance) {
				options->changeDist(curr->edges[j], altDist);
				curr->edges[j]->previous = curr;
			}
		}
	}
}


/**
 * @brief Calculates the shortest path to the destination star using
 * the Bellman Ford Algorithm.
 *
 * This calculates the shortest path to the destination star based on
 * the metrics provided in the CostSpec.
 *
 * @attention This is a student-written function.
 * Student may implement any shortest-path algorithm.
 * Remember: if implementing A*, don't overestimate the distance to goal.
 *
 * @param[in] src the origin point from which to find a path.
 * @param[in] dest the destination to find a path to.
 * @param[in] costs a cost specification for this calculation.
 *
 * @return a list of stars from the origin to the destination inclusive,
 * along the shortest path available.
 */
 
 
 /**
  * Outline
  * 1) Initialize a map of distances to source and previous star, with
  * key values as the star ID numbers
  * 2) Compile the list of all edges of the graph
  * 
  * REPEAT V-1 Times
  * 	FOR EACH edge of the graph
  * 		IF distance going through first star of edge is shorter
  * 			than current distance from source of second star
  * 				distance[star2] = distance(u, v) + distance[star1]
  *					previous[star2] = star1
  *	Backtrack:
  * Start with destination star
  * Save a pointer to that star
  * WHILE star pointing to is not source star
  * 	Add star pointing to to list of shortest path
  * 	Change star pointing to its previous star
  * END WHILE
  * 
  * THIS GIVES US THE SHORTEST PATH USING Bellman-Ford's ALGORITHM 
  */
std::list<Star*> Starmap::BellmanFord(Star * src, Star * dest, CostSpec costs) {
	//Store distance to source and previous star in shortest path
	// keyed by ID number of star	
	std::map<int, double> distances;
	std::map<int, Star *> previous;
	
	std::vector<Pair> edge;
	
	// Iterate through all the stars
	std::map<int, Star *>::iterator i;
	for (i = stars.begin(); i != stars.end(); i++) {	
		Star *curr = i->second;
		
		// Store its edges. If this edge is part of the MST note that
		for (int j = 0; j < curr->edges.size(); j++) {
			if (MSTExists(curr->edges[j], curr->mst_edges))
				edge.push_back(Pair(curr, curr->edges[j], true));
			else
				edge.push_back(Pair(curr, curr->edges[j], false));
		}
		// Set all distances source initially to infinity, except for
		// source (which has distance 0)
		if (curr != src)
			distances[curr->getID()] = std::numeric_limits<double>::infinity();
		else 
			distances[curr->getID()] = 0;
		previous[curr->getID()] = NULL;
	}
	// Go through all edges (number of stars - 1) times
	for (int j = 0; j < stars.size() - 1; j++) {
		for (int k = 0; k < edge.size(); k++) {
			// Calculate weight of this edge, taking into account
			// different multipliers
			double edgeDist;
			double multMst;
			double multSec;
			if (edge[k].MST) multMst =  costs.costPerMSTEdge;
			else multMst = costs.costPerNormalEdge;
			if (edge[k].second->sec_stat < 0.5) 
				multSec = costs.lowSecCostMult;
			else multSec = costs.highSecCostMult;
			
			edgeDist = edge[k].first->cartesianDistanceTo(edge[k].second)
			* multMst * multSec;
			// If the distance to 2nd star would be less going through
			// 1st star of edge, change that to shortest distance
			if (edgeDist + distances[edge[k].first->getID()] < 
				distances[edge[k].second->getID()]) {
					distances[edge[k].second->getID()] = 
						distances[edge[k].first->getID()]+ edgeDist;
					previous[edge[k].second->getID()] = edge[k].first;
			}
		}
	}
	std::list<Star*> ret;

	ret.push_front(dest);
	// Backtrack through the stars to see which one was chosen
	// before in the shortest path
	Star *bt = dest;
	while(previous[bt->getID()] != NULL) {
		bt = previous[bt->getID()];
		ret.push_front(bt);
	}
    return ret;

}
		

/**			
 * @brief Finds the star of all the options which currently thinks
 * it has the minimum distance to the source star.
 *
 * @param src the origin point from which to find a path.
 * @param options the list of stars you want to pick from.
 *
 * @return the index of the star with closest distance to the source.
 */
int Starmap::minDist(Star *src, std::vector<Star*>options) {
	// Originally set the index to -1 and shortest distance to 
	// infinity so that something will be smaller
	int index = -1;
	double shortD = std::numeric_limits<double>::infinity();
	for (int i = 0; i < options.size(); i++) {
		if (options[i]->distance < shortD) {
			shortD = options[i]->distance;
			index = i;
		}
	}
	return index;	
}

/**
 * @brief Check if the star we are looking for is in a vector.
 *
 * @param[in] check the star to look for.
 * @param[in] listToCheck the vector of stars to check in.
 *
 * @return a boolean saying whether the star is in the list.
 */
bool Starmap::MSTExists(Star *check, std::vector<Star*>listToCheck) {
	for(int i = 0; i < listToCheck.size(); i++) {
		if (listToCheck[i] == check) return true;
	}
	return false;	
}



/**
 * @brief Calculates the minimum spanning tree of this starmap.
 *
 * This calculates the minimum spanning tree using the Cartesian metric,
 * optionally constrained to existing edges.
 *
 * @attention This is a student-written function.
 * Student may implement any shortest-path algorithm.
 * Prim's algorithm only works on fully connected subgraphs,
 * so you'll need a starting star within New Eden (and outside
 * Jove and CCP space) if you're not ignoring edges.
 */
 
 /**
  * Outline: (Prim's Algorithm)
  * 
  * Clear any old MST by deleting the MST edges of each star
  * 
  * 1) Add start vertex to list of vertices on tree
  * 2) Store list of vertices not on tree
  * WHILE not all vertices have been added
  * 	FOR EACH star of the MST
  * 		FOR EACH neighbor of that star
  * 			Check if that edge has shorter distance than the
  * 			current shortest
  * 		END FOR
  *		END FOR
  * 	Add the vetex with shortest distance to the tree
  * 	Remove this vertex from the list of stars not on the tree
  * END WHILE
  */
void Starmap::generateMST(bool ignore_edges)
{
    INFO("Computing MST...");  

	// Iterate through all the stars of the map and clear any 
	// mst edges they have stored from previous runs
    std::map<int, Star *>::iterator i;
	for (i = stars.begin(); i != stars.end(); i++) {
		Star *curr = i->second;
		if (!curr->mst_edges.empty()) {
			curr->mst_edges.erase(curr->mst_edges.begin(), curr->mst_edges.end());
		}	
	}
	onMST.erase(onMST.begin(), onMST.end());
	notOnMST.erase(notOnMST.begin(), notOnMST.end());

	// Initialize the cost at first to be zero
	double cost = 0;
		
	// Start with Jita, which is a more central star
	onMST.push_back(stars[30000142]);

	// At first, each of the other stars are not on the MST
	for (i = stars.begin(); i != stars.end(); i++) {
		if (i->first != 30000142) {
			Star *curr = i->second;
			notOnMST.push_back(curr);
		}
	}
	
	Star *notOnTree;
	Star *OnTree;
	// While we still have stars that are not on the MST
	while (!notOnMST.empty()) {
		// We will find the shortest distance of any star not on the
		// MST to a star on the MST
		double shortestDist = std::numeric_limits<double>::infinity();
		notOnTree = NULL;
		OnTree = NULL;
		int added = -1;
		for(int i = 0; i < onMST.size(); i++) {
			// If we are ignoring existing edges, we must check
			// all the edges that are not on the MST for each of 
			// the stars currently on the MST
			if (ignore_edges) {
				for (int j = 0; j < notOnMST.size(); j++) {
					double dist = onMST[i]->cartesianDistanceTo(notOnMST[j]);
					if (dist < shortestDist) {
						shortestDist = dist;
						notOnTree = notOnMST[j];
						OnTree = onMST[i];
						added = j;
					}
				}
			}
			// If we are not ignoring existing edges, then we
			// must check all the edges that each of the star connects
			// to
			else {
				for (int j = 0; j < onMST[i]->edges.size(); j++) {
					double dist = onMST[i]->cartesianDistanceTo(onMST[i]->edges[j]);
					bool alreadyIn = true;
					if (dist < shortestDist) {
						// We should also check if the star that
						// we have an edge to and seems to be the shortest
						// is already on the tree
						for (int k = 0; k < notOnMST.size(); k++) {
							if (onMST[i]->edges[j]->getID() == notOnMST[k]->getID()) {
								alreadyIn = false;
								added = k;
							}
						}
						if (alreadyIn) continue;
						shortestDist = dist;
						notOnTree = onMST[i]->edges[j];
						OnTree = onMST[i];
					}
				}
			}
			
		}
		
		// Takes care of the case where not all stars have been
		// added but the stars left are not in the same connected
		// component as Jita. If so, starts a new connected component
		// by adding a star to the MST which does not have any
		// mst_edges connections at first
		if (notOnTree == NULL) {
			onMST.push_back(notOnMST[0]);
			continue;
		}
		
		// We push the star we have found with shortest distance
		// on the tree
		OnTree->mst_edges.push_back(notOnTree);
		/** Fixed error of not adding a to b.mst_edges AND b to a.mst_edges */
		notOnTree->mst_edges.push_back(OnTree);
		cost += OnTree->cartesianDistanceTo(notOnTree);
		onMST.push_back(notOnTree);
		// And remove it from the list of stars not on the MST
		notOnMST.erase(notOnMST.begin() + added);
	}
	INFO("Cost %f", cost);
    INFO("Done computing MST");

}


/**
 * @brief Marks a path on the starmap.
 *
 */
void Starmap::markPath(std::list<Star*> path)
{
    std::map<int, Star *>::iterator f;
    for(f = this->stars.begin(); f != this->stars.end(); f++)
    {
        f->second->path_next = NULL;
    }

    std::list<Star*>::iterator i, j;
    for(i = path.begin(); i != path.end(); i++)
    {
        j = i;
        j++;
        if(j != path.end())
        {
            Star * u = *i;
            Star * v = *j;
            u->path_next = v;
        }
    }
}

/**
 * @brief Loads starmap data from the local database.
 *
 * This queries the local copy of the star database and loads all the
 * relevant information into this starmap object.
 */
void Starmap::loadStarmapFromDB()
{
    // First let's prepare all the relevant SQL stuff
    sqlite3 * db;
    int rc;
    int s_count = 0, e_count = 0;

    rc = sqlite3_open("map.db", &db);
    REQUIRE(rc == 0, "Can't open map database: %s", sqlite3_errmsg(db));

    INFO("Loading stars...");

    // We first load in all the stars
    sqlite3_stmt * ppstmt;
    const char * unused;
    // prepare the relevant SQL statement
    sqlite3_prepare_v2(db,
#if DATASET_FULL
    "SELECT solarSystemID, solarSystemName, x, y, z, security FROM solarSystems WHERE 1",
#else
    "SELECT solarSystemID, solarSystemName, x, y, z, security FROM solarSystems WHERE "
    "regionID = \"10000002\" OR regionID = \"10000016\" OR regionID = \"10000023\" OR regionID = \"10000033\"",
#endif
    -1,
    &ppstmt,
    &unused);

    // now step through it all the times
    while((rc = sqlite3_step(ppstmt)) == SQLITE_ROW)
    {
        int __id = sqlite3_column_int(ppstmt, 0);
        const unsigned char * __name = sqlite3_column_text(ppstmt, 1);
        double __x = sqlite3_column_double(ppstmt, 2) / 1e16;
        double __y = sqlite3_column_double(ppstmt, 3) / 1e16;
        double __z = sqlite3_column_double(ppstmt, 4) / 1e16;
        double __sec = sqlite3_column_double(ppstmt, 5);

        std::string __name_str((const char *)__name);

        Star * s = new Star(__id, __name_str, __x, __y, __z, __sec);
        this->addStar(s);
        //DEBUG("Added star %s (%d)", __name, __id);
        s_count++;
    }

    REQUIRE(rc == SQLITE_DONE, "Error reading stars: %s", sqlite3_errmsg(db));
    sqlite3_finalize(ppstmt);
    // Now all the stars are loaded yay

    // Now load all of the edges

    INFO("Loading edges...");

    sqlite3_prepare_v2(db,
#if DATASET_FULL
    "SELECT fromSolarSystemID, toSolarSystemID FROM solarSystemJumpn WHERE 1",
#else
    "SELECT fromSolarSystemID, toSolarSystemID FROM solarSystemJumpn WHERE "
    "(fromRegionID = \"10000002\" OR fromRegionID = \"10000016\" OR fromRegionID = \"10000023\" OR fromRegionID = \"10000033\")"
    "AND (toRegionID = \"10000002\" OR toRegionID = \"10000016\" OR toRegionID = \"10000023\" OR toRegionID = \"10000033\")",
#endif
    -1,
    &ppstmt,
    &unused);

    while((rc = sqlite3_step(ppstmt)) == SQLITE_ROW)
    {
        int from_id = sqlite3_column_int(ppstmt, 0);
        int to_id = sqlite3_column_int(ppstmt, 1);

        Star * p = this->stars[from_id];
        Star * q = this->stars[to_id];

        p->addEdgeTo(q);
        //DEBUG("Added link from star %s (%d) to star %s (%d)",
              //p->getName().c_str(), from_id, q->getName().c_str(), to_id);
        e_count++;
    }

    REQUIRE(rc == SQLITE_DONE, "Error reading edges: %s", sqlite3_errmsg(db));
    sqlite3_finalize(ppstmt);


    // We are now loaded yay

    sqlite3_close(db);
    INFO("%d stars, %d edges", s_count, e_count);
    INFO("Starmap loaded with %d stars", this->stars.size());

    this->selected_star = this->stars[30000144];

}

#ifndef NO_GFX
/**
 * @brief Renders all the stars in this starmap.
 */

void Starmap::render(double dist, double azm, double alt, bool pick)
{
    std::map<int, Star*>::iterator i;

    // before we draw anything we orient our viewpoint in space
    // we do transforms in OpenGL backwards because matrix math

    // and last we zoom out
    glTranslated(0, 0, dist);
    // then we rotate the whole thing
    glRotated(alt, 1, 0, 0);
    glRotated(azm, 0, 1, 0);
    // then we scale the whole thing to avoid funny render glitches
    glScaled(1e-2, 1e-2, 1e-2);
    // so first we center ourselves on our focus star
    GLdouble * focus_coords;
    if(this->focus_star != NULL)
    {
        focus_coords = this->focus_star->getCoords();
        glTranslated(-focus_coords[0], -focus_coords[1], -focus_coords[2]);
    }

    // now we're correctly oriented in space so we can draw stuff yay

    // first render all the edges
    if(!pick)
    {
        glBegin(GL_LINES);

        for(i = this->stars.begin(); i != this->stars.end(); i++)
        {
            Star * s = i->second;
            s->drawEdges();

        }

        glEnd();

        // edges should be behind everything
        glClear(GL_DEPTH_BUFFER_BIT);
    }

    // then render all the stars

    for(i = this->stars.begin(); i != this->stars.end(); i++)
    {
        Star * s = i->second;
        glPushName(s->getID());
        glBegin(GL_POINTS);
        s->glColor3d();
        s->glVertex3d();
        glEnd();
        glPopName();
    }

    // then we want to render the selection diamonds
    if(!pick)
    {
        if(this->selected_star != NULL)
        {
            glColor4d(0.0, 0.5, 1.0, 0.5);
            GLdouble * coords = this->selected_star->getCoords();
            GLdouble x = coords[0];
            GLdouble y = coords[1];
            GLdouble z = coords[2];

            glPushMatrix();
            glTranslated(x, y, z);
            glScaled(1, 1, 1);
            glScaled(dist, dist, dist);
            glutSolidOctahedron();
            glPopMatrix();
        }

        if(this->selected_star_2 != NULL)
        {
            glColor4d(1.0, 0.5, 0.0, 0.5);
            GLdouble * coords = this->selected_star_2->getCoords();
            GLdouble x = coords[0];
            GLdouble y = coords[1];
            GLdouble z = coords[2];

            glPushMatrix();
            glTranslated(x, y, z);
            glScaled(1, 1, 1);
            glScaled(dist, dist, dist);
            glutSolidOctahedron();
            glPopMatrix();
        }
    }

}

/**
 * @brief Selects the star clicked on by mouse.
 *
 * We do this by putting ourselves into GL_SELECT mode,
 * then rendering everything while constraining ourselves
 * to a tiny little box around the mouse coordinates.
 * We take note of any stars that rendered within the box,
 * and select the closest of these to the viewpoint (if any).
 *
 */
void Starmap::mouseSelect(int which, int x, int y, double dist, double azm, double alt)
{
    GLint viewport[4];
	double ratio;
    GLint hits;
    GLuint selectBuf[4096];

    // define a select buffer
	glSelectBuffer(1024,selectBuf);

	glGetIntegerv(GL_VIEWPORT,viewport);

	glRenderMode(GL_SELECT);

    glInitNames();

    glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	gluPickMatrix(x,viewport[3]-y,9,9,viewport);
	ratio = (viewport[2]+0.0) / viewport[3];
	gluPerspective(45, (double)WIDTH/HEIGHT, .0001, 1000);
	glMatrixMode(GL_MODELVIEW);

    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    this->render(dist, azm, alt, true);

    glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glFlush();
	hits = glRenderMode(GL_RENDER);
	if (hits != 0){
        GLint i, j, numberOfNames;
        GLuint names, *ptr, minZ, *ptrNames;

        ptr = (GLuint *) selectBuf;
        minZ = 0xffffffff;
        for (i = 0; i < hits; i++) {
            names = *ptr;
            ptr++;
            if (*ptr < minZ) {
                numberOfNames = names;
                minZ = *ptr;
                ptrNames = ptr+2;
            }

            ptr += names+2;
        }
        if (numberOfNames > 0) {
            ptr = ptrNames;
            Star * u = this->stars[*ptr];
            INFO("Selecting star %s", u->getName().c_str());

            if(which == 0)
            {
                this->selected_star = u;
            }
            else if(which == 1)
            {
                this->selected_star_2 = u;
            }
            else if(which == 2)
            {
                this->setFocus(u);
            }

        }

	}
}
#endif
