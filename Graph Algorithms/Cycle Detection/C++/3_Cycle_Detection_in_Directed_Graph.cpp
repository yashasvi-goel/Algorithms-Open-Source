#include <bits/stdc++.h>
using namespace std;

class Graph{
	int V;
	vector<int> *adj;
public:
	Graph(int vertices){
		this->V = vertices;
		adj = new vector<int>[V];
	}

	void addEdge(int u, int v){
		adj[u].push_back(v);
	}	

	bool cycleVer(int curr,bool vis[],bool recStack[]){
		if(vis[curr]==false){
			vis[curr] = true;
			recStack[curr] = true;
			
			for(vector<int>::iterator i = adj[curr].begin(); i!=adj[curr].end(); i++){
				if(!vis[*i]&&cycleVer(*i,vis,recStack))
					return true;
				else if(recStack[*i])
					return true;
			}
		}
		recStack[curr] = false;
		return false;
	}

	bool checkCycle(){
		bool vis[V];
		bool recStack[V];
		memset(vis,false,sizeof(vis));
		memset(recStack,false,sizeof(recStack));
		for(int i = 0;i<V;i++){
			if(cycleVer(i,vis,recStack))
				return true;
		}
		return false;
	}
	
};

int main(){
	int T;
	cin>>T;
	while(T--){
		int V,E,i;
		cin>>V>>E;
		Graph g(V);
		for(i=0;i<E;i++){
			int x,y;
			cin>>x>>y;
			g.addEdge(x,y);
		}
		if(g.checkCycle())
			cout<<"Cycle found\n";
		else
			cout<<"No cycle found\n";
	}	
	return 0;
}

/* INPUT EXAPMPLE
3
2 2
0 1 0 0
4 3
0 1 1 2 2 3
4 3
0 1 2 3 3 2
*/
