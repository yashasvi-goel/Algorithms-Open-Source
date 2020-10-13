/*
    BellMan Ford ALogrithm :
    This algorithm is finds shortest path in the graph if the graph contains negative weights. It also reports
    for the negative weight cycle.

    Problem Statement -
    You play a game consisting of n rooms and m tunnels. 
    Your initial score is 0, and each tunnel increases your score by x where x may be both positive or negative. 
    You may go through a tunnel several times.
    Your task is to walk from room 1 to room n. What is the maximum score you can get?

*/
#include<bits/stdc++.h>
using namespace std;
#define ll           long long int
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
    int n,m;
    cin >> n >> m ;
    ll a[n+1][n+1];
    for(int i=0;i<=n;i++)
    {
    	for(int j=0;j<=n;j++)
    		a[i][j] = INT_MIN;
    }
    vector< vector<ll> > graph;
    for(int i=0;i<m;i++)
    {
    	ll x,y,z;
    	cin >> x >> y >> z;
    	a[x][y] = max(z,a[x][y]);
    	a[y][x] = max(z,a[y][x]);
    	graph.PB(vector<ll>{x,y,z});
    }


    // inititally all the distances in INT_MIN
    ll distance[n+1];
    for(int i=0;i<=n;i++)
    	distance[i] = INT_MIN;
    distance[1] = 0;

    // Relax all edges |V| - 1 times. A simple 
    // shortest path from src to any other 
    // vertex can have at-most |V| - 1 edges 
    for (int i = 0; i <=n-1; i++)
    { 
        for (int j = 0; j < m; j++)
        { 
            if (distance[graph[j][0]] + graph[j][2] > distance[graph[j][1]]) 
            	distance[graph[j][1]] = distance[graph[j][0]] + graph[j][2]; 
        } 
    } 
    ll ans = distance[n];

    // check for negative-weight cycles. 
    // If we get a -> 
    // shorter path, then there is a cycle. 
    bool negativeCycle = false;
    for(int i=0;i<m;i++)
    {
    	ll x = graph[i][0];
    	ll y = graph[i][1];
    	ll z = graph[i][2];
    	if(distance[x]!=INT_MIN and distance[x]+z < distance[y])
    	{
    		negativeCycle = true;
    		break;
    	}
    }

    // due to negative weight cycle the shortest path will always gets reduced while travelling this cycle. So no shortest path exists.
    if(negativeCycle)
    	ans = -1;
    cout << ans << '\n';

}

/*
I/P->
4 5
1 2 3
2 4 -1
1 3 -2
3 4 7
1 4 4

OP->
Shortest path from 1 to n is
5

*/
