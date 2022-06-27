#include <bits/stdc++.h>
#define db double
#define il inline
#define re 
#define ll long long
#define ui unsigned int
#define ull unsigned ll
#define fi first
#define se second
#define pll pair<ll, ll>
#define pil pair<int, ll>
#define pli pair<ll, int>
#define pii pair<int, int>
#define MP(x, y) make_pair(x, y)
#define lowbit(x) ((x) & (~(x) + 1))
#define INF 0x3f3f3f3f
using namespace std;
#define MaxSize 20
char buf[1 << MaxSize], *p1, *p2;
#define GetChar() ((p1 == p2) ? (p2 = buf + fread(p1 = buf, 1, 1 << MaxSize, stdin), p1 == p2 ? EOF : *p1++) : *p1++)
template <class T>
inline void Read(T &x)
{
    x = 0;
    re bool f = 0;
    re char c = GetChar();
    while (c < 47 || c > 58)
        f |= (c == '-'), c = GetChar();
    while (c > 46 && c < 59)
        x = (x << 3) + (x << 1) + (c & 15), c = GetChar();
    x = f ? (~x + 1) : x;
}
int T, n;
struct Node
{
    int x, y;
} a[2010];
bool cmp(Node x, Node y)
{
    return x.y < y.y || x.y == y.y && x.x < y.x;
}
int f[2010];
int main()
{
    // freopen("sample.in","r",stdin);
    for (scanf("%d\n", &T); T--;)
    {
        scanf("%d\n", &n);
        memset(f, 0, sizeof(f));
        for (int i = 1; i <= n; i++)
        {
            scanf("%d-%d\n", &a[i].x, &a[i].y);
            // cout<<a[i].x<<' '<<a[i].y<<endl;
            if (a[i].x > a[i].y)
                swap(a[i].x, a[i].y);
        }
        sort(a + 1, a + 1 + n, cmp);
        // for(int i=1;i<=n;i++) cout<<a[i].x<<' '<<a[i].y<<endl;
        int tot = 0;
        f[++tot] = a[1].x;
        for (int i = 2; i <= n; i++)
        {
            int lst = 0;
            for (int j = 1; j <= tot; j++)
                if (a[i].x >= f[j] && f[lst] <= f[j])
                    lst = j;
            if (lst == 0)
                f[++tot] = a[i].x;
            else
                f[lst] = a[i].x;
        }
        printf("%d\n", tot);
    }
}