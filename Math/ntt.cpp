#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
namespace ntt{
	#define sz(v) ((int)(v).size())
    #define all(v) (v).begin(),(v).end()
    // + int *ll 
	const int A = 45, B = 24, P = A << B | 1, R = 11;
	// + ll *llu
	//const ll A=3, B=30, P = A << B | 1, R = 5;

	inline int Pow(int x, int y) {
		int r = 1;
		while (y) {
			if (y & 1) r = (long long)r * x % P;
			x = (long long)x * x % P;
			y >>= 1;
		}
		return r;
	}
	void fft(vector<int> &a, bool f) {
		int n=sz(a);
		for (int i=1,j=0;i<n;i++){
            int bit = n >> 1;
            for (;j>=bit;bit>>=1) j -= bit;
            j += bit;
            if (i < j) swap(a[i],a[j]);
        }
		for (int i = 1; i < n; i <<= 1) {
			int x = Pow(f ? Pow(R, P - 2) : R, P / i >> 1);
			for (int j = 0; j < n; j += i << 1) {
				int y = 1;
				for (int k = 0; k < i; k++) {
					int z = (long long)a[i | j | k] * y % P;
					a[i | j | k] = a[j | k] - z;
					if (a[i | j | k] < 0) a[i | j | k] += P;
					a[j | k] += z;
					if (a[j | k] >= P) a[j | k] -= P;
					y = (long long)y * x % P;
				}
			}
		}
		if (f) {
			int r=Pow(n,P-2);
			for (int i = 0; i < n; i++) a[i] = (long long)a[i] * r % P;
		}
	}

	void multiply(const vector<int> &a,const vector<int> &b,vector<int> &res)
    {
        vector<int> fa(all(a)), fb(all(b));
        int n = 1;
        while (n < max(sz(a),sz(b))) n <<= 1;
        n*=2;
        fa.resize(n); fb.resize(n);
        fft(fa,false); fft(fb,false);
        for (int i=0;i<n;i++) fa[i] = (long long)fa[i]*fb[i]%P;
        fft(fa,true);
    	res=fa;
	}
};
