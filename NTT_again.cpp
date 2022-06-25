#include <bits/stdc++.h>
#define int long long
using namespace std;
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
const int MOD = 998244353, G = 3, Gi = 332748118, N = 5e6 + 10;
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
int n, m, a[N], b[N], limit, binl, rev[N];
void NTT(int *A, int type)
{
    for (int i = 0; i < limit; i++)
        if (i < rev[i])
            swap(A[i], A[rev[i]]);
    for (int mid = 1; mid < limit; mid <<= 1)
    {
        int delt = qpow((type == 1 ? G : Gi), (MOD - 1) / (mid << 1));
        for (int j = 0; j < limit; j += (mid << 1))
        {
            int w = 1;
            for (int k = 0; k < mid; k++, w = (w * delt) % MOD)
            {
                int x = A[j + k], y = w * A[j + k + mid] % MOD;
                A[j + k] = (x + y) % MOD;
                A[j + k + mid] = (x - y + MOD) % MOD;
            }
        }
    }
}
signed main()
{
    n = Read();
    m = Read();
    for (int i = 0; i <= n; i++)
        a[i] = Read();
    for (int i = 0; i <= m; i++)
        b[i] = Read();
    limit = 1;
    binl = 0;
    while (limit <= n + m)
        limit <<= 1, binl++;
    for (int i = 0; i < limit; i++)
        rev[i] = (rev[i >> 1] >> 1) | (i & 1) << (binl - 1);
    NTT(a, 1);
    NTT(b, 1);
    for (int i = 0; i < limit; i++)
        a[i] = a[i] * b[i] % MOD;
    NTT(a, -1);
    int inv = qpow(limit, MOD - 2);
    for (int i = 0; i <= n + m; i++)
        printf("%lld ", a[i] * inv % MOD);
    return 0;
}