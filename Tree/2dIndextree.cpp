// =====================================================================================
// 
//       Filename:  2dIndextree.cpp
//        Created:  2017년 03월 19일 23시 07분 05초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;
vector<vector<int> > mat;
int n, m;
struct Indextree{
	vector<vector<int> > tree;
	int n;
	Indextree(const vector<vector<int> > &mat){
		n=1;
		while(n<mat.size())
			n*=2;
		n*=2;
		tree=vector<vector<int> >(n, vector<int>(n, 0));
		init(mat);
	}
	void init(const vector<vector<int> > &mat){
		for(int i=0;i<mat.size();i++){
			for(int j=0;j<mat[i].size();j++){
				tree[i+n/2][j+n/2]=mat[i][j];
				int idx=j+n/2;
				while(idx>1){
					idx/=2;
					tree[i+n/2][idx]=tree[i+n/2][idx*2]+tree[i+n/2][idx*2+1];
				}
			}
			for(int j=1;j<n;j++){
				int idx=i+n/2;
				while(idx>1){
					idx/=2;
					tree[idx][j]=tree[idx*2][j]+tree[idx*2+1][j];
				}
			}
		}
	}
	int query(int x1, int y1, int x2, int y2){
		x1+=n/2;
		x2+=n/2;
		int ret=0;
		while(x1<=x2){
			if(x1&1){
				int a=y1+n/2;
				int b=y2+n/2;
				while(a<=b){
					if(a&1){
						ret+=tree[x1][a];
						a++;
					}
					if(!(b&1)){
						ret+=tree[x1][b];
						b--;
					}
					a/=2;
					b/=2;
				}
				x1++;
			}
			if(!(x2&1)){
				int a=y1+n/2;
				int b=y2+n/2;
				while(a<=b){
					if(a&1){
						ret+=tree[x2][a];
						a++;
					}
					if(!(b&1)){
						ret+=tree[x2][b];
						b--;
					}
					a/=2;
					b/=2;
				}
				x2--;
			}
			x1/=2;
			x2/=2;
		}
		return ret;
	}
	void update(int x, int y, int val){
		x+=n/2;
		y+=n/2;
		tree[x][y]=val;
		int tx=x;
		while(tx>1){
			int ty=y;
			while(ty>1){
				tree[tx/2][ty]=tree[tx/2*2][ty]+tree[tx/2*2+1][ty];
				ty/=2;
				tree[tx][ty]=tree[tx][ty*2]+tree[tx][ty*2+1];
				tree[tx/2][ty]=tree[tx/2*2][ty]+tree[tx/2*2+1][ty];
			}
			tx/=2;
		}
	}
};
int main(){
	scanf("%d%d", &n, &m);
	mat=vector<vector<int> >(n, vector<int>(n, 0));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d", &mat[i][j]);
	Indextree idtree(mat);
	for(int i=0;i<m;i++){
		int w;
		scanf("%d", &w);
		if(w){
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			printf("%d\n", idtree.query(x1-1, y1-1, x2-1, y2-1));
		}
		else{
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			idtree.update(x-1, y-1, c);
		}
	}
	return 0;
}

