#include "star.hpp"

/**
 * A binary min-heap so that the stars with lowest distance to source
 * are at the top of the heap
 */
class BHeap 
{
	std::vector <Star *> bheap;
	
	public:
		BHeap(std::map<int, Star *> stars, Star *src) {
			// Distance from source to source is zero, all other 
			// distances infinity
			src->distance = 0;
			src->previous = NULL;
			
			std::map<int, Star *>::iterator i;
			for (i = stars.begin(); i != stars.end(); i++) {
				Star *curr = i->second;
				if (curr->getID() != src->getID()) {
					curr->distance = std::numeric_limits<double>::infinity();
					curr->previous = NULL;
				}
				this->insert(curr);
			}
		}
		// Insert a node into the binary heap
		void insert(Star *toInsert) {
			// Add node initially as a leaf to the end
			bheap.push_back(toInsert);
			int child = bheap.size() - 1;
			int parent = (child-1)/2;
			// While the child's distance is less than the parent's 
			// distance move it up in the heap
			while (parent >= 0 && 
			   bheap[child]->distance < bheap[parent]->distance) {
				swap(child, parent);
				child = parent;
				parent = (child-1)/2;
			}
		}
		// Remove a node from the binary heap
		Star* remove() {
			// If only one element just remove it
			if (bheap.size() == 1) {
				Star *lastOne = bheap[0];
				bheap.pop_back();
				return lastOne;
			}
			// Otherwise, switch the first and last element for easier
			// removal and remove the one now at the end (the smallest value)
			swap(bheap.size() -1, 0);
			Star *toRemove = bheap[bheap.size() - 1];
			bheap.pop_back();
			int parent = 0;
			int child = 2*parent + 1;
			// If the parent is larger than the child, move it down
			while(child < bheap.size() &&
				(bheap[parent]->distance > bheap[child]->distance
				|| bheap[parent]->distance > bheap[child+1]->distance)){
				if (bheap[child]->distance > bheap[child+1]->distance) {
					child++;
				}
				swap(parent, child);
				parent = child;
				child = 2*parent + 1;
			}
			return toRemove;
		}
		// Finding takes O(n) time
		int find(Star *toFind) {
			for (int i = 0; i < bheap.size(); i++) {
				if (toFind->getID() == bheap[i]->getID()) return i;
			}
		}
		// If you find the shortest distance to source for some star,
		// change it and move it up in the heap if necessary
		void changeDist(Star *toChange, double distToSource) {
			toChange->distance = distToSource;
			
			int child = find(toChange);
			int parent = (child-1)/2;
			while (bheap[child]->distance < bheap[parent]->distance) {
				swap(child, parent);
				child = parent;
				parent = (child-1)/2;
			}
		}
		// Swap two elements of the binary heap
		void swap(int swap1, int swap2) {
			Star *temp = bheap[swap1];
			bheap[swap1] = bheap[swap2];
			bheap[swap2] = temp;
		}
		
		bool empty() {
			return bheap.size() <= 0;
		}
};
