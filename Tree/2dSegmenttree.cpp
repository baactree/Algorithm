// =====================================================================================
// 
//       Filename:  2dSegmenttree.cpp
//        Created:  2017년 03월 20일 00시 16분 15초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;
struct Segmenttree{
	vector<vector<int> > tree;
	int n;
	Segmenttree(const vector<vector<int> > &mat){
		n=1;
		while(n<mat.size())
			n*=2;
		n*=2;
		tree=vector<vector<int> >(n, vector<int>(n, 0));
		init(mat, 0, mat.size()-1, 1, 0, mat.size()-1, 1);
	}
	int init(const vector<vector<int> > &mat, int xle, int xri, int xnode, int yle, int yri, int ynode){
		if(xle==xri){
			if(yle==yri)
				return tree[xnode][ynode]=mat[xle][yle];
			int mid=(yle+yri)/2;
			int left_ret=init(mat, xle, xri, xnode, yle, mid, ynode*2);
			int right_ret=init(mat, xle, xri, xnode, mid+1, yri, ynode*2+1);
			return tree[xnode][ynode]=left_ret+right_ret;
		}
		int mid=(xle+xri)/2;
		init(mat, xle, mid, xnode*2, yle, yri, ynode);
		init(mat, mid+1, xri, xnode*2+1, yle, yri, ynode);
		for(int i=1;i<n;i++)
			tree[xnode][i]=tree[xnode*2][i]+tree[xnode*2+1][i];
		return tree[xnode][ynode];
	}
	int query(int x1, int y1, int x2, int y2, int xle, int xri, int xnode, int yle, int yri, int ynode){
		if(x1>xri||x2<xle)
			return 0;
		if(x1<=xle&&xri<=x2){
			if(y1>yri||y2<yle)
				return 0;
			if(y1<=yle&&yri<=y2)
				return tree[xnode][ynode];
			int mid=(yle+yri)/2;
			return query(x1, y1, x2, y2, xle, xri, xnode, yle, mid, ynode*2)+
				query(x1, y1, x2, y2, xle, xri, xnode, mid+1, yri, ynode*2+1);
		}
		int mid=(xle+xri)/2;
		return query(x1, y1, x2, y2, xle, mid, xnode*2, yle, yri, ynode)+
			query(x1, y1, x2, y2, mid+1, xri, xnode*2+1, yle, yri, ynode);
	}
	int update(int x, int y, int val, int xle, int xri, int xnode, int yle, int yri, int ynode){
		if(x<xle||xri<x)
			return tree[xnode][ynode];
		if(xle==xri){
			if(y<yle||yri<y)
				return tree[xnode][ynode];
			if(yle==yri)
				return tree[xnode][ynode]=val;
			int mid=(yle+yri)/2;
			int left_ret=update(x, y, val, xle, xri, xnode, yle, mid, ynode*2);
			int right_ret=update(x, y, val, xle, xri, xnode, mid+1, yri, ynode*2+1);
			return tree[xnode][ynode]=left_ret+right_ret;
		}
		int mid=(xle+xri)/2;
		update(x, y, val, xle, mid, xnode*2, yle, yri, ynode);
		update(x, y, val, mid+1, xri, xnode*2+1, yle, yri, ynode);
		int ty=y+n/2;
		while(ty>1){
			tree[xnode][ty]=tree[xnode*2][ty]+tree[xnode*2+1][ty];
			ty/=2;
		}
		return tree[xnode][ynode]=tree[xnode*2][ynode]+tree[xnode*2+1][ynode];
	}
};
vector<vector<int> > mat;
int n, m;
int main(){
	scanf("%d%d", &n, &m);
	mat=vector<vector<int> >(n, vector<int>(n, 0));
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			scanf("%d", &mat[i][j]);
	Segmenttree sgtree(mat);
	for(int i=0;i<m;i++){
		int w;
		scanf("%d", &w);
		if(w){
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			printf("%d\n", sgtree.query(x1-1, y1-1, x2-1, y2-1, 0, n-1, 1, 0, n-1, 1));
		}
		else{
			int x, y, c;
			scanf("%d%d%d", &x, &y, &c);
			sgtree.update(x-1, y-1, c, 0, n-1, 1, 0, n-1, 1);
		}
	}
	return 0;
}

