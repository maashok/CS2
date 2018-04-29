/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief The bubble sort, quick sort, merge sort, and in-place quicksort
 * algorithms (implementation).
 *
 */
#include "sorter.h"

int main(int argc, char* argv[])
{
    // Set up buffers and data input
    std::vector<int> nums;
    std::string line;
    char *filename;
    int sort_type;

    // Ensure that at most one type of sort and at least a filename are specified.
    if (argc > 3 || argc < 2)
    {
        usage();
    }

    // default sort is bubble sort
    sort_type = BUBBLE_SORT;

    // Figure out which sort to use
    for (int i = 1; i < argc; ++i)
    {
        char *arg = argv[i];
        if (strcmp(arg, "-b") == 0) { sort_type = BUBBLE_SORT; }
        else if (strcmp(arg, "-q") == 0) { sort_type = QUICK_SORT; }
        else if (strcmp(arg, "-m") == 0) { sort_type = MERGE_SORT; }
        else if (strcmp(arg, "-qi") == 0) { sort_type = QUICK_SORT_INPLACE; }
        else { filename = argv[i]; }
    }

    // Read the file and fill our vector of integers
    // THIS FUNCTION IS STUDENT IMPLEMENTED
    readFile(filename, nums);

    switch (sort_type)
    {
        case BUBBLE_SORT:
        print_vector(bubbleSort(nums));
        break;

        case QUICK_SORT:
        print_vector(quickSort(nums));
        break;

        case MERGE_SORT:
        print_vector(mergeSort(nums));
        break;

        case QUICK_SORT_INPLACE:
        quicksort_inplace(nums, 0, nums.size() - 1);
        print_vector(nums);
        break;

        default:
        usage();
        break;
    }
    return 0;
}

/**
 * Usage    Prints out a usage statement and exits.
 */
void usage()
{
    fprintf(stderr, "%s", usage_string);
    exit(1);
}

/**
 * TO STUDENTS: In all of the following functions, feel free to change the
 * function arguments and/or write helper functions as you see fit. Remember to
 * add the function header to sorter.h if you write a helper function!
 */

/**
 * Bubble Sort
 * Allows the larger elements to bubble to the end one by one until
 * there are no more elements left to sort,that aren't already in order.
 *
 * WHILE SOME ELEMENTS NOT IN ORDER
 *   WHILE ELEMENTS LEFT IN LIST TO CHECK
 * 	    IF ELEM AT INDEX i > ELEM AT INDEX i+1
 * 		    SWAP
 * 			REMEMBER LAST ELEMENT SWAPPED
 * 		ELSE 
 * 			CONTINUE TO NEXT PAIR
 *		ENDIF
 * 	 ELEMENTS NOT IN ORDER = LAST ELEMENT SWAPPED
 */

std::vector<int> bubbleSort(std::vector<int> &list)
{
	// The elements from 0 to notInOrder - 1 must still be sorted
	int notInOrder = list.size()-1;
	while (notInOrder > 0) {
		// Initialize a variable to save what element is last swapped
		int last = 0;
		// Go through the list and swap adjacent elements if necessary
		for (int i = 0; i < notInOrder; i++) {
			if (list[i] > list[i+1]) {
				swap(list, i, i+1);
				// Save what element was swapped last
				last = i;
			}
		}
		// The number of elements left to sort becomes the last one
		// swapped
		notInOrder = last;
	}
    return list;
}

/**
 * Swaps two elements of the list, given the indices to swap at.
 */

void swap(std::vector<int> &list, int i, int j) {
	int temp = list[i];
	list[i] = list[j];
	list[j] = temp;
}

/**
 * Quick Sort
 * Split the list into values lower than the pivot, the pivot
 * itself, and values greater than the pivot. Then sort the list lower
 * and greater than the pivot using the quicksort method again, until
 * you have two lists of length 1.
 * 
 * IF size of list = 1
 * 		return list
 * ENDIF
 * pivot = list[midpoint(0, size)]
 * IF element <= pivot
 * 		place in lessThan list
 * ELSE if element > pivot
 * 		place in GreaterThan list
 * ENDIF
 * lessThan = quicksort(lessThan)
 * greaterThan = quicksort(greaterThan)
 * concatenate (lessThan, pivot, greaterThan)
 * return list
 * 
 */
std::vector<int> quickSort(std::vector<int> &list)
{
	// If the list is empty or has only one element, it is sorted
	if (list.size() == 1 || list.size() == 0) return list;
	int pivot = list[list.size() / 2];
	// Split elements into those less than and greater than pivot
	std::vector<int> lessThan, greaterThan;
	for (unsigned int i = 0; i < list.size(); i++) {
		if (i == (list.size() / 2)) continue;
		if (list[i] <= pivot)
			lessThan.push_back(list[i]);
		else if (list[i] > pivot)
			greaterThan.push_back(list[i]);
	}
	// Recursively quicksort the less than and greater than lists
	lessThan = quickSort(lessThan);
	greaterThan = quickSort(greaterThan);
	// Concatenate these sorted lists along with the pivot
    list = concat(lessThan, pivot, greaterThan);
    return list;
}

/**
 * Concatenates the list of items less than pivot, the pivot, and the
 * list of items greater than pivot
 */
