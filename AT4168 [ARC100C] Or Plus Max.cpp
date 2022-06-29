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
const int N = 20;
struct Node
{
    int max1, max2;
    Node operator+(Node y)
    {
        Node res;
        if (y.max1 > max1)
        {
            res.max1 = y.max1;
            res.max2 = max(y.max2, max1);
        }
        else
        {
            res.max1 = max1;
            res.max2 = max(y.max1, max2);
        }
        return res;
    }
} a[1 << N];
int n;
int main()
{
    n = Read();
    int nn = 1 << n;
    for (int i = 0; i < nn; i++)
    {
        a[i].max1 = Read();
        a[i].max2 = INT_MIN;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j < nn; j++)
            if ((j >> i) & 1)
                a[j] = a[j] + a[j ^ (1 << i)];
    int ans = 0;
    for (int j = 1; j < nn; j++)
        ans = max(ans, a[j].max1 + a[j].max2), printf("%d\n", ans);
    return 0;
}