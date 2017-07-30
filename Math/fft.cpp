
// fft : convolution을 구하는데 nlogn의 시간으로 가능
// f(x), g(x) 가 ax^n+bx^(n-1)+cx^(n-2).....+z 꼴
// f(x)->(dft)->f'(x) 함수 f를 dft하여 변환
// g(x)->(dft)->g'(x) 함수 g를 dft하여 변환
// f'*g'(x) O(n) 시간에 가능 그냥 곱하면 된다! (so easy!!)
// f'*g'(x)->(dft)->f*g(x) 로 역변환 하면
// 두 함수의 곱을 O(nlogn)에 가능
// 기존 dft는 O(n^2)이 걸리지만 fft를 사용하면 O(nlogn)에 가능 
//
// convolution 
// c[i] = sigma(0<=j<=i)(a[j]*b[i-j]) 의 형태를 가진
// c를 convolution이라고 한다.

namespace fft{
    #define sz(v) ((int)(v).size())
    #define all(v) (v).begin(),(v).end()
    typedef complex<double> base;
    const double pi=acos(-1.0);
    void fft(vector <base> &a, bool invert)
    {
        int n = sz(a);
        for (int i=1,j=0;i<n;i++){
            int bit = n >> 1;
            for (;j>=bit;bit>>=1) j -= bit;
            j += bit;
            if (i < j) swap(a[i],a[j]);
        }
        for (int len=2;len<=n;len<<=1){
            double ang = 2*pi/len*(invert?-1:1);
            base wlen(cos(ang),sin(ang));
            for (int i=0;i<n;i+=len){
                base w(1);
                for (int j=0;j<len/2;j++){
                    base u = a[i+j], v = a[i+j+len/2]*w;
                    a[i+j] = u+v;
                    a[i+j+len/2] = u-v;
                    w *= wlen;
                }
            }
        }
        if (invert){
            for (int i=0;i<n;i++) a[i] /= n;
        }
    }
    
    void multiply(const vector<int> &a,const vector<int> &b,vector<int> &res)
    {
        vector <base> fa(all(a)), fb(all(b));
        int n = 1;
        while (n < max(sz(a),sz(b))) n <<= 1;
        //큰수 곱셈의 경우에는 a*b= a.size()+b.size()-1 의 크기를 가지므로 n*=2
        n*=2;
        fa.resize(n); fb.resize(n);
        fft(fa,false); fft(fb,false);
        for (int i=0;i<n;i++) fa[i] *= fb[i];
        fft(fa,true);
        res.resize(n);
        for (int i=0;i<n;i++) res[i] = int(fa[i].real()+(fa[i].real()>0?0.5:-0.5));
    }
};