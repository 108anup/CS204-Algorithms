#include <bits/stdc++.h>

using namespace std;

class graph{
    vector<vector<int> > c;
    vector<vector<int> > f;
    int n;
    int flow_value;

public:
    //O(V^2)
    graph(int n){
	this->n = n;
	flow_value = 0;
	f = c =  vector<vector<int> >(n, vector<int>(n,0));
	// vector<vector<int> >(m, vector<int>(n,k))
	//creates a 2d vector of size m*n with all values = k
	
    }

    //O(1)
    void add_edge(int u,int v,int cap){
	c[u][v] = cap;
    }

    // O(V^2)
    graph residual(){
	graph res(n);

	for(int u = 0; u<n; u++){
	    for(int v = 0; v<n; v++){
		res.add_edge(u,v,c[u][v] - f[u][v]);
	    }
	}
	return res;
    }

    //O(V^2)
    void BFS(int s, int t, vector<int> &path, vector<char> &color){
	path.clear();
	color.clear();
	
	vector<int> p(n,-1);
	color = vector<char>(n,'W');
	color[s] = 'G';

	queue<int> q;
	q.push(s);

	while(!q.empty()){
	    int u = q.front();
	    q.pop();

	    for(int v = 0; v<n; v++){
		if(c[u][v]>0 && color[v] == 'W'){
		    p[v] = u;
		    color[v] = 'G';
		    q.push(v);
		}
	    }

	    color[u] = 'B';
	}

	if(color[t] == 'B'){
	    int node = t;
	    while(node!=-1){
		path.push_back(node);
		node = p[node];
	    }
	    reverse(path.begin(),path.end());
	}
    } 

    //O(EV*BFS)
    vector<pair<int,int> > mincut(int s, int t){
	vector<int> path;
	vector<char> color;
	while(true){
	    graph gf = residual();
	    gf.BFS(s,t, path, color);
	    if(!path.empty()){
		int cp = INT_MAX;
		for(int i = 0; i<path.size()-1; i++){
		    int u = path[i];
		    int v = path[i+1];
		    
		    cp = min(cp,c[u][v]);
		}
		flow_value += cp;
		for(int i = 0; i<path.size()-1; i++){
		    int u = path[i];
		    int v = path[i+1];

		    f[u][v] += cp;
		    f[v][u] = -f[u][v];
		}
	    }
	    else{
		break;
	    }
	}
	
	vector<pair<int,int> > mc;
	for(int u = 0; u<n; u++){
	    for(int v = 0; v<n; v++){
		if(color[u] == 'B' && color[v] == 'W' && c[u][v]!=0){
		    mc.push_back(make_pair(u,v));
		}
	    }
	}
	return mc;
    }
};


int main()
{
    int t;
    cin>>t;

    while(t--){
	int n;
	cin>>n;

	graph g(n);

	int cap;
	for(int u = 0; u<n; u++){
	    for(int v = 0; v<n; v++){
		cin>>cap;
		g.add_edge(u,v,cap);
	    }
	}

	int s,t;
	cin>>s>>t;

	vector<pair<int,int> > mc = g.mincut(s,t);
	for(int i = 0; i<mc.size(); i++){
	    cout<<mc[i].first<<" "<<mc[i].second<<" "; 
	}
	cout<<"\n";
    }
    return 0;
}
