1.5 Analysis

When the maze has a lot of path divergences, the average time will be better for BFS, since we can 
"simultaneously" look at all the paths, and can find the end faster. However, if DFS picks a path to start
that is not the right one, it will continue along that path until it finally reaches a dead end. In this case, BFS
will be better to look at all options equally. However, DFS, will have a better best case scenario, if it always
decides to go on the right path first, in which case, there will be no backtracking at all. However, this can't be
expected at all times.



One example of using a stack is in placing items in a cupboard. The last item placed will be the first item to be
removed, while the first item placed will be the last item to be removed. Items are added and removed
from the same end of the cupboard (where the opening is).

An example of using a queue is for standing in line at the movie theater. The first person to enter the line
will get his/her ticket first, while the people to enter the line last will get their tickets last. People join
at the back of the line and leave from the front of it.