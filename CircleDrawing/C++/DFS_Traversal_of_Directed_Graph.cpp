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

	void dfsUtil(int root,vector<bool>& arr){
		arr[root] = true;
		cout<<root<<" ";
		for(vector<int>::iterator x = adj[root].begin(); x!=adj[root].end();x++)
			{
				if(arr[*x]==false){
					arr[root] = true;
					dfsUtil(*x,arr);
				}
			}
		
	}
	
	void dfs(){
		vector<bool> arr (V,false);
		dfsUtil(0,arr);
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
		cout<<"DFS: ";
		g.dfs();
		cout<<endl;
	
	}	
	return 0;
}

/* INPUT EXAMPLE
2
5 7
0 1
0 4
1 2
1 3
1 4
2 3
3 4
3 3
0 1
1 2
2 0
*/
