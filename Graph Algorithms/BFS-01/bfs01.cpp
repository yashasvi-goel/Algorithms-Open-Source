#include<bits/stdc++.h>
using namespace std;
#define inf 1000000007

void bfs01(vector<vector<int>> &adj, vector<vector<int>> &cost, int n, int source) {
	//distance array holds the distance of the vertices
	vector<int> dist(n + 1);
	for (int i = 1; i <= n; i++)
		dist[i] = inf;


	//initialising the distance of the source to be equal to zero
	dist[source] = 0;

	//doubly ended queue to eliminate the use of Priority Queue
	deque<int> d;
	d.push_front(source);

	//iterating until the deque is empty
	while (!d.empty()) {
		int node = d.front();
		d.pop_front();

		vector<int>::const_iterator itr = cost[node].begin();
		for (auto child : adj[node]) {

			//calculate the new distance to perform the step of relaxation
			int new_dist = dist[node] + *itr;

			//perform the relaxation step
			if (new_dist < dist[child]) {
				if (*itr == 1)
					d.push_back(child);
				else
					d.push_back(child);
			}
		}
	}

	//now print all the distances from the source node
	for (int i = 1; i <= n; i++) {
		if (dist[i] == -1)
			cout << "Not Reachable ";
		else
			cout << dist[i];
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
		//there's a undirected edge from u to v with edge weight w
		int u, v, w;
		cin >> u >> v >> w;

		adj[u].push_back(v);
		adj[v].push_back(u);

		cost[u].push_back(w);
		cost[v].push_back(w);
	}

	int source;
	cin >> source;

	bfs01(adj, cost, n, source);
	return 0;
}
