#include <iostream>
#include <cstdio>
#include <cstring>
#define ll long long
using namespace std;
ll mod = 998244353, G[2] = {332748118, 3};
ll A[450001], invA[450001], f[450001], g[450001], inv;
int len, m, rev[450001];
ll qp(ll x, int y)
{
    if (y == 0)
        return 1ll;
    if (y == 1)
        return x;
    ll res = qp(x, y >> 1);
    (res *= res) %= mod;
    if (y & 1)
        (res *= x) %= mod;
    return res;
}
void NTT(ll *a, int flag, int n)
{
    ll w, w_n, x, y;
    for (int i = 1; i < n; i += 1)
    {
        if (i < rev[i])
            swap(a[i], a[rev[i]]);
    }
    for (int i = 1; i < n; i <<= 1)
    {
        w_n = qp(G[flag], (mod - 1) / (i << 1));
        for (int j = 0; j < n; j += (i << 1))
        {
            w = 1ll;
            for (int k = j; k < i + j; k += 1)
            {
                x = a[k];
                y = (a[k + i] * w) % mod;
                a[k] = (x + y) % mod;
                a[k + i] = (x - y + mod) % mod;
                (w *= w_n) %= mod;
            }
        }
    }
    if (!flag)
    {
        inv = qp(n, mod - 2);
        for (int i = 0; i < n; i += 1)
            (a[i] *= inv) %= mod;
    }
    return;
}
int main()
{
    scanf("%d", &len);
    len -= 1;
    for (int i = 0; i <= len; i += 1)
        scanf("%lld", &A[i]);
    invA[0] = qp(A[0], mod - 2);
    for (int i = 1; i <= len; i <<= 1)
    {
        memset(g, 0, sizeof(g));
        m += 1;
        for (int j = 0; j < i; j += 1)
            g[j] = invA[j];
        for (int j = 0; j < (i << 1); j += 1)
            f[j] = A[j];
        for (int j = 1; j < (i << 2); j += 1)
            rev[j] = ((rev[j >> 1] >> 1) | ((j & 1) << m));
        NTT(g, 1, i << 2);
        NTT(f, 1, i << 2);
        for (int j = 0; j < (i << 2); j += 1)
            g[j] = (((g[j] * g[j]) % mod) * f[j]) % mod;
        NTT(g, 0, i << 2);
        for (int j = i; j < (i << 1); j += 1)
            invA[j] = ((invA[j] << 1) % mod - g[j] + mod) % mod;
    }
    for (int i = 0; i <= len; i += 1)
        printf("%lld ", invA[i]);
    printf("\n");
    return 0;
}
