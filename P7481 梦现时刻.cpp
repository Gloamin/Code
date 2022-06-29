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
const int MOD = 998244353, N = 5010;
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
int n, m, fac[N], ifac[N], dp[N][N];
int C1(int x, int y)
{
    if (x < y)
        return 0;
    if (x == y || y == 0)
        return 1;
    int ans = 1;
    for (int i = x - y + 1; i <= x; i++)
        ans = ans * i % MOD;
    return ans * ifac[y] % MOD;
}
int C2(int x, int y)
{
    if (x < y)
        return 0;
    if (x == y || y == 0)
        return 1;
    return fac[x] * ifac[y] % MOD * ifac[x - y] % MOD;
}
int getf(int a, int b)
{
    int ans = 0;
    for (int i = 0; i <= b; i++)
        ans = (ans + C2(b, i)) % MOD;
    return ans;
}
signed main()
{
    n = Read();
    m = Read();
    fac[0] = 1;
    for (int i = 1; i <= m; i++)
        fac[i] = fac[i - 1] * i % MOD, ifac[i] = qpow(fac[i], MOD - 2);
    for (int i = 0; i <= m; i++)
        dp[0][i] = getf(0, i), dp[i][0] = C1(n, i);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
        {
            dp[i][j] = (2 * dp[i][j - 1] - dp[i - 1][j] + dp[i - 1][j - 1] + MOD) % MOD;
        }
    int ans = 0;
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            ans ^= dp[i][j];
    cout << ans;
    return 0;
}