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
const int N = 2e6 + 1009;
const int mod = 998244353;
int n, m, sg[N], A[N], B[N];
int Pow(int a, int p)
{
    int ans = 1;
    for (; p; p >>= 1, a = a * a % mod)
        if (p & 1)
            ans = ans * a % mod;
    return ans % mod;
}
void FWT(int *A, int n, int type)
{
    int inv_2 = Pow(2, mod - 2);
    for (int m = 1; m < n; m <<= 1)
    {
        for (int i = 0; i < n; i += 2 * m)
        {
            for (int j = 0; j < m; j++)
            {
                int x = A[i + j], y = A[i + j + m];
                A[i + j] = (1ll * x + y) * (type == 1 ? 1 : inv_2) % mod;
                A[i + j + m] = (1ll * x - y + mod) * (type == 1 ? 1 : inv_2) % mod;
            }
        }
    }
}
void Arrtimes(int *A, int lim, int *B)
{
    for (int i = 0; i < lim; i++)
        A[i] = A[i] * B[i] % mod;
}
void FWTPow(int *A, int p, int *B, int lim)
{
    for (int i = 0; i < lim; i++)
        B[i] = 1;
    FWT(A, lim, 1);
    for (; p; p >>= 1, Arrtimes(A, lim, A))
        if (p & 1)
            Arrtimes(B, lim, A);
    FWT(B, lim, -1);
}
signed main()
{
    n = Read();
    m = Read();
    for (int i = 0; i <= m; i++)
        sg[i] = i - (1 << (32 - __builtin_clz(i) - 1)) + 1;
    for (int i = 1; i <= m; i++)
        A[sg[i]]++;
    int lim = 1;
    while (lim <= m)
        lim <<= 1;
    FWTPow(A, n, B, lim);
    // printf("%lld\n", B[0]);
    printf("%lld\n", (Pow(m, n) - B[0] + mod) % mod);
    return 0;
}