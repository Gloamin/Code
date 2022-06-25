#include <bits/stdc++.h>
#define ll long long
#define int long long 
using namespace std;
struct cplx
{
    ll re, im;
    cplx(ll _re = 0, ll _im = 0)
    {
        re = _re;
        im = _im;
    }
    const bool operator==(cplx y) const
    {
        return re == y.re && im == y.im;
    }
};
ll mod;
ll itwice;
cplx operator*(cplx x, cplx y)
{
    return cplx((x.re * y.re % mod + itwice * x.im % mod * y.im) % mod, (x.re * y.im % mod + y.re * x.im % mod) % mod);
}
cplx qpow(cplx a, int b)
{
    cplx res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a;
        a = a * a;
        b >>= 1;
    }
    return res;
}
bool chk(int x)
{
    return qpow(x, (mod - 1) / 2) == 1;
}
void work(int n, int p, int &res0, int &res1)
{
    mod = p;
    int a = rand() % mod;
    while (a == 0 || chk((a * a + mod - n) % mod) != 0)
        a = rand() % mod;
    itwice = (a * a + mod - n) % mod;
    res0 = qpow(cplx(a, 1), (mod + 1) >> 1).re;
    res1 = mod - res0;
}
signed  main()
{
    srand(time(NULL));
    // ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while (T--)
    {
        int n, p;
        cin >> n >> p;
        int x0=0, x1=0;
        if (n == 0)
        {
            cout << "0\n";
            continue;
        }
        work(n, p, x0, x1);
        if (x0 <= 0)
        {
            cout << "Hola!\n";
        }
        else
        {
            if (x0 == x1)
            {
                cout << x0 << endl;
            }
            else
            {
                if (x0 % p > x1 % p)
                    swap(x0, x1);
                cout << x0 << " " << x1 << endl;
            }
        }
    }
    return 0;
}