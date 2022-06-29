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
const int MOD = 1e9 + 9;
int cnt1(int x)
{
    return __builtin_popcount(x);
}
void orFWT(int a[], int limit, int type)
{
    for (int i = 1; i < limit; i <<= 1)
    {
        for (int j = 0; j < limit; j += (i << 1))
        {
            for (int k = 0; k < i; k++)
            {
                a[i + j + k] = ((a[i + j + k] + a[j + k] * type) % MOD + MOD) % MOD;
            }
        }
    }
}
int n, f[21][1048576], g[21][1048576], h[21][1048576];
signed main()
{
    n = Read();
    int nn = (1 << n);
    for (int i = 0; i < nn; i++)
        f[cnt1(i)][i] = Read();
    for (int i = 0; i < nn; i++)
        g[cnt1(i)][i] = Read();
    for (int i = 0; i <= n; i++)
    {
        orFWT(f[i], nn, 1);
        orFWT(g[i], nn, 1);
    }
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j + i <= n; j++)
        {
            for (int s = 0; s < nn; s++)
            {
                h[i + j][s] = (h[i + j][s] + f[i][s] * g[j][s] % MOD) % MOD;
            }
        }
    }
    for (int i = 0; i <= n; i++)
        orFWT(h[i], nn, -1);
    for (int i = 0; i < nn - 1; i++)
    {
        printf("%lld ", h[cnt1(i)][i]);
    }
    printf("%lld\n", h[n][nn - 1]);
    return 0;
}