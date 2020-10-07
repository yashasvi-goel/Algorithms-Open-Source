'''
Problem Statement :-
Given a matrix containing '.' (free passage), '#' (walls) and 'M' (Monsters). The Monsters can travel in all 4 directions from their current 
location. We have to find the LEAST time at which any free passage will be attacked by any of the monsters. 
'''

dx = [1,-1,0,0];
dy = [0,0,-1,1];
INF = 10**18

n,m = map(int,input().split())
a = []
monsters = []
for i in range(n):
	x = input()
	for j in range(len(x)):
		if x[j]=='M':
			monsters.append([i,j])
	a.append(x)


# timer matrix contains the times at which monster attacks any cell (initially all are INF)
timer = [ [INF for i in range(m)]for j in range(n) ]
queue = []
visited = set()


# push all monsters inside the queue
for monster in monsters:
	queue.append(monster)
	visited.add((monster[0],monster[1]))


# do MULTI-SOURCE BFS
# process monsters to get time at which current cell gets attacked by any one of the monster.
time = 0
while len(queue):
	size = len(queue)
	for i in range(size):
		f = queue.pop(0)
		r,c = f[0],f[1]
		timer[r][c] = min(timer[r][c],time)
		for j in range(4):
			nx,ny = r+dx[j], c+dy[j]
			if 0<=nx<n and 0<=ny<m and a[nx][ny]=='.' and ((nx,ny) not in visited):
				queue.append([nx,ny])
				visited.add((nx,ny))
	time += 1

for row in timer:
	for cell in row:
		if cell == INF:
			print('#',end=' ')
		else:
			print(cell,end=' ')
	print()

'''

5 8
########
#M.....#
#.#.M#.#
#M#..#..
#.######

OP->
# # # # # # # # 
# 0 1 2 1 2 3 # 
# 1 # 1 0 # 4 # 
# 0 # 2 1 # 5 6 
# 1 # # # # # # 

'''