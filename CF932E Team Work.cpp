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
const int MOD = 1e9 + 7, N = 5050;
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
int S[N][N], n, k, ans;
void Stirling()
{
    S[0][0] = 1;
    for (int i = 1; i <= k; i++)
        for (int j = 1; j <= i; j++)
        {
            S[i][j] = (S[i - 1][j - 1] + j * S[i - 1][j] % MOD) % MOD;
        }
}
signed main()
{
    n = Read();
    k = Read();
    Stirling();
    for (int i = 1; i <= n && i <= k; i++)
    {
        int tmp = S[k][i] * qpow(2, n - i) % MOD;
        for (int j = n - i + 1; j <= n; j++)
            tmp = tmp * j % MOD;
        ans = (ans + tmp) % MOD;
    }
    cout << ans;
    return 0;
}