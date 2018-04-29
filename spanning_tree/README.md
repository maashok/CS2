Caltech CS2 Assignment 5: Graphs

See [assignment5.html](http://htmlpreview.github.io/?https://github.com/caltechcs2/spanning_tree/blob/master/assignment5.html)

Part 0: 
There is a problem when the DFS runs on a graph rather than a tree (so
when the data structure it runs on has cycles). This is seen in the
basic case when we have 3 nodes A, B, C in a triangular arrangement.
A stores pointers to B and C in its edges. B stores pointers to A and
C in its edges, and so on. If we have A as the root node, and want
to find the value that is stored in node C through DFS, we will end 
up doing the following. The code checks whether the value in A is the
one we are looking for, which it is not. Then, it calls dfs on the first
of its neighbor nodes, which we can take to be node B. Node B, which
does not contain the value we are looking for, will call dfs on the
first of its neighbor nodes, node A. This creates an infinite loop in
our dfs algorithm.
To fix this, we would add a visited variable to the Node class, so
after checking if the value in that node is the one we are looking for
we can mark it as visited. Then, before recursively calling dfs on a
node, we check if it is already visited. If it is visited, we continue
to just check the next edge. In the previous example, that would mean
that A would have been marked as visited, so B would not call the dfs
on node A again, and would call dfs on node C instead, so that we can
find the node the value is in.


Part 1:
Short Answer
1) The three most essential properties of a MST are that it is
of minimum size, spanning, and is a tree. In terms of a graphs, 
it is a tree, meaning that it is an undirected graph, so that
edges do not have a particular direction and there are no cycles. 
The edge from v1 to v2 is the same as the edge from v2 to v1. Also,
the MST is spanning, so the tree includes all the nodes of the graph.
Finally, the minimum means the tree will have minimum total weight. 
In a weighted graph where different edges have different weights,
this MST will include all the nodes in a way that we use a tree of 
minimum total weight.

2) We should pick whichever adjacent node that will form the minimum
weighted edge with the first node. This way, we can ensure that our
first edge is of minimum weight. Since every vertex will be connected
but not necessarily all the edges, we may as well pick the edge that
will contribute the least weight so the whole MST will have minimum
total weight.

3) At each subsequent step, we should pick the edge with one node
in the tree and 1 node outside that will contribute the least weight, 
so that the whole tree has minimum weight. The node that this edge 
connects to the tree will be added to the tree.
We will know that we are finished when there are no nodes that
are not marked as connected already that we have left to compare to
find the next edge with the least weight. This works since it signifies
that every node has already been connected, and there is no way
to do it with even less weight, as we chose the edges that would add
minimum weight to our tree at every step along the way.

4) We should pick the minimum weight edge that connects two different
trees. This will work since we need to connect all the trees, and you
want all the edges to have minimum weight, so each connection you make
between trees should have minimum weight. 
Finally, we stop this when each of the candidate trees is connected 
(so that it is in fact just one tree), which means all the nodes are
connected as well.

Prim's Algorithm OUTLINE BEFORE CODE IN starmap.cpp (Starts line 391)
	
Cost for edge-only MST:
308.170896

Cost for full MST:
289.987905
	
	

Part 2:
1) If we're trying to minimize path length, it makes sense to 
investigate the neighbor that has shortest distance to the source node.

2) It makes sense to look at the node that has the shortest distance
to the source node, since that will help us reach the minimum path
length. 
At each step, we should update all the nodes that the node that we
just looked at is connected to, to see if the distance to those
nodes is shortened by going through the current node. This yields the
shortest path to another node since we can see if the original distance
from the source is more than the distance it takes to get through the 
node by going through the current node. If so, that yields a new 
shortest path.

3) We know that we're done if the CURRENT node that we are looking
at is the goal node. This is definitely the shortest path
since we greedily chose the shortest path at each step along the way
until we got to the destination star, so the final path is also the 
shortest possible. To derive the path, we go back through the previous
pointers to each node that is connected in the path before it, and
put those nodes in order to get the shortest path.


Djikstra's Algorithm OUTLINE BEFORE CODE IN starmap.cpp (line 42)

The implementation is using binary heap, and can also run using
vector implementation of the list of stars to be added instead by
uncommenting the line 
//vectorShortestPath(src, dest, costs); 
in the shortestPath function and commenting out the line
bHeapShortestPath(src, dest, costs); instead.

To run Dijkstra's shortest path, run with the preprocessor toggle [-d].
To run Bellman-Ford's shortest path algorithm, run with preprocessor
toggle [-b].


Part X:
A trade hub like Jita may arise due to that star having some special
resource that people in other stars desire, making Jita a valuable
trade post to stop by. Jita is also near the middle of New Eden, meaning
that starships that need to cross New Eden might find it convenient
to stop at Jita to refuel. However, there are just as many other
central stars. What might make Jita special is that it has been
civilized longer, meaning much of the trade post will be more established
and easier to get through. Also, it might just have more people, in
which case more starships will come through Jita to supply all the
needed resources for all the people. This may be a reason Jita continues
to be economically important.



Feedback:
I am at basic-intermediate level. I took AP Computer Science before 
CS 1. I am mostly following everything of the course.

I think the hardest part about adopting C++ as a working language
is the extra debugging that comes with it (seg faults and memory leaks).
Perhaps a larger section of the first assignment could be devoted to 
using to learn valgrind and gdb.

I spent 15 - 20 hours on this assignment. Not much of that time was
spent figuring out C++ specific stuff. About 2-3 hours might have been
spent understanding the algorithms themselves, but most of the time
was writing code and debugging.

Of the preceding 4 assignments, the 2nd took me the most time, and the 
4th took me the least time. The 2nd gave me the most trouble because
of minor errors in my code that were very hard to find and it taking
more time to understand the algorithms for the convex hull.

I think writing the outlines helped me write the code. I wrote the 
outlines before writing the code. I think outlines should continue
to be required, and points should be given for them since the major
algorithm development thinking goes into writing the outlines.
If you have the outline written out, all that left is translating into
code (and debugging).

This assignment was interesting, and I liked the concept of it, but
I felt it was too hard, especially to understand what was wanted and
to get through all the different scenarios that could be possible such
as freighter, outlaw, scout, MST enabled, not MST enabled. It covered
the concepts of MST and Dijkstra's algorithm, but I'm not sure
if I fully understand graphs themselves. The idea behind the assignment
was definitely cool but I think it could have been explained better.
This assignment made me a better programmer in that it taught me
another algorithm. To make me a better programmer in the sense that
I am better at programming methods in general, this assignment could
have maybe just focused on one of the two algorithms, MST or shortest
path so that I could spend more time on that one and optimize it to
best extent I could instead of just stopping after it seemed to work.
That way, I could have been a better programmer in that I might try and
see how my algorithm worked, and see if there would be any way to 
implement it so it ran faster, and even researched other algorithms
that would be better instead of just Prim's.

I went to the recitation before and found it very useful in explaining
the algorithm. The TA was definitely well prepared, but maybe
the recitation section could have been improved by starting with a 
short intro on graphs themselves so I understood more about what
I was writing these algorithms for.

I went to the lectures before as well, but they were not as useful.
The lecturer was clear, but I felt that Dijkstra's algorithm could
have been explained a little more clearly. Also, it would have been
nice for MST to also be covered in lecture.

This course is pretty much how I expected it to be. I like that this
course is giving me a flavor of very diverse areas of CS. The course
could be made better by covering the topics that show up on the homework
by the Friday before they are due, since covering it on Monday makes
it hard to do the homework without that extra knowledge, and it is hard
to just start the homework on Monday.
