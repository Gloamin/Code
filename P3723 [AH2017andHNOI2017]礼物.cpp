#include <bits/stdc++.h>
#define int long long
#define int long long
using namespace std;
const int MOD = 998244353, G = 3, Gi = 332748118;
const int N = 5e5 + 10;
template <typename T>
T read()
{
    char c = getchar();
    int neg = 1;
    T sum = 0;
    while (!isdigit(c))
    {
        if (c == '-')
            neg = -1;
        c = getchar();
    }
    while (isdigit(c))
    {
        sum = (sum << 3) + (sum << 1) + (c ^ 48);
        c = getchar();
    }
    return sum * neg;
}
#define Read read<int>
int qpow(int a, int b)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
int resl, binl, n, m;
int rev[N];
void NTT(int *a, int type)
{

    // for (int i = 0; i < resl; i++)
    //     cout << a[i] << endl;
    for (int i = 0; i < resl; ++i)
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    // for (int i = 0; i < resl; i++)
    //     cout << a[i] << endl;
    for (int k = 1; k < resl; k <<= 1)
    {
        int dg = qpow((type == 1) ? G : Gi, (MOD - 1) / (k << 1));
        for (int i = 0; i < resl; i += (k << 1))
            for (int j = i, g = 1; j < i + k; ++j, g = (g * dg) % MOD)
            {
                int Nx = a[j], Ny = (a[j + k] * g) % MOD;
                a[j] = (Nx + Ny) % MOD, a[j + k] = (Nx - Ny + MOD) % MOD;
            }
    }
}
void Revvv()
{
    for (int i = 0; i < resl; i++)
        rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (binl - 1));
}
int aa[N], bb[N], nn, mm;
signed main()
{
    nn = Read();
    mm = Read();
    int bas = 0, k = 0, ans = 0;
    for (int i = 1; i <= nn; i++)
    {
        aa[nn - i] = Read();
        // cout << aa[nn - i] << endl;
        ans += aa[nn - i] * aa[nn - i];
        k += aa[nn - i];
    }
    // for (int i = 0; i <= nn; i++) cout << aa[n-i] << endl;
    for (int i = 1; i <= nn; i++)
    {
        bb[i] = bb[nn + i] = Read();
        ans += bb[i] * bb[i];
        k -= bb[i];
    }
    // cout << ans << endl;
    k *= 2;
    double dcz = -1.0 * k / nn / 2;
    // cout << dcz <<endl;
    int trC = 0;
    if (dcz > 0)
        trC = (int)(dcz + 0.5);
    else
        trC = (int)(dcz - 0.5);
    ans += trC * k + nn * trC * trC;
    n = nn;
    m = 2 * nn;
    resl = 1;
    while (resl <= n + m)
        resl <<= 1, binl++;
    // cout <<"$AFd" << resl << endl;
    Revvv();
    // puts("ASDADwwaw");
    NTT(aa, 1);
    NTT(bb, 1);
    for (int i = 0; i < resl; i++)
        aa[i] = aa[i] * bb[i] % MOD;
    NTT(aa, -1);
    int inv = qpow(resl, MOD - 2);
    for (int i = 0; i <= resl; i++)
        aa[i] = aa[i] * inv % MOD;
    int Rr = 0;
    for (int i = nn; i <= 2 * nn + 1; i++)
        Rr = max(Rr, aa[i]) /*, cout << aa[i]*/;
    // cout << Rr << endl;
    cout << ans - 2 * Rr;
    return 0;
}