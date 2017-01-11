struct MCMF {
	int V, totalFlow, totalCost;
	struct Edge {
		int target, capacity, cost, flow;
		Edge* dual;
		Edge(int target, int capacity, int cost) :
			target(target), capacity(capacity), cost(cost), flow(0) {}
		inline int residual() const {
			if (flow < 0)
				return -flow;
			return capacity - flow;
		}
		inline int getCost()const {
			if (flow < 0)
				return -dual->cost;
			return cost;
		}
		void push(int amt) {
			flow += amt;
			dual->flow -= amt;
		}
	};
	vector<vector<Edge*> > adj;
	MCMF(int n) :V(n), totalFlow(0), totalCost(0), adj(n) {}
	~MCMF() {
		for (int i = 0; i < V; i++)
			for (int j = 0; j < adj[i].size(); j++)
				delete adj[i][j];
	}
	void setEdge(int u, int v, int uvCapacity, int uvCost) {
		Edge* uv = new Edge(v, uvCapacity, uvCost);
		Edge* vu = new Edge(u, 0, 0);
		uv->dual = vu;
		vu->dual = uv;
		adj[u].push_back(uv);
		adj[v].push_back(vu);
	}
	int improve(int s, int t) {
		while (true) {
			vector<int> dist(V, INF), par(V, -1), edgeNo(V, -1), capa(V, -1);
			par[s] = s;
			dist[s] = 0;
			capa[s] = INF;
			queue<int> q;
			q.push(s);
			while (!q.empty()) {
				int now = q.front();
				q.pop();
				for (int i = 0; i < adj[now].size(); i++) {
					Edge* e = adj[now][i];
					if (e->residual() <= 0)
						continue;
					int thereCost = dist[now] + e->getCost();
					if (dist[e->target] > thereCost) {
						dist[e->target] = thereCost;
						q.push(e->target);
						par[e->target] = now;
						edgeNo[e->target] = i;
						capa[e->target] = min(capa[now], e->residual());
					}
				}
			}
			if (dist[t] == INF)
				break;
			int here = t, amt = capa[t];
			while (here != s) {
				int there = par[here];
				adj[there][edgeNo[here]]->push(amt);
				here = there;
			}
			totalFlow += amt;
			totalCost += dist[t] * amt;
		}
		return totalCost;
	}
};
