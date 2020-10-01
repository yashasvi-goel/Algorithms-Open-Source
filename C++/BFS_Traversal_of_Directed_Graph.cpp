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
	bool bfs(int root){
		queue<int> q; // stores the next node to visit
		set<int> s; // stores visited nodes
		
		q.push(root);
		s.insert(root);
	
		while(!q.empty()){
			int temp = q.front();
			
			q.pop();
			cout<<temp<<" ";
			for(vector<int>::iterator x = adj[temp].begin(); x!=adj[temp].end();x++)
			{
				if(s.find(*x)==s.end()){
				
					q.push(*x);
					s.insert(*x);
			}
		}	
    }

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
		cout<<"BFS: ";
		g.bfs(0);
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
