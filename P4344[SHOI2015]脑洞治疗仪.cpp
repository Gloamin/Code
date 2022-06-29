#include <bits/stdc++.h>
#define lson ind << 1
#define rson ind << 1 | 1
using namespace std;

inline int read()
{
    int x = 0, f = 1;
    char ch = getchar();
    for (; ch > '9' || ch < '0'; ch = getchar())
        if (ch == '-')
            f = -1;
    for (; ch <= '9' && ch >= '0'; ch = getchar())
        x = (x << 1) + (x << 3) + (ch ^ '0');
    return x * f;
}

int n, m, tp, l0, r0, l1, r1;

struct segtree
{
    int l, r, tot, pre, suf, tag, mx;
} tr[2000005];

inline void add(int ind, int x)
{
    tr[ind].tag = x;
    if (x == 0)
    {
        tr[ind].tot = 0;
        tr[ind].pre = tr[ind].suf = tr[ind].mx = (tr[ind].r - tr[ind].l + 1);
    }
    else
    {
        tr[ind].tot = (tr[ind].r - tr[ind].l + 1);
        tr[ind].pre = tr[ind].suf = tr[ind].mx = 0;
    }
}

inline void pushup(int ind)
{
    tr[ind].tot = tr[lson].tot + tr[rson].tot;
    tr[ind].pre = tr[lson].pre;
    tr[ind].suf = tr[rson].suf;
    if (tr[lson].pre == tr[lson].r - tr[lson].l + 1)
        tr[ind].pre += tr[rson].pre;
    if (tr[rson].suf == tr[rson].r - tr[rson].l + 1)
        tr[ind].suf += tr[lson].suf;
    tr[ind].mx = max(max(tr[lson].mx, tr[rson].mx), tr[lson].suf + tr[rson].pre);
}

void build(int ind, int l, int r)
{
    tr[ind].l = l;
    tr[ind].r = r;
    tr[ind].tag = -1;
    if (l == r)
    {
        tr[ind].tot = 1;
        return;
    }
    int mid = (l + r) >> 1;
    build(lson, l, mid);
    build(rson, mid + 1, r);
    pushup(ind);
}

inline void pushdown(int ind)
{
    if (tr[ind].tag == 0)
    {
        add(lson, 0);
        add(rson, 0);
    }
    else if (tr[ind].tag == 1)
    {
        add(lson, 1);
        add(rson, 1);
    }
    tr[ind].tag = -1;
}

void update1(int ind, int x, int y)
{
    int l = tr[ind].l, r = tr[ind].r;
    if (x <= l && r <= y)
    {
        add(ind, 0);
        return;
    }
    int mid = (l + r) >> 1;
    pushdown(ind);
    if (x <= mid)
        update1(lson, x, y);
    if (mid < y)
        update1(rson, x, y);
    pushup(ind);
}

int update2(int ind, int x, int y, int num)
{
    if (!num)
        return 0;
    int l = tr[ind].l, r = tr[ind].r;
    if (x <= l && r <= y && num >= r - l + 1 - tr[ind].tot)
    {
        int ret = num - (r - l + 1 - tr[ind].tot);
        add(ind, 1);
        return ret;
    }
    int mid = (l + r) >> 1;
    pushdown(ind);
    if (x <= mid)
        num = update2(lson, x, y, num);
    if (mid < y)
        num = update2(rson, x, y, num);
    pushup(ind);
    return num;
}

int query1(int ind, int x, int y)
{
    int l = tr[ind].l, r = tr[ind].r;
    if (x <= l && r <= y)
    {
        return tr[ind].tot;
    }
    int mid = (l + r) >> 1, ret = 0;
    pushdown(ind);
    if (x <= mid)
        ret += query1(lson, x, y);
    if (mid < y)
        ret += query1(rson, x, y);
    return ret;
}

segtree merge(segtree a, segtree b)
{
    segtree ret;
    ret.l = a.l;
    ret.r = b.r;
    ret.tot = a.tot + b.tot;
    ret.pre = a.pre;
    ret.suf = b.suf;
    if (a.pre == a.r - a.l + 1)
        ret.pre += b.pre;
    if (b.suf == b.r - b.l + 1)
        ret.suf += a.suf;
    ret.mx = max(max(a.mx, b.mx), a.suf + b.pre);
    return ret;
}

segtree query2(int ind, int x, int y)
{
    int l = tr[ind].l, r = tr[ind].r;
    if (x <= l && r <= y)
        return tr[ind];
    int mid = (l + r) >> 1;
    segtree a, b;
    a.mx = b.mx = -1;
    pushdown(ind);
    if (x <= mid)
        a = query2(lson, x, y);
    if (mid < y)
        b = query2(rson, x, y);
    if (a.mx == -1)
        return b;
    else if (b.mx == -1)
        return a;
    else
        return merge(a, b);
}

int main()
{
#ifdef LOCAL
#undef LOCAL
    freopen("sample.in", "r", stdin);
    freopen("sample.out", "w", stdout);
#endif
    n = read();
    m = read();
    build(1, 1, n);
    for (int i = 1; i <= m; i++)
    {
        tp = read();
        if (tp == 0)
        {
            l0 = read();
            r0 = read();
            update1(1, l0, r0);
        }
        else if (tp == 1)
        {
            l0 = read();
            r0 = read();
            l1 = read();
            r1 = read();
            int num = query1(1, l0, r0);
            update1(1, l0, r0);
            update2(1, l1, r1, num);
        }
        else
        {
            l0 = read();
            r0 = read();
            segtree ans = query2(1, l0, r0);
            printf("%d\n", ans.mx);
        }
    }
    return 0;
}