std::vector<int> concat(std::vector<int> &less, int pivot, std::vector<int> &greater) {
	// Will just add all the values to the end of the less than vector
	// so we don't have to create another vector
	
	// Adds the pivot value to the end of the vector
	less.push_back(pivot);
	// Add each of the greater than values to the end of the vector
	for (unsigned int i = 0; i < greater.size(); i++) {
		less.push_back(greater[i]);
	}
	return less;
}

/**
 * Merge Sort
 * Recursively split the list into smaller sets, and sort the smaller
 * lists and then merge these smaller sorted lists.
 *  
 * IF size of list = 1
 * 		return list
 * ENDIF
 * mid = midpoint(low, high)
 * 1stHalf = mergeSort(1stHalf of list)
 * 2ndHalf = mergeSort(2ndHalf of list)
 * merge (1stHalf, 2ndHalf)
 * 
 */
std::vector<int> mergeSort(std::vector<int> &list)
{
	// If the list is of size 0 or 1, just return the list
	if (list.size() <= 1) return list;
	// Store the middle index to partition at
	unsigned int mid = (list.size()) / 2;
	unsigned int i;
	
	// Partition the list into two halves
	std::vector<int> list1;
	for (i = 0; i < mid; i++)
		list1.push_back(list[i]);
	std::vector<int> list2;
	for (i = mid; i < list.size(); i++)
		list2.push_back(list[i]);
	
	// Merge sort each half of the list
	list1 = mergeSort(list1);
	list2 = mergeSort(list2);
	// Merge together the halves
	list = merge(list1, list2);
	return list;
}

/**
 * Merge two sorted lists together, in sorted order
 */
 
std::vector<int> merge(std::vector<int> &left, std::vector<int> &right)
{
	// Indices to store the position in each vector
	unsigned int i = 0, j = 0;
	std::vector<int> merged;
	// While both vectors have not been fully looked at
	while (i < left.size() || j < right.size()) {
		// If the right vector has been fully looked at, we must
		// add elements from the left vector
		if (j == right.size()) {
			merged.push_back(left[i]);
			i++;
		}
		// If the left vector has been fully looked at, we must add
		// elements from the right vector
		else if (i == left.size()) {
			merged.push_back(right[j]);
			j++;
		}
		// Otherwise, if the element in the left vector is smaller, 
		// we add that one and increment the index in the left vector
		else if (left[i] <= right[j]) {
			merged.push_back(left[i]);
			i++;
		}
		// Finally, if the element in the right vector is smaller,
		// we add that one and increment the index in the right vector
		else if (right[j] <= left[i]){
			merged.push_back(right[j]);
			j++;
		}
	}

    return merged;
}

/*
 * quicksort_inplace:  In-place version of the quicksort algorithm. Requires
 *              O(1) instead of O(N) space, same time complexity. Each call of
 *              the method partitions the list around the pivot (an item taken
 *              from the middle of the array) with items left of the pivot
 *              smaller than it and items to its right larger than it. Then the
 *              method recursively sorts the left and right portions of the list
 *              until it reaches its base case: a list of length 1 is already
 *              sorted.
 *
 * @param list: pointer to integer array to be sorted
 * @returns:    Nothing, the array is sorted IN-PLACE.
 *
 * 
 */
 /**
 * We want to split the numbers of the list to the left and the right
 * of the pivot, so that numbers lower than the pivot value move
 * to the left of it, and numbers greater than the pivot to the right of
 * it. Then, we call quicksort on both parts of the list.
 * We define [left, right] as the range of values to sort in the list
 * 
 * pivot = list[midpoint(left, right)]
 * index1 = left
 * index2 = right
 * WHILE index1 <= index2
 * 		MOVE index1 until list[index1] is greater than pivot
 * 		MOVE index2 until list[index2] is less than pivot
 *		IF not crossed pivot yet
 *  		SWAP the elements at index1 and index2
 * 		ENDIF
 * IF more than one element in list
 * 		return quicksort(list, left, index2)
 * 		return quicksort(list, index1, right)
 * ENDIF
 */
void quicksort_inplace(std::vector<int> &list, int left, int right)
{
	// If the vector has only one element (or zero)
	if (left >= right) return;
	// Set the pivot to the value at the middle of the vector
	int pivot = list[(left + right)/2];
	int i = left, j = right;
	// Go through the vector and place elements less than the pivot
	// value to the left of it, and elements greater than the pivot
	// value to the right of it
	while (i <= j) {
		// Find an element to the left of the pivot that is greater
		// than the pivot
		while (pivot > list[i]) i++;
		// Find an element to the right of the pivot that is less
		// than the pivot
		while (pivot < list[j]) j--;
		// If the first element has lower index than the right element
		// (We haven't changed indices so much we would be changing
		// to put a larger element before or smaller element after)
		if (i <= j) {
			// Swap these two elements and change your indices
			swap(list, i, j);
			i++;
			j--;
		}
	}
	// Quicksort the vector from the start up to where index j ended
	// The partition might be unequal - depending on what your
	// pivot value was
	if (left < j) quicksort_inplace(list, left, j);
	// Quicksort the vector from where index i started to the end
	if (i < right) quicksort_inplace(list, i, right);
    return;
}

