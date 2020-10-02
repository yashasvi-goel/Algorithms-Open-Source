from queue import PriorityQueue
inf = 100000009

##
#p is a 2-element tuple
#dist is a list of ints
#adj is a list of list of ints
#cost is a list of list of ints
#pq is a priority queue of 3-element tuples where the first element is the negative of the second
#to permit reverse ordering
def process(p, dist, adj, cost, pq):
    cur_node, cur_d = p[1], p[0]
    itr_list = adj[cur_node]#; itr = 0
    itr_list1 = cost[cur_node]; itr1 = 0
    for itr in itr_list:
        if (cur_d + itr_list1[itr1]) < dist[itr]):
            dist[itr] = cur_d + itr_list1[itr1]
            pq.put((-1 * dist[itr], dist[itr], itr))
        itr_list1[itr1] = itr_list1[itr1] + 1

#adj and cost mean the same, s and t are ints
def bidirectional_dijkstra(adj, cost, s, t):
    global inf
    s_dist = [inf] * (len(adj) + 1)
    t_dist = [inf] * (len(adj) + 1)

    pq_s = PriorityQueue()
    pq_t = PriorityQueue()

    s_dist[s] = 0
    t_dist[t] = 0

    pq_s.put((-s_dist[s], s_dist[s], s))
    pq_t.put((-t_dist[t], t_dist[t], t))
    min_dist = -1

    s_visit = []
    t_visit = []

    while (not pq_s.empty()) and (not pq_t.empty):
        p1 = pq_s.get()
        p2 = pq_t.get()

        #already popped

        s_visit.append(p1[2])
        t_visit.append(p2[2])

        process((p1[1], p1[2]), s_dist, adj, cost, pq_s)
        process((p2[1], p2[2]), s_dist, adj, cost, pq_t)
        if p1[2] == p2[2]:
            min_dist = s_dist[p1[2]] + t_dist[p2[2]]
            break

    if min_dist == -1:
        return -1
    else:
        for i in range(len(s_visit)):
            itr_list = adj[s_visit[i]]; itr = 0
            itr_list1 = cost[s_visit[i]]; itr1 = 0

            while itr < len(itr_list):
                if s_dist[s_visit[i]] != inf and t_dist[itr_list[itr]] != inf:
                    min_dist = min(min_dist, s_dist[s_visit[i]] + t_dist[itr_list[itr]] + itr_list1[itr1])
                itr += 1
                itr1 += 1
        return min_dist

from sys import stdin,stdout
stdin = open("input.txt", "rt")
stdout = open("output.txt", "wt")

(n, m) = tuple(map(lambda s: int(s), input().split()))

adj = []; cost = []
for i in range(n+1):
    adj.append(list())
    cost.append(list())

for i in range(m):
    (u, v, w) = tuple(map(lambda s: int(s), input().split()))
    adj[u].append(v)
    adj[v].append(u)

    cost[u].append(w)
    cost[v].append(w)

(s, t) = tuple(map(lambda s: int(s), input().split()))

print(bidirectional_dijkstra(adj, cost, s, t))
