#include <bits/stdc++.h>
using namespace std;

#define MAXN 500005
 
int N,SA[MAXN],lcp[MAXN];
char S[MAXN];
 
void LCP()
{
    int i,j,k=0;
    vector <int> rank(N+1,0);
    for (i=1;i<=N;i++) rank[SA[i]] = i;
    for (i=1;i<=N;lcp[rank[i++]]=k)
        for (k?k--:0,j=SA[rank[i]-1];S[i+k]==S[j+k];k++);
}


//출처: http://blog.myungwoo.kr/57 [PS 이야기]
