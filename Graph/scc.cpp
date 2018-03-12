struct Scc{
	vector<vector<int>> adj;
	vector<int> scc;
	vector<int> discoverd;
	stack<int> st;
	int vertex_count;
	int scc_count;
	int v;
	Scc(const vector<vector<int>> &adj):adj(adj){
		v=adj.size()-1;
		scc=vector<int>(v+1, -1);
		discoverd=vector<int>(v+1, -1);
		vertex_count=0;
		scc_count=0;
	}
	int dfs(int now){
		int ret=discoverd[now]=vertex_count++;
		st.push(now);
		for(int i=0;i<adj[now].size();i++){
			int there=adj[now][i];
			if(discoverd[there]==-1)
				ret=min(ret, dfs(there));
			else if(scc[there]==-1)
				ret=min(ret, discoverd[there]);
		}
		if(ret==discoverd[now]){
			while(true){
				int temp=st.top();
				st.pop();
				scc[temp]=scc_count;
				if(temp==now)
					break;
			}
			scc_count++;
		}
		return ret;
	}
	vector<int> make_scc(){
		for(int i=1;i<=v;i++)
			if(discoverd[i]==-1)
				dfs(i);
		return scc;
	}
};
