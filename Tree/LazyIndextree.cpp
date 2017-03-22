// =====================================================================================
// 
//       Filename:  LazyIndextree.cpp
//        Created:  2017년 03월 20일 21시 48분 08초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;
template <class T>
struct Indextree{
	int n;
	vector<pair<T, T> > tree;
	Indextree(const vector<T>& arr){
		n=1;
		while(n<arr.size())
			n*=2;
		n*=2;
		tree=vector<pair<T, T> > (n, {0, 0});
		init(arr);
	}
	void init(const vector<T>& arr){
		for(int i=0;i<arr.size();i++){
			int now=i+n/2;
			while(now){
				tree[now].first+=arr[i];
				now/=2;
			}
		}
	}
	T query(int a, int b){
		a+=n/2;
		b+=n/2;
		T ret=0;
		int r=1;
		while(a<=b){
			if(a&1){
				ret+=tree[a].first;
				int t=a;
				while(t){
					ret+=tree[t].second*r;
					t/=2;
				}
				a++;
			}
			if(!(b&1)){
				ret+=tree[b].first;
				int t=b;
				while(t){
					ret+=tree[t].second*r;
					t/=2;
				}
				b--;
			}
			r*=2;
			a/=2;
			b/=2;
		}
		return ret;
	}
	void update(int a, int b, T val){
		a+=n/2;
		b+=n/2;
		int r=1;
		while(a<=b){
			if(a&1){
				tree[a].second+=val;
				int t=a/2;
				while(t){
					tree[t].first+=val*r;
					t/=2;
				}
				a++;
			}
			if(!(b&1)){
				tree[b].second+=val;
				int t=b/2;
				while(t){
					tree[t].first+=val*r;
					t/=2;
				}
				b--;
			}
			r*=2;
			a/=2;
			b/=2;
		}
	}
};
int n, m, k;
int main(){
	scanf("%d%d%d", &n, &m, &k);
	vector<long long> arr(n);
	for(int i=0;i<n;i++)
		scanf("%lld", &arr[i]);
	Indextree<long long> idtree(arr);
	for(int i=0;i<m+k;i++){
		int a;
		scanf("%d", &a);
		if(a==1){
			long long b, c, d;
			scanf("%lld%lld%lld", &b, &c, &d);
			idtree.update(b-1, c-1, d);
		}
		else{
			int b, c;
			scanf("%d%d", &b, &c);
			printf("%lld\n", idtree.query(b-1, c-1));
		}
	}
	return 0;
}

