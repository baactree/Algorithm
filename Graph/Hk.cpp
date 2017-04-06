// =====================================================================================
// 
//       Filename:  Hk.cpp
//        Created:  2017년 04월 03일 23시 38분 34초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;

class Hk{
public:
	int n;
	vector<int> b;
	vector<int> level;
	vector<bool> trip;
	vector<vector<int> > &adj;
	Hk(vector<vector<int> > &adj):adj(adj){
		n=adj.size();
		b=vector<int>(n);
		level=vector<int>(n);
		trip=vector<bool>(n);
	}
	void bfs(){
		fill(level.begin(), level.end(), -1);
		queue<int> q;
		for(int i=0;i<n;i++){
			if(!trip[i]){
				q.push(i);
				level[i]=0;
			}
		}
		while(!q.empty()){
			int now=q.front();
			q.pop();
			for(int i=0;i<adj[now].size();i++){
				int there=adj[now][i];
				if(b[there]!=-1&&level[b[there]]==-1){
					level[b[there]]=level[now]+1;
					q.push(b[there]);
				}
			}
		}
	}
	bool dfs(int now){
		for(int i=0;i<adj[now].size();i++){
			int there=adj[now][i];
			if(b[there]==-1||(level[b[there]]==level[now]+1&&dfs(b[there]))){
				trip[now]=true;
				b[there]=now;
				return true;
			}
		}
		return false;
	}
	int flow(){
		fill(trip.begin(), trip.end(), false);
		fill(b.begin(), b.end(), -1);
		int total_flow=0;
		while(true){
			bfs();
			int flow=0;
			for(int i=0;i<n;i++){
				if(!trip[i]&&dfs(i))
					flow++;
			}
			if(flow==0)
				break;
			total_flow+=flow;
		}
		return total_flow;
	}
};
int n;
vector<vector<int> > adj;
int main(){
	while(scanf("%d", &n)!=EOF){
		adj.clear();
		adj.resize(n);
		for(int i=0;i<n;i++){
			int a, b;
			scanf("%d: (%d)", &a, &b);
			for(int j=0;j<b;j++){
				int in;
				scanf("%d", &in);
				adj[a].push_back(in-n);
			}
		}
		Hk hk(adj);
		printf("%d\n", hk.flow());
	}
}
