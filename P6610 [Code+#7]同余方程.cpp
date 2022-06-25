#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e7 + 5;
typedef long long ll;
void read(int &x)
{
    x = 0;
    int f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -f;
    for (; isdigit(c); c = getchar())
        x = x * 10 + c - '0';
    x *= f;
}
int tot, prime[MAXN], f[MAXN], g[MAXN];
ll func[MAXN];
void sieve(int n)
{
    func[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        if (f[i] == 0)
        {
            prime[++tot] = f[i] = g[i] = i;
            for (ll j = i, e = 1; j <= n; j *= i, e++)
            {
                if (i == 2)
                    func[j] = j;
                else if (i % 4 == 3)
                {
                    if (e % 2)
                        func[j] = j / i;
                    else
                        func[j] = j;
                }
                else
                    func[j] = j / i * ((i - 1) * e + i);
            }
        }
        for (int j = 1; j <= tot && prime[j] <= f[i]; j++)
        {
            int tmp = prime[j] * i;
            if (tmp > n)
                break;
            f[tmp] = prime[j];
            if (prime[j] != f[i])
            {
                g[tmp] = prime[j];
                func[tmp] = func[g[tmp]] * func[tmp / g[tmp]];
            }
            else
                g[tmp] = g[i] * f[i];
        }
    }
}
int main()
{
    int T;
    read(T);
    sieve(1e7);
    while (T--)
    {
        int n, x;
        ll ans = 1;
        read(n), read(x);
        while (n != 1)
        {
            int p = f[n], e = 0, v = 1;
            while (f[n] == p)
                n /= p, v *= p, e++;
            int k = x % v;
            if (k == 0)
                ans = ans * func[v];
            else
            {
                int r = k, b = 0;
                while (r % p == 0)
                    r /= p, b++;
                if (p % 4 == 1)
                    ans *= 1ll * v / p * (b + 1) * (p - 1);
                else if (p % 4 == 3)
                {
                    if (b % 2 == 0)
                        ans *= 1ll * v / p * (p + 1);
                    else
                        ans = 0;
                }
                else
                {
                    if (b == e - 1)
                        ans *= 1ll * v;
                    else if (r % 4 == 1)
                        ans *= 2ll * v;
                    else
                        ans *= 0;
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}