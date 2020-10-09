/*
	FLOYD WARSHALL ALGORITHM OR ALl PAIRS SHORTEST PATHS
	(Return shortest paths between ith and jth cities)

	Problem Statement:
	Given A graph and Q queries. A Query is of the form x y .Answer for each query is the shortest path between xth and yth city.
*/
#include<bits/stdc++.h>
using namespace std;
#define ll          long long int
#define fast         ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define INF          1e18
#define MOD          1000000007
#define Vi           vector<ll> 
#define Vs           vector<string>
#define VI           vector<vector<ll> >
#define PII          pair<ll,ll> 
#define PSI          pair<string,ll>
#define PB           push_back


int dx[] = {1,-1,0,0};
int dy[] = {0,0,-1,1};
int DX[] = {0,-1,-1,-1,0,1,1,1};
int DY[] = {-1,-1,0,1,1,1,0,-1};

int main()
{
    fast;
    int n,m,q;
    cin >> n >> m >> q;

    // Graph as Adjaceny Matrix
    ll adj[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
    	for(int j=0;j<=n;j++)
    		adj[i][j] = INF;
    }

    // assigning weights of paths in the adjacency Matrix
    for(int i=0;i<m;i++)
    {
    	ll x,y,z;
    	cin >> x >> y >> z;
    	adj[x][y] = min(z,adj[x][y]);
    	adj[y][x] = min(z,adj[y][x]);
    }

    ll distance[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
    	for(int j=0;j<=n;j++)
    	{
    		if(i==j)
    			distance[i][j] = 0;
    		else
    			distance[i][j] = adj[i][j];
    	}
    }

   
    for(int k=1;k<=n;k++)
    {
    	// k is an intermediate vertex between i and j
    	for(int i=1;i<=n;i++)
    	{
    		for(int j=1;j<=n;j++)
    		{

    			// if the distance through the intermediate vertex is lesser than the actual distance.
    			// update the actual distance with this intermediate path's distance.
    			if(distance[i][k]!=INF and distance[k][j]!=INF and distance[i][k]+distance[k][j] < distance[i][j] )
    				distance[i][j]  =distance[i][k] + distance[k][j];
    			
    		}
    	}
    }
    for(int i=1;i<=n;i++)
    {
    	for(int j=1;j<=n;j++)
    	{
    		if(distance[i][j]==INF)
    			cout << "INF ";
    		else
    			cout << distance[i][j] << " ";
    	}
    	cout << "\n";
    }
    for(int i=0;i<q;i++)
    {
    	int x,y;
    	cin >> x >> y;
    	if(distance[x][y] == INF)
    		cout << "-1\n";
    	else cout << distance[x][y] << "\n";
    }

}

/*
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


*/
