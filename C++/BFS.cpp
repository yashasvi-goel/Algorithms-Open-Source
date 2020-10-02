#include<bits/stdc++.h>
using namespace std;
int main()
{
    ios::sync_with_stdio(0); 
    cin.tie(0); 
    cout.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        int n,m;
        cin>>n>>m; // number of nodes and edges
        vector<int> adj[n+1];
        deque<int> q;
        int i;
        q.push_back(1); // starting node 1
        for(i=0;i<m;++i)
        {
            int e1,e2;
            cin>>e1>>e2;
            adj[e1].push_back(e2); // undirected graph
            adj[e2].push_back(e1); // undirected graph
        }
        bool b[n];
        memset(b,false,sizeof b);
        b[1]=true;
        while(q.size()!=0)
        {
            int y=q.front();
            cout<<y<<" ";
            q.pop_front();
            for(i=0;i<adj[y].size();i++)
            {
                if(b[adj[y][i]]==false)
                {
                    b[adj[y][i]]=true;
                    q.push_back(adj[y][i]);
                }
            }
        }
    }
}