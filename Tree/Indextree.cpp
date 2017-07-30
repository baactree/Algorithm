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
		tree=vector<T>(n*2, 0);
		init(arr);
	}
	void init(const vector<T> &arr){
		for(int i=0;i<arr.size();i++){
			int idx=n+i;
			while(idx){
				tree[idx]+=arr[i];
				idx >>= 1;
			}
		}
	}
	T query(int a, int b){
		T ret=0;
		a+=n;
		b+=n;
		while(a<=b){
			if(a&1)
				ret+=tree[a++];
			if(!(b&1))
				ret+=tree[b--];
			a >>= 1;
			b >>= 1;
		}
		return ret;
	}
	void update(int a, T b){
		a+=n;
		while(a){
			tree[a] += b;
			a >>= 1;
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
			long long diff = c - arr[b - 1];
			arr[b - 1] += diff;
			idtree.update(b-1, c);		
		}
		else{
			printf("%lld\n", idtree.query(b-1, c-1));
		}
	}
	return 0;
}

