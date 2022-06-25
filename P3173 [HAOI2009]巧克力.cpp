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
const int N = 1e4 + 10;
priority_queue<pair<int, int>> vec;
int n, m;
signed main()
{
    n = Read();
    m = Read();
    for (int i = 1; i < n; i++)
    {
        int x = Read();
        vec.push(make_pair(x, 1));
    }
    for (int i = 1; i < m; i++)
    {
        int x = Read();
        vec.push(make_pair(x, 2));
    }
    int s[3];
    s[1] = s[2] = 1;
    int ans = 0;
    while (!vec.empty())
    {
        auto cur = vec.top();
        vec.pop();
        s[3-cur.second]++;
        ans += cur.first * s[cur.second];
        // printf("%d %d %d\n", cur.first, cur.second, s[3-cur.second]);
    }
    printf("%d", ans);
    return 0;
}