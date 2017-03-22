// =====================================================================================
// 
//       Filename:  Sqrtdecomposition.cpp
//        Created:  2017년 03월 22일 16시 03분 01초
//       Compiler:  g++ -O2 -std=c++14
//         Author:  baactree ,  bsj0206@naver.com
//        Company:  Chonnam National University
// 
// =====================================================================================

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int n, m, k;
ll arr[1000000];
ll sq[1500];
int sz;
ll query(int l, int r){
	int lidx=l/sz;
	int ridx=r/sz;
	ll ret=0;
	if(lidx==ridx){
		for(int i=l;i<=r;i++)
			ret+=arr[i];
		return ret;
	}
	for(int i=lidx+1;i<ridx;i++)
		ret+=sq[i];
	for(int i=l;i<(lidx+1)*sz;i++)
		ret+=arr[i];
	for(int i=ridx*sz;i<=r;i++)
		ret+=arr[i];
	return ret;
}
int main(){
	scanf("%d%d%d", &n, &m, &k);
	sz=sqrt(n);
	for(int i=0;i<n;i++){
		scanf("%lld", &arr[i]);
		sq[i/sz]+=arr[i];
	}
	for(int i=0;i<m+k;i++){
		int a;
		scanf("%d", &a);
		if(a==1){
			int b;
			ll c;
			scanf("%d%lld", &b, &c);
			ll diff=c-arr[b-1];
			arr[b-1]+=diff;
			sq[(b-1)/sz]+=diff;
		}
		else{
			int b, c;
			scanf("%d%d", &b, &c);
			printf("%lld\n", query(b-1, c-1));
		}
	}
	return 0;
}

