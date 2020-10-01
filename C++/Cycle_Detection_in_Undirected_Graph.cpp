#include<iostream> 
#include <list> 
#include <limits.h>
#include <vector>
using namespace std; 

class Graph 
{ 
	int V;
	vector<int> *adj; 

public: 
 
	Graph(int V) 
{ 
	this->V = V; 
	adj = new vector<int>[V]; 
} 

void addEdge(int v, int w) 
{ 
	adj[v].push_back(w);  
	adj[w].push_back(v);  
} 
	
bool checkVer(int v, bool visited[], int parent) 
{ 
	visited[v] = true; 

	for (vector<int>::iterator i = adj[v].begin(); i != adj[v].end(); ++i) 
	{ 
		
		if (!visited[*i]) 
		{ 
		if (isCyclicUtil(*i, visited, v)) 
			return true; 
		}  
		else if (*i != parent) 
		return true; 
	} 
	return false; 
}		
	
bool checkCyclic() 
{ 
	 
	bool *vis = new bool[V]; 
	for (int i = 0; i < V; i++) 
			vis[i] = false; 


	for (int u = 0; u < V; u++) 
		if (!visited[u])
		if (cycleVer(u, vis, -1)) 
			return true; 

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
		if(g.checkCyclic())
			cout<<"1\n";
		else
			cout<<"0\n";
	}	
	return 0;
}

/* INPUT EXAMPLE
3
2 1
0 1
4 3
0 1 1 2 2 3
5 4
0 1 2 3 3 4 4 2
*/
