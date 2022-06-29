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
const int N = 2000 + 5;
int n, k, a[N], b[N], l[N], dp[N][N], fac[N], ifac[N], g[N];
int C(int n, int m)
{
	return 1ll * fac[n] * ifac[m] % MOD * ifac[n - m] % MOD;
}
signed main()
{
	n=Read();k=Read();
	if ((n + k) & 1)
	{
		puts("0");
		return 0;
	}
	k = (n + k) / 2;
	ifac[0] = ifac[1] = fac[0] = fac[1] = 1;
	for (int i = 2; i < N; i++)
		ifac[i] = -1ll * MOD / i * ifac[MOD % i] % MOD;
	for (int i = 2; i < N; i++)
		fac[i] = 1ll * fac[i - 1] * i % MOD, ifac[i] = 1ll * ifac[i - 1] * ifac[i] % MOD;
	for (int i = 1; i <= n; i++)
		a[i]=Read();
	for (int i = 1; i <= n; i++)
		b[i]=Read();
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	int loc = 0;
	for (int i = 1; i <= n; i++)
	{
		while (loc < n && b[loc + 1] < a[i])
			++loc;
		l[i] = loc;
	}
	dp[0][0] = 1;
	for (int i = 1; i <= n; i++)
	{
		dp[i][0] = dp[i - 1][0];
		for (int j = 1; j <= i; j++)
			dp[i][j] = (1ll * dp[i - 1][j] + 1ll * dp[i - 1][j - 1] * max(0LL, l[i] - j + 1) % MOD) % MOD;
	}
	for (int i = 0; i <= n; i++)
		g[i] = 1ll * dp[n][i] * fac[n - i] % MOD;
	int ans = 0;
	for (int i = k; i <= n; i++)
		if ((i - k) & 1)
			(ans -= 1ll * C(i, k) * g[i] % MOD) %= MOD;
	else
		(ans += 1ll * C(i, k) * g[i] % MOD) %= MOD;
	printf("%lld\n", (ans + MOD) % MOD);
}
