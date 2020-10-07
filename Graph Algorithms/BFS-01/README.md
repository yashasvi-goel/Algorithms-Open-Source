Introduction :-

0-1 Breadth First Search Algorithm is an optimisation over the regular Dijkstra's Algorithm but for Graphs with edge weights either 0 or 1


Implementation Details :- 

0-1 BFS is implemented with the help of the deque (doubly ended queue). It is very similiar to the regular Dijkstra's Algorithm except for the fact that it has linear time complexity. The edges with 0 edge weights are pushed at front and those with 1 are pushed at the back in this way we can maintain the deque and make it function like a priority_queue thereby eliminating the use of it

Improvement over complexity:- 

Linear Time Complexity O(n)
  
