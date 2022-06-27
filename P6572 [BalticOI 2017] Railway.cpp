#include <bits/stdc++.h>
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
int n, m, k;
vector<pair<int, int>> g[100010];
vector<int> id[100010];
int f[100010][32], dfsxu[100010], dep[100010];
int cnt, diff[100010], toe[100010];
void dfs(int cur, int fa)
{
    dfsxu[cur] = ++cnt;
    f[cur][0] = fa;
    dep[cur] = dep[fa] + 1;
    for (int i = 1; (1 << i) <= dep[cur]; i++)
        f[cur][i] = f[f[cur][i - 1]][i - 1];
    for (int i = 0; i < g[cur].size(); i++)
    {
        int to = g[cur][i].second;
        if (to == fa)
            continue;
        dfs(to, cur);
        toe[to] = g[cur][i].first;
    }
}
int lca(int x, int y)
{
    if (dep[x] > dep[y])
        swap(x, y);
    for (int i = 30; i >= 0; i--)
    {
        if (dep[f[y][i]] >= dep[x])
            y = f[y][i];
    }
    if (x == y)
        return x;
    for (int i = 30; i >= 0; i--)
    {
        if (f[x][i] != f[y][i])
            x = f[x][i], y = f[y][i];
    }
    return f[x][0];
}
bool cmp(int x, int y)
{
    return dfsxu[x] < dfsxu[y];
}
bool cmp2(int x, int y)
{
    return toe[x] < toe[y];
}
void Calcans(int cur, int fa)
{
    for (int i = 0; i < g[cur].size(); i++)
    {
        int to = g[cur][i].second;
        if (to == fa)
            continue;
        Calcans(to, cur);
        diff[cur] += diff[to];
    }
}
int main()
{
#ifdef LOCAL
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif
    n = Read();
    m = Read();
    k = Read();
    for (int i = 1; i < n; i++)
    {
        int x = Read(), y = Read();
        g[x].push_back(make_pair(i, y));
        g[y].push_back(make_pair(i, x));
    }
    dfs(1, 0);
    vector<int> vec;
    for (int i = 1; i <= m; i++)
    {
        int x = Read();
        vec.clear();
        for (int j = 1; j <= x; j++)
            vec.push_back(Read());
        sort(vec.begin(), vec.end(), cmp);
        for (int j = 0; j < x - 1; j++)
        {
            int xx = vec[j], y = vec[j + 1], l = lca(xx, y);
            diff[xx] += 1;
            diff[y] += 1;
            diff[l] -= 2;
        }
        int xx = vec[vec.size() - 1], y = vec[0], l = lca(xx, y);
        diff[xx] += 1;
        diff[y] += 1;
        diff[l] -= 2;
    }
    Calcans(1, 0);
    vec.clear();
    for (int i = 2; i <= n; i++)
    {
        if (diff[i] >= 2 * k)
            vec.push_back(i);
    }
    printf("%d\n", vec.size());
    sort(vec.begin(), vec.end(), cmp2);
    for (auto i : vec)
        printf("%d ", toe[i]);
    return 0;
}