#include<bits/stdc++.h>
using namespace std;

int dx[] = {1,-1,0,0};
int dy[] = {0,0,-1,1};
int DX[] = {0,-1,-1,-1,0,1,1,1};
int DY[] = {-1,-1,0,1,1,1,0,-1};
#define ll           long long int
#define fast         ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define VI           vector<vector<ll> >
#define PII          pair<ll,ll> 
#define PB           push_back

int main()
{
    fast;
    int n,m;
    cin >> n >> m;
    vector<string> a;
    PII player;
    vector<PII> monster;
    for(int i=0;i<n;i++)
    {
    	string x;
    	cin >> x;
    	for(int j=0;j<m;j++)
    	{
    		// get all the monsters
    		if( x[j]=='M' )
    			monster.PB({i,j});
    	}
    	a.PB(x);
    }

    // timer matrix contains the times at which monster attacks any cell (initially all are INT_MAX)
    int timer[n][m];
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<m;j++)
    		timer[i][j] = INT_MAX;
    }

    // do a MULTI-SOURCE BFS (push all monsters inside the queue at Time=0)
    // pre-process monsters to get time at which current cell gets attacked by any one of the monster.
    queue<PII> q;
    set<PII> visited;
    for(int i=0;i<monster.size();i++)
    {
    	q.push(monster[i]);
    	visited.insert(monster[i]);
    }
	
	int time = 0;
	while(!q.empty())
	{
		int size = q.size();
		for(int j=0;j<size;j++)
		{
			PII f = q.front();
			q.pop();	
			int r = f.first;
			int c = f.second;
			timer[r][c] = min(timer[r][c],time);

			// a monster can travel in any four direction from its current cell
			for(int k=0;k<4;k++)
			{
				int nx = r + dx[k];
				int ny = c + dy[k];
				if( nx>=0 and nx<n and ny>=0 and ny<m and a[nx][ny]!='#' and visited.find({nx,ny})==visited.end() )
				{
					q.push({nx,ny});
					visited.insert({nx,ny});
				}
			}
		}
		time++;

	}
    

	// final time matrix which has the time at which a monster attcks any cell
    for(int i=0;i<n;i++)
    {
    	for(int j=0;j<m;j++)
    	{
    		if(timer[i][j]==INT_MAX)
    			cout << "#" <<  " ";
    		else cout << timer[i][j] << " ";
    	}
    	cout << '\n';
    }
}


/*
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


*/