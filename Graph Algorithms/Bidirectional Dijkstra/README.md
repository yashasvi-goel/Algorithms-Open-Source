
Introduction :- 

The code present in this directory is an implementation of Bi-directional 		Dijkstra's Algorithm which is a basic optimisation of the traditional 	     	Dijkstra's Algorithm. 



When to Use this Algorithm :- 

Usually in the traditional Dijkstra's Algorithm we have the source, 		 travelling from which we obtain the shortest path to every edge reachable from that particular edge using edge relaxation technique. Let's say if we are given with the target and the source node of the graph and asked to find the shortest path length, we simply start propagating from both the sides until we reach the middle portion and then search for nodes in the middle which gives the optimised path. Even while propagating from both the ends we use edge relaxation when we encounter a new edge. 


Now Optimization part :- 

Since we are propagating from both the sides our search arena decreases. So we can find the shortest path by discovering half the number of nodes from source and the other half from target. This significantly reduces the time complexity for sparse Graphs , Graphs where branches increase exponentially, as well as for regular graphs. 

 
