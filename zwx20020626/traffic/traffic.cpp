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
int n, m, K, e, dis[25][25], f[25][25];
int d, canrun[25][110]; // point,day
bool chk(int pnt, int l, int r)
{
    for (int i = l; i <= r; i++)
        if (canrun[pnt][i])
            return 1;
    return 0;
}
bool cn[105];
int getmindis(int l, int r)
{
    for (int i = 1; i <= m; i++)
    {
        cn[i] = 0;
        for (int j = l; j <= r; j++)
            if (canrun[i][j])
            {
                cn[i] = 1;
                break;
            }
    }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            f[i][j] = dis[i][j];
    for (int k = 1; k <= m; k++)
    {
        if (cn[k])
            continue;
        for (int i = 1; i <= m; i++)
        {
            if (cn[i])
                continue;
            for (int j = 1; j <= m; j++)
            {
                if (cn[j])
                    continue;
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
            }
        }
    }
    return f[1][m];
}
int dp[105], mindis[105][105];
signed main()
{
    freopen("traffic.in", "r", stdin);
    freopen("traffic.out", "w", stdout);
    n = Read();
    m = Read();
    K = Read();
    e = Read();
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m; j++)
            dis[i][j] = INT_MAX;
    for (int i = 1; i <= e; i++)
    {
        int x = Read(), y = Read(), z = Read();
        dis[x][y] = dis[y][x] = z;
    }
    d = Read();
    for (int i = 1; i <= d; i++)
    {
        int p = Read(), a = Read(), b = Read();
        canrun[p][a]++;
        canrun[p][b + 1]--;
    }
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= n; j++)
            canrun[i][j] += canrun[i][j - 1];
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            mindis[i][j] = getmindis(i, j);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        dp[i] = mindis[1][i] * i;
        for (int j = i - 1; j >= 0; j--)
        {
            dp[i] = min(dp[i], dp[j] + mindis[j + 1][i] * (i - j) + K);
        }
    }
    cout << dp[n];
    return 0;
}