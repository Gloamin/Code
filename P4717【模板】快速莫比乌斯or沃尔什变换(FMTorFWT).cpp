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
const int N = (1 << 18) + 100, MOD = 998244353, Inv2 = 499122177;
int
    cor[2][2] = {{1, 0}, {1, 1}},
    icor[2][2] = {{1, 0}, {MOD - 1, 1}},
    cand[2][2] = {{1, 1}, {0, 1}},
    icand[2][2] = {{1, MOD - 1}, {0, 1}},
    cxor[2][2] = {{1, 1}, {1, MOD - 1}},
    icxor[2][2] = {{Inv2, Inv2}, {Inv2, MOD - Inv2}};
void FWT(int *f, int c[2][2], int n)
{
    for (int k = 2; k <= n; k <<= 1)
    {
        for (int i = 0; i < n; i += k)
        {
            for (int j = i; j < i + (k / 2); j++)
            {
                int x = f[j], y = f[j + (k / 2)];
                f[j] = ((c[0][0] * x % MOD + c[0][1] * y % MOD) % MOD + MOD) % MOD;
                f[j + (k / 2)] = ((c[1][0] * x % MOD + c[1][1] * y % MOD) % MOD + MOD) % MOD;
            }
        }
    }
}
int n, a[N], b[N], c[N], d[N];
void cpy()
{
    memcpy(c, a, sizeof(a));
    memcpy(d, b, sizeof(b));
    return;
}
void solve(int cc[2][2], int icc[2][2])
{
    cpy();
    FWT(c, cc, n);
    FWT(d, cc, n);
    for (int i = 0; i < n; i++)
        c[i] = c[i] * d[i] % MOD;
    FWT(c, icc, n);
    for (int i = 0; i < n; i++)
        printf("%lld ", c[i]);
    puts("");
}
signed main()
{
    n = Read();
    n = 1 << n;
    for (int i = 0; i < n; i++)
        a[i] = Read();
    for (int i = 0; i < n; i++)
        b[i] = Read();
    solve(cor, icor);
    solve(cand, icand);
    solve(cxor, icxor);
    return 0;
}