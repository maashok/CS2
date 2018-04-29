/*
 * SeamCarveAlgorithm.cpp
 * Defines the seam carving algorithm.
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
 *
 */

#include "SeamCarveApp.hpp"

#define min(x, y)           ((x) < (y) ? (x) : (y))

void calculateCost(int **cost, unsigned int **smap, int h, int w);

/**
 * @brief Peforms the seam carving algorithm.
 *
 * @param smap 2-d saliency map with width `w` and height `h`; can be
 * indexed by `smap[i][j]`
 *
 * @param w Width of the saliency map
 *
 * @param h Height of the saliency map
 */
unsigned int *DoSeamCarve(unsigned int **smap, int w, int h)
{
    unsigned int *seam = new unsigned int[h];
	
	// Initialize a 2-D array to hold the cost of each pixel
	int **cost = new int*[h];
	for (int i = 0; i < h; i++)
		cost[i] = new int[w];
		
	// Calculate the cost map based on the saliency map
	calculateCost(cost, smap, h, w);
		
	// To find the seam, the last row just starts with the pixel with
	// the lowest cost
	int bottomLowest = 0;
	for (int col = 1; col < w; col++) {
		if (cost[h-1][col] < cost[h-1][bottomLowest])
			bottomLowest = col;
	}
	seam[h-1] = bottomLowest;
	
	// Then, you backtrack based on the previous row's lowest cost pixel, looking
	// at the three pixels in the row above it to the left, directly above
	// and to the right, and find the one with the lowest cost.
	// That is the next pixel on the seam
	int row = h - 2;
	while (row >= 0) {
		// Take care of edge cases where there are only 2 pixels above
		// to choose from
		if (seam[row+1] == 0) {
			if (cost[row][seam[row+1]] <= cost[row][seam[row+1]+1])
				seam[row] = seam[row+1];
			else
				seam[row] = seam[row+1]+1;
		}
		else if(seam[row+1] == (unsigned)w - 1) {
			if (cost[row][seam[row+1]] <= cost[row][seam[row+1]-1])
				seam[row] = seam[row+1];
			else
				seam[row] = seam[row+1]-1;
		}
		// All other cases have 3 pixels to compare with
		else {
			if (cost[row][seam[row+1]] <= cost[row][seam[row+1]-1] && 
						 cost[row][seam[row+1]] <= cost[row][seam[row+1]+1])
				seam[row] = seam[row+1];
			else if (cost[row][seam[row+1]-1] <= cost[row][seam[row+1]] &&
						cost[row][seam[row+1]-1] <= cost[row][seam[row+1]+1])
				seam[row] = seam[row+1] - 1;
			else
				seam[row] = seam[row+1] + 1;
		}
		row--;
	}
	
	// Delete memory allocated for the cost 2-D array
    for (int i = 0; i < h; i++)
		delete[] cost[i];
	delete[] cost;

    return seam;
}

/**
 * @brief Calculates the cost map.
 *
 * @param cost 2-d cost map with width `w` and height `h`
 * 
 * @param smap 2-d saliency map with width `w` and height `h`; can be
 * indexed by `smap[i][j]`
 *
 * @param h Height of the saliency map
 *
 * @param w Width of the saliency map
 */
void calculateCost(int **cost, unsigned int **smap, int h, int w) {
	// The first row of the cost map is the same as the saliency
	for (int k = 0; k < w; k++)
		cost[0][k] = smap[k][0];
		
	// For all succeeding rows, it is the sum of the saliency at that
	// pixel plus the minimum cost of the three above
	for (int i = 1; i < h; i++) {
		for (int j = 0; j < w; j++) {
			// Takes care of edge cases where there are only 2 pixels
			// above the current pixel separately
			if (j == 0) {
				cost[i][j] = smap[j][i] + min(cost[i-1][j], cost[i-1][j+1]);
			}
			else if(j == w - 1) {
				cost[i][j] = smap[j][i] + min(cost[i-1][j], cost[i-1][j-1]);
			}
			// All other pixels are treated normally, with comparisons
			// between 3 costs
			else 
				cost[i][j] = smap[j][i] + 
					min(min(cost[i-1][j-1], cost[i-1][j]), cost[i-1][j+1]);
		}
	}
}
