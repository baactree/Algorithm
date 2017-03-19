// =====================================================================================
// 
//       Filename:  Indextree.cpp
//        Created:  2017년 03월 19일 22시 30분 41초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct Indextree{
	vector<T> tree;
	int n;
	Indextree(const vector<T> &arr){
		n=1;
		while(n<arr.size())
			n*=2;
		n*=2;
		tree=vector<T>(n, 0);
		init(arr);
	}
	void init(const vector<T> &arr){
		for(int i=0;i<arr.size();i++){
			tree[n/2+i]=arr[i];
			int idx=n/2+i;
			while(idx>1){
				tree[idx/2]+=arr[i];
				idx/=2;
			}
		}
	}
	T query(int a, int b){
		T ret=0;
		a+=n/2;
		b+=n/2;
		while(a<=b){
			if(a==b){
				ret+=tree[a];
				break;
			}
			if(a&1){
				ret+=tree[a];
				a/=2;
				a++;
			}
			else
				a/=2;
			if(b&1)
				b/=2;
			else{
				ret+=tree[b];
				b/=2;
				b--;
			}
		}
		return ret;
	}
	void update(int a, T b){
		a+=n/2;
		T temp=tree[a];
		tree[a]=b;
		while(a>1){
			tree[a/2]=tree[a/2]-temp+b;
			a/=2;
		}
	}
};
int main(){
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	vector<long long> arr(n);
	for(int i=0;i<n;i++)
		scanf("%lld", &arr[i]);
	Indextree<long long> idtree(arr);
	for(int i=0;i<m+k;i++){
		long long a, b, c;
		scanf("%lld%lld%lld", &a, &b, &c);
		if(a==1){
			idtree.update(b-1, c);		
		}
		else{
			printf("%lld\n", idtree.query(b-1, c-1));
		}
	}
	return 0;
}

