#include<bits/stdc++.h>
#define inf 1000000009
using namespace std;

//implmenting bidirectional dijkstra


// building the process function to perform the edge relaxation for the outgoing edges from current node
void process(pair<int, int> p, vector<int> &dist, vector<vector<int>> &adj, vector<vector<int>> &cost, priority_queue < pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> &pq) {

	int cur_node = p.second, cur_d = p.first;

	vector<int>::const_iterator itr = adj[cur_node].begin();
	vector<int>::const_iterator itr1 = cost[cur_node].begin();

	for (; itr != adj[cur_node].end(); itr++) {
		// performing the process of relaxation
		if (cur_d + *itr1 < dist[*itr]) {
			dist[*itr] = cur_d + *itr1;
			pq.push({dist[*itr], *itr});
		}
		*itr1++;
	}
}
int bidirectional_dijkstra(vector<vector<int>> &adj, vector<vector<int>> &cost, int s, int t) {
	// s_dist -> stores the distance of the nodes evaluated from source node that can be reached before meet in the middle
	// t_dist -> stores the distance of the nodes evaluated from target node that can be reached before meet in the middle
	vector<int> s_dist(adj.size() + 1, inf), t_dist(adj.size() + 1, inf);

	//pq_s -> from the start node
	//pq_t -> from the target node
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_s;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq_t;

	s_dist[s] = 0;
	t_dist[t] = 0;

	pq_s.push({s_dist[s], s});
	pq_t.push({t_dist[t], t});
	int min_dist = -1;

	vector<int> s_visit, t_visit;

	while (!pq_s.empty() && !pq_t.empty()) {
		pair<int, int> p1 = pq_s.top(), p2 = pq_t.top();
		//cout << p1.second << " " << p2.second << "\n";
		// pushing the elements visited while calculating the shortest path from target and from source
		pq_s.pop();
		pq_t.pop();


		s_visit.push_back(p1.second);
		t_visit.push_back(p2.second);



		process(p1, s_dist, adj, cost, pq_s);
		process(p2, t_dist, adj, cost, pq_t);
		if (p1.second == p2.second) {
			min_dist = s_dist[p1.second] + t_dist[p2.second];
			break;
		}
	}

	if (min_dist == -1)
		return -1;
	else {

		for (int i = 0; i < s_visit.size(); i++) {
			vector<int>::const_iterator itr = adj[s_visit[i]].begin();
			vector<int>::const_iterator itr1 = cost[s_visit[i]].begin();

			while (itr != adj[s_visit[i]].end()) {
				if (s_dist[s_visit[i]] != inf  && t_dist[*itr] != inf) {
					min_dist = min(min_dist, s_dist[s_visit[i]] + t_dist[*itr] + (*itr1));
				}
				itr++;
				itr1++;
			}
		}

		return min_dist;
	}
}
signed main() {
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif

	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	// input of the number of vertices in the graph
	int n;
	cin >> n;
	// input of the number of edges in a graph
	int m;
	cin >> m;
	// adjacency list for storing the edges of the graph
	vector<vector<int>> adj(n + 1, vector<int>());
	// two-d vectors of cost for storing the cost of travelling from one edge to other
	vector<vector<int>> cost(n + 1, vector<int>());

	while (m--) {
		int u, v, w;
		cin >> u >> v >> w;

		adj[u].push_back(v);
		adj[v].push_back(u);

		cost[u].push_back(w);
		cost[v].push_back(w);
	}
	int s, t;
	cin >> s >> t;
	int dist = bidirectional_dijkstra(adj, cost, s, t);
	cout << dist << "\n";
	return 0;
}
