from collections import defaultdict

def KahnAlgo(n,d,inDegree):
    topOrder = []
    q = []
    for i in range(n):
        if inDegree[i]==0:
            q.append(i)
    while len(q)>0:
        x = q.pop(0)
        topOrder.append(x)
        l = d[x]
        for e in l:
            inDegree[e] -= 1
            if inDegree[e] == 0:
                q.append(e)
    return topOrder



n, m = map(int,input().split())
pre = []
inDegree = [ 0 for i in range(n+1) ]
d = defaultdict(list)
for i in range(m):
    x,y = map(int,input().split())
    d[y].append(x)
    inDegree[x]+=1
print(d)
ans = KahnAlgo(n,d,inDegree)
print(ans)
