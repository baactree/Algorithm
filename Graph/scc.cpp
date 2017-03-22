// =====================================================================================
// 
//       Filename:  scc.cpp
//        Created:  2017년 03월 22일 15시 01분 57초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;
struct Scc{
	vector<vector<int>> adj;
	vector<int> scc;
	vector<int> discoverd;
	stack<int> st;
	int vertex_count;
	int scc_count;
	int v;
	Scc(const vector<vector<int>> &adj){
		v=adj.size()-1;
		this->adj=adj;
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

vector<vector<int>> adj;
int v, e;
int main(){
	scanf("%d%d", &v, &e);
	adj=vector<vector<int>>(v+1);
	for(int i=0;i<e;i++){
		int a, b;
		scanf("%d%d", &a, &b);
		adj[a].push_back(b);	
	}
	Scc scc(adj);
	vector<int> ans=scc.make_scc();
	vector<vector<int>> out(v+1);
	for(int i=0;i<ans.size();i++){
		if(ans[i]==-1)
			continue;
		out[ans[i]].push_back(i);
	}
	sort(out.begin(), out.begin()+scc.scc_count);
	printf("%d\n", scc.scc_count);
	for(int i=0;i<scc.scc_count;i++){
		for(int j=0;j<out[i].size();j++)
			printf("%d ", out[i][j]);
		printf("-1\n");
	}
	return 0;
}

