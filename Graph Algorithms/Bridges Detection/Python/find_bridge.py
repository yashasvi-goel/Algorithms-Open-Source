from collections import defaultdict 

n, m = map(int,input().split())
graph = defaultdict(list)
for i in range(m):
    x,y = map(int,input().split())
    graph[x].append(y)
    graph[y].append(x)
Time = 0

def bridgeUtil(u, visited, parent, low, disc):
    global Time
    visited[u]= True
    disc[u] = Time 
    low[u] = Time 
    Time += 1 
    for v in graph[u]: 
        if visited[v] == False : 
            parent[v] = u 
            bridgeUtil(v, visited, parent, low, disc) 
            low[u] = min(low[u], low[v]) 
            if low[v] > disc[u]: 
                print ("%d %d" %(u,v)) 
  
                  
        elif v != parent[u]: # Update low value of u for parent function calls. 
            low[u] = min(low[u], disc[v]) 

def bridge(): 
    visited = [False] * (n) 
    disc = [float("Inf")] * (n) 
    low = [float("Inf")] * (n) 
    parent = [-1] * (n) 
    for i in range(n): 
        if visited[i] == False: 
            bridgeUtil(i, visited, parent, low, disc) 

bridge()


 
