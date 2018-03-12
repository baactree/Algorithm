class Dinic{
public:
	const int inf = 0x3f3f3f3f;
	struct Edge{
		int v, capacity, flow;
		Edge *rev;
		Edge(int v, int capacity):v(v), capacity(capacity), flow(0), rev(0){}
		inline int residual(){
			if(flow<0)
				return -flow;
			return capacity-flow;
		}
	};
	int n;
	vector<vector<Edge*> > adj;
	vector<int> level;
	vector<int> idx;
	Dinic(int n):n(n){
		level=vector<int>(n);
		idx=vector<int>(n);
		adj=vector<vector<Edge*> > (n);
	}
	~Dinic(){
		for(int i=0;i<n;i++)
			for(int j=0;j<adj[i].size();j++)
				delete adj[i][j];
	}
	void make_edge(int u, int v, int capacity){
		Edge *uv=new Edge(v, capacity);
		Edge *vu=new Edge(u, 0);
		uv->rev=vu;
		vu->rev=uv;
		adj[u].push_back(uv);
		adj[v].push_back(vu);
	}
	bool bfs(int s, int t){
		fill(level.begin(), level.end(), -1);
		level[s]=0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int now=q.front();
			q.pop();
			for(int i=0;i<adj[now].size();i++){
				int there=adj[now][i]->v;
				int sub=adj[now][i]->residual();
				if(level[there]==-1&&sub>0){
					level[there]=level[now]+1;
					q.push(there);
				}
			}
		}
		return level[t]==-1;
	}
	int dfs(int now, int t, int amount){
		if(now==t)
			return amount;
		for(int &i=idx[now];i<adj[now].size();i++){
			int there=adj[now][i]->v;
			int sub=adj[now][i]->residual();
			if(level[there]==level[now]+1&&sub>0){
				int temp=dfs(there, t, min(amount, sub));
				if(temp>0){
					adj[now][i]->flow+=temp;
					adj[now][i]->rev->flow-=temp;
					return temp;
				}
			}
		}
		return 0;
	}
	int flow(int s, int t){
		int max_flow=0;
		while(true){
			if(bfs(s, t))
				break;
			fill(idx.begin(), idx.end(), 0);
			while(true){
				int flow=dfs(s, t, inf);
				if(flow==0)
					break;
				max_flow+=flow;
			}
		}
		return max_flow;
	}
};
