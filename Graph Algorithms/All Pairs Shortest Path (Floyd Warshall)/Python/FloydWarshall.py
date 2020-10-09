'''
	FLOYD WARSHALL ALGORITHM OR ALl PAIRS SHORTEST PATHS
	(Return shortest paths between ith and jth cities)

	Problem Statement:
	Given A graph and Q queries. A Query is of the form x y .Answer for each query is the shortest path between xth and yth city.
'''

from sys import stdin, stdout

n, m, q = map(int,input().split())
INF = 10**30

adj = [ [INF for i in range(n+1)] for j in range(n+1) ]
for i in range(m):
	x,y,z = map(int,stdin.readline().split())
	adj[x][y] = min(z,adj[x][y])
	adj[y][x] = min(z,adj[y][x])

distance = adj

for k in range(1,n+1):
	#k is an intermediate vertex between i and j
	for i in range(1,n+1):
		for j in range(1,n+1):
			'''
			if the distance through the intermediate vertex is lesser than the actual distance.
    			update the actual distance with this intermediate path's distance.
			'''
			if distance[i][k] + distance[k][j] < distance[i][j]:
				distance[i][j] = distance[i][k] + distance[k][j]

for row in distance:
	for cell in row:
		if cell == INF:
			print("INF",end=' ')
		else:
			print(cell,end=' ')
	print()

for i in range(q):
	x,y = map(int,input().split())
	if distance[x][y] == INF:
		stdout.write("-1\n")
	else:
		stdout.write(str(distance[x][y])+"\n")

'''
INP ->
4 3 5
1 2 5
1 3 9
2 3 3

1 2
2 1
1 3
1 4
3 2

OP ->
0   5   8  INF 
5   0   3  INF 
8   3   0  INF 
INF INF INF 0 


5
5
8
-1
3
'''