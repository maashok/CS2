/**
* @file testsuite.cpp
* @author Ellen Price <<eprice@its.caltech.edu>>
* @version 1.0
* @date 2014-2015
* @copyright see License section
*
* @brief Runs a series of tests on the shortest path algorithms, etc.
*
* @section License
* Copyright (c) 2014-2015 California Institute of Technology.
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

#define ITAMO       (30000119)
#define JAKANERVA   (30000148)
#define JITA        (30000142)
#define HEK         (30002053)


class StarTester {
public:
    Star *star;

    StarTester(Star *star) {
        this->star = star;
    }

    std::vector<Star *> * get_mst_edges() {
        return &star->mst_edges;
    }
};

class StarmapTester {
public:
    Starmap *map;

    StarmapTester(Starmap *map) {
        this->map = map;
    }

    double mst_total_weight() {
        double total = 0;
        std::map<int, Star*>::iterator star_it;
        for (star_it = map->stars.begin(); star_it != map->stars.end();
                star_it++) {
            Star *star = star_it->second;
            std::vector<Star *> * mst_edges =
                StarTester(star).get_mst_edges();
            std::vector<Star*>::iterator adjacent_star_it;
            for (adjacent_star_it = mst_edges->begin();
                 adjacent_star_it != mst_edges->end();
                 adjacent_star_it++) {
                total += star->cartesianDistanceTo(*adjacent_star_it);
            }
        }
        return total / 2;
    }

    double num_mst_edges() {
        double total = 0;
        std::map<int, Star*>::iterator star_it;
        for (star_it = map->stars.begin(); star_it != map->stars.end();
                star_it++) {
            Star *star = star_it->second;
            std::vector<Star *> * mst_edges =
                StarTester(star).get_mst_edges();
            total += mst_edges->size();
        }
        return total / 2;
    }
};


void print_path(std::list<Star*> path)
{
    std::list<Star*>::iterator pi;
    int pidx = 0;
    for(pi = path.begin(); pi != path.end(); pi++)
    {
        INFO("Hop %d: %s", pidx++, (*pi)->getName().c_str());
    }
}


int main(int argc, char *argv[])
{
    CostSpec s;
    std::list<Star*> path;

    Starmap *map = new Starmap();
    map->loadStarmapFromDB();

    // Print MST total weight with ignore_edges=true
    map->generateMST(true);
    INFO("");
    INFO("MST weight is %G", StarmapTester(map).mst_total_weight());
    INFO("MST number of edges is %G", StarmapTester(map).num_mst_edges());
    INFO("");

    // Print MST total weight with ignore_edges=false
    map->generateMST(false);
    INFO("");
    INFO("MST weight is %G", StarmapTester(map).mst_total_weight());
    INFO("MST number of edges is %G", StarmapTester(map).num_mst_edges());
    INFO("");

    // Print shortest path Itamo -> Jakanerva, avoid lowsec, no MST
    Star *u = map->getStar(ITAMO);
    Star *v = map->getStar(JAKANERVA);
    s.lowSecCostMult = 20.;
    s.highSecCostMult = 1.;
    s.MSTEnabled = false;
    path = map->shortestPath(u, v, s);
    INFO("Itamo -> Jakanerva, avoid lowsec, no MST");
    print_path(path);
    INFO("");

    // Print shortest path Itamo -> Jakanerva, avoid highsec, no MST
    INFO("Itamo -> Jakanerva, avoid highsec, no MST");
    s.lowSecCostMult = 1.;
    s.highSecCostMult = 20.;
    s.MSTEnabled = false;
    path = map->shortestPath(u, v, s);
    print_path(path);
    INFO("");

    // Print shortest path Itamo -> Jakanerva, restricted MST"
    INFO("Itamo -> Jakanerva, restricted MST");
    s.lowSecCostMult = 1.;
    s.highSecCostMult = 1.;
    s.MSTEnabled = true;
    path = map->shortestPath(u, v, s);
    print_path(path);
    INFO("");

    return 0;
}
