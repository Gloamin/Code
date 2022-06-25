// with NTT
#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;
const int MOD = 998244353, G = 3, Gi = 332748118;
const int N = 5e6 + 10;
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
ll qpow(ll a, ll b)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % MOD;
        a = a * a % MOD;
        b >>= 1;
    }
    return res;
}
ll a[N], b[N], n, m, resl, binl, cc[N];
ll rev[N];
void NTT(ll *A, int opt)
{
    for (int i = 0; i < resl; i++)
        if (i < rev[i])
            swap(A[i], A[rev[i]]);
    for (int mid = 1; mid < resl; mid <<= 1)
    {
        ll Wn = qpow(opt == 1 ? G : Gi, (MOD - 1) / (mid << 1));
        for (int j = 0; j < resl; j += (mid << 1))
        {
            ll w = 1;
            for (int k = 0; k < mid; k++, w = (w * Wn) % MOD)
            {
                int x = A[j + k], y = w * A[j + k + mid] % MOD;
                A[j + k] = (x + y) % MOD;
                A[j + k + mid] = (x - y + MOD) % MOD;
            }
        }
    }
}
char ch[N];
vector<int> vec;
signed main()
{
    scanf("%s", ch);
    n = strlen(ch);
    for (int i = 0; i < n; i++)
    {
        a[i] = ch[n - i - 1] - '0';
    }
    scanf("%s", ch);
    m = strlen(ch);
    for (int i = 0; i < m; i++)
    {
        b[i] = ch[m - i - 1] - '0';
    }
    // for (int i = 0; i < n; i++)
    //     cout << a[i];
    // cout << endl;
    // for (int i = 0; i < m; i++)
    //     cout << b[i];
    // cout<<endl;
    resl = 1;
    while (resl <= n + m)
        resl <<= 1, binl++;
    for (int i = 0; i < resl; i++)
        rev[i] = (rev[i >> 1] >> 1) | (i & 1) << (binl - 1);
    NTT(a, 1);
    NTT(b, 1);
    for (int i = 0; i < resl; i++)
        a[i] = a[i] * b[i] % MOD;
    NTT(a, -1);
    int inv = qpow(resl, MOD - 2);
    for (int i = 0; i <= n + m; i++)
        cc[i] = a[i] * inv % MOD;
    for (int i = 0; i <= n + m; i++)
    {
        if (cc[i] >= 10)
        {
            cc[i + 1] += cc[i] / 10;
            cc[i] %= 10;
        }
    }
    int pp = n + m - 1;
    while (cc[pp] == 0)
        pp--;
    for (int i = pp; i >= 0; i--)
    {
        printf("%d", cc[i]);
    }
    return 0;
}