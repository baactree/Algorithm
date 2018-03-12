// 디오판토스 방정식
// ax+by=c
// (a,b)|c 인 경우에만 해가 존재 (필요충분조건)
// ax+by=(a,b)의 해를 x0,y0라고 하고
// c=k*(a,b) 라고 할 때
// 초기해는 k*x0, k*y0이다
// 일반해는 k*x0+b/(a,b), k*y0-a/(a,b) 이다
//
// 확장된 유클리드 호제법
// ax+by=(a,b)의  {(a,b),{x0,y0}} 리턴
//
// 일차 합동 방정식 ax=c(mod b)
// ax+by=c 의 해를 구하면 됨
typedef long long ll;
pair<ll, pair<ll, ll> > gcd(ll a, ll b){
    ll r, r1, r2;
    ll s, s1, s2;
    ll t, t1, t2;
    r1 = a;
    r2 = b;
    s1 = 1;
    s2 = 0;
    t1 = 0;
    t2 = 1;
    ll q;
    while (r2 > 0){
        q = r1 / r2;
        r = r1 - q*r2;
        r1 = r2;
        r2 = r;
        s = s1 - q*s2;
        s1 = s2;
        s2 = s;
        t = t1 - q*t2;
        t1 = t2;
        t2 = t;
    }
    return{ r1, { s1, t1 } };
}