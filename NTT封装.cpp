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
const int MOD = 998244353, G = 3, Gi = 332748118;
void Prework(int &lim, int &binl, int n, int m)
{
    lim = 1;
    binl = 0;
    while (lim <= n + m)
        lim <<= 1, binl++;
}
void Rev(int lim, int binl, int *rev)
{
    for (int i = 0; i < lim; i++)
        rev[i] = ((rev[i >> 1] >> 1)) | (i & 1) << (binl - 1);
}
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
void NTT(int *A, int *rev, int lim, int type)
{
    for (int i = 0; i < lim; i++)
        if (i < rev[i])
            swap(A[i], A[rev[i]]);
    for (int mid = 1; mid < lim; mid <<= 1)
    {
        int delt = qpow((type == 1 ? G : Gi), (MOD - 1) / (mid << 1));
        // cout << "AAA";
        for (int j = 0; j < lim; j += (mid << 1))
        {
            int w = 1;
            for (int k = 0; k < mid; k++, w = (w * delt) % MOD)
            {
                int x = A[j + k], y = w * A[j + k + mid] % MOD;
                A[j + k] = (x + y) % MOD;
                A[j + k + mid] = (x - y + MOD) % MOD;
            }
        }
    }
}
void Mul(int *A, int *B, int *rev, int n, int m)
{
    memset(rev, 0, sizeof rev);
    int lim, binl;
    Prework(lim, binl, n, m);
    Rev(lim, binl, rev);
    // cout << "AAA";
    NTT(A, rev, lim, 1), NTT(B, rev, lim, 1);
    for (int i = 0; i < lim; i++)
        A[i] = A[i] * B[i] % MOD;
    // cout << "AAA";
    NTT(A, rev, lim, -1);
    int inv = qpow(lim, MOD - 2);
    for (int i = 0; i <= n + m; i++)
        A[i] = A[i] * inv % MOD;
}
int a[5000010], b[5000010], rev[5000010], n, m;
signed main()
{
    n = Read();
    m = Read();
    for (int i = 0; i <= n; i++)
        a[i] = Read();
    for (int i = 0; i <= m; i++)
        b[i] = Read();
    // cout << "AAA";
    Mul(a, b, rev, n, m);
    for (int i = 0; i <= n + m; i++)
        printf("%lld ", a[i]);
    return 0;
}