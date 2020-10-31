#include<bits/stdc++.h>
using namespace std;

stack<int> st;
void top_sort(vector<vector<int> > &v,bool vis[],int n)
{
	vis[n] = true;
	for(int i=0;i<v[n].size();i++)
	{
		if( vis[v[n][i]] == false)
			top_sort(v,vis,v[n][i]);
	}
	st.push(n);
}

int main()
{
	
	int n,m;
	cin >> n >> m;
	vector< vector<int> > v(n+1);
	for(int i=0;i<m;i++)
	{
		int x,y;
		cin >> x >> y;
		v[x].push_back(y);
	}
	bool vis[n+1];
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++)
	{
		if( vis[i] == false)
			top_sort(v,vis,i);
	}
	while(!st.empty())
	{
		cout << st.top() << " ";
		st.pop();
	}
	cout << endl;
}