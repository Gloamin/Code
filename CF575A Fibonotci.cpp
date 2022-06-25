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
int P;
struct Matrix
{
    int a[3][3];
    Matrix()
    {
        memset(a, 0, sizeof a);
    }
};
Matrix operator*(Matrix x, Matrix y)
{
    Matrix res;
    res.a[1][1] = (x.a[1][1] * y.a[1][1] % P + x.a[1][2] * y.a[2][1] % P) % P;
    res.a[1][2] = (x.a[1][1] * y.a[1][2] % P + x.a[1][2] * y.a[2][2] % P) % P;
    res.a[2][1] = (x.a[2][1] * y.a[1][1] % P + x.a[2][2] * y.a[2][1] % P) % P;
    res.a[2][2] = (x.a[2][1] * y.a[1][2] % P + x.a[2][2] * y.a[2][2] % P) % P;
    return res;
}


int main()
{
    return 0;
}