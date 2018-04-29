/**
 * @file
 * @author The CS2 TA Team <<cs2-tas@ugcs.caltech.edu>>
 * @version 1.0
 * @date 2013-2014
 * @copyright This code is in the public domain.
 *
 * @brief Example of a linked list class and usage.
 *
 */

/** This program is leaking memory since 10 allcoations are made, but
 * only one of these items allocated is freed. This is seen in the
 * main method, where list.insert() is called 10 times. In each of these
 * function calls, memory is allocated for a new node in the linked
 * list. However, when we return from the main method, and the class
 * destructor is called, only the head of the linked list is freed,
 * while the memory allocated for all the other nodes remains in
 * the heap. This could be a problem for a much longer linked list, 
 * where after moving on to another function, we run out of memory
 * in the heap due to not freeing memory that is not needed anymore.
 * This can lead the program to crash, losing all the work done.
 */ 

#include <iostream>

/**
 * A class defining the shell of a linked list data structure.
 */
class List
{

/**
 * Public methods accessible by external code.
 */
public:
    List();
    ~List();
    void insert(int item);
    void printList();

/**
 * Private data, including structure definition and class variables.
 */
private:
    struct Node
    {
        int data;
        Node *next;

        /**
         * Constructor for a node structure.
         */
        Node(int data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
    };
    Node *head;
    int num_elements;
};

/**
 * List constructor.
 */
List::List()
{
    head = NULL;
    num_elements = 0;
}

/**
 * List destructor.
 */
List::~List()
{
	// Use a node pointer nxt to go through the linked list
	Node *nxt = head;
	// Use a node pointer toDel to delete the memory location
	Node *toDel;
	// Stops at one past the last node in the linked list (which is NULL)
    while (nxt != NULL) {
		// Save the current node into toDel so we can delete it
		toDel = nxt;
		// Move nxt to point to the next node in the list
		nxt = nxt->next;
		// Delete the memory location of toDel, or current node
		delete toDel;
	}
}

/**
 * insert   Insert an integer at the end of the list.
 * @param   item integer to be inserted at the end of the list
 */
void List::insert(int item)
{
    // If we have elements...
    if (num_elements > 0)
    {
        // Set up a pointer to get to end of current list
        Node *temp = head;
        for (int i = 0; i < num_elements - 1; ++i)
        {
            temp = temp->next;
        }
        // temp now points to node at end of list

        // Construct our new node, it doesn't point to anything yet
        Node *new_node = new Node(item, NULL);

        // Make the old tail point to the new tail
        temp->next = new_node;

        // and update the number of elements in the list
        num_elements++;
    }
    else
    {
        head = new Node(item, NULL);
        num_elements++;
    }
    return;
}

/**
 * printList    Prints the contents of our list out, one integer per line.
 */
void List::printList()
{
    Node *temp = head;
    while (temp != NULL)
    {
        std::cout << temp->data << std::endl;
        temp = temp->next;
    }
    return;
}

int main(int argc, char const *argv[])
{
    List lst;
    for (int i = 0; i < 10; ++i)
    {
        lst.insert(i);
    }
    lst.printList();
    return 0;
}
