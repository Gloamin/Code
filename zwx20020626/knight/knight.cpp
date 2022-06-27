#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N = 2e5+10;
int n, w[N], dis[N];
vector<int> son[N], fa[N];
bool vis[N];
queue<int> q;
void SPFA()
{
	for (int i = 1; i <= n; ++i)
		q.push(i), vis[i] = 1;
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		vis[cur] = 0;
		int val = w[cur];
		for (int i = 0; i < son[cur].size(); i++)
			val += dis[son[cur][i]];
		if (val >= dis[cur])
			continue;
		dis[cur] = val;
		for (int i = 0; i < fa[cur].size(); i++)
		{
			if (!vis[fa[cur][i]])
			{
				vis[fa[cur][i]] = 1;
				q.push(fa[cur][i]);
			}
		}
	}
}
signed main()
{
	freopen("knight.in", "r", stdin);
	freopen("knight.out", "w", stdout);
	scanf("%lld", &n);
	for (int i = 1; i <= n; i++)
	{
		int x, t;
		scanf("%lld%lld%lld", &w[i], &dis[i], &x);
		for(int j = 1; j <= x; j++)
		{
			scanf("%lld", &t);
			son[i].push_back(t);
			fa[t].push_back(i);
		}
	}
	SPFA();
	printf("%lld", dis[1]);
	return 0;
}
