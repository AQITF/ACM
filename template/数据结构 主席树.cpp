/*��ϯ��*/
/*
һ���÷� ������
�������Ӷ�
1���ռ䣺O��nlogn��
2��ʱ�䣺
��1�����£�O��nlogn��
��2����ѯ��O��nlogn��
*/
/*��̬�����K�� POJ2104*/
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 10;
int a[MAXN], b[MAXN], n, m, q;
int rt[MAXN], lson[MAXN << 5], rson[MAXN << 5], sum[MAXN << 5], tot;/*ע�������С*/
/*��ɢ��*/
void initHash()
{
    copy(a + 1, a + 1 + n, b + 1);
    sort(a + 1, a + 1 + n);
    m = unique(a + 1, a + 1 + n) - (a + 1);
}
/*rt�����ô���*/
void build(int l, int r, int& rt)
{
    rt = ++tot;
    sum[rt] = 0;

    if(l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, lson[rt]);
    build(mid + 1, r, rson[rt]);
}
/*nowRoot�����ô���*/
void update(int& nowRoot, int lastRoot, int l, int r, int pos)
{
    nowRoot = ++tot;
    sum[nowRoot] = sum[lastRoot] + 1;/*�̳���һ����*/
    if(l == r) return;
    int mid = (l + r) >> 1;
    if(pos <= mid)
    {
        /*����ֻ���������Ҫ�½��� �Ҷ���ֱ�Ӽ̳���һ����*/
        update(lson[nowRoot], lson[lastRoot], l, mid, pos);
        rson[nowRoot] = rson[lastRoot];
    }
    else
    {
        update(rson[nowRoot], rson[lastRoot], mid + 1, r, pos);
        lson[nowRoot] = lson[lastRoot];
    }
}
int query(int L, int R, int l, int r, int k)
{
    if(l == r) return l;
    int mid = (l + r) >> 1;
    /*amt�����ڲ�ѯ���䣨���������Եģ��ڣ� ��ʱ��ڵ�����[l, mid]ֵ����������ֵĸ���*/
    int amt = sum[lson[R]] - sum[lson[L]];
    if(k <= amt)
    {
        return query(lson[L], lson[R], l, mid, k);
    }
    else
    {
        return query(rson[L], rson[R], mid + 1, r, k - amt);
    }
}
void solve()
{
    initHash();
    build(1, m, rt[0]);
    for(int i = 1; i <= n; i++)
    {
        int pos = lower_bound(a + 1, a + 1 + m, b[i]) - a;
        update(rt[i], rt[i - 1], 1, m, pos);
    }
    while(q--)
    {
        int l, r, k; scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", a[query(rt[l - 1], rt[r], 1, m, k)]);
    }
}
int main()
{
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    solve();
	return 0;
}

/*���޸ģ���ѯ������ٸ���ͬ���� SPOJ DQUERY*/
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e4 + 10;
int n, q;

int a[MAXN];
int tot, root[MAXN], lson[MAXN << 5], rson[MAXN << 5], sum[MAXN << 5], vis[1000000 + 10];
void build(int l ,int r, int& rt)
{
    rt = ++tot;
    sum[rt] = 0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(l, mid, lson[rt]);
    build(mid + 1, r, rson[rt]);
}
void pushUp(int rt)
{
    sum[rt] = sum[lson[rt]] + sum[rson[rt]];
}
void update(int pos, int val, int l, int r, int& rt, int last)
{
    rt = ++tot;
    if(l == r)
    {
        sum[rt] = sum[last] + val;
        return;
    }
    int mid = (l + r) >> 1;
    if(pos <= mid)
    {
        update(pos, val, l, mid, lson[rt], lson[last]);
        rson[rt] = rson[last];
    }
    else
    {
        update(pos, val, mid + 1, r, rson[rt], rson[last]);
        lson[rt] = lson[last];
    }
    pushUp(rt);
}
int query(int L, int R, int l, int r, int rt)
{
    if(L <= l && r <= R)
    {
        return sum[rt];
    }
    int ans = 0;
    int mid = (l + r) >> 1;
    if(L <= mid) ans += query(L, R, l, mid, lson[rt]);
    if(R > mid) ans += query(L, R, mid + 1, r, rson[rt]);
    return ans;
}
int main()
{
    scanf("%d", &n);
    for(int i = 1; i <= n; i++)
    {
        scanf("%d", &a[i]);
    }
    build(1, n, root[0]);
    for(int i = 1; i <= n; i++)
    {
        if(vis[a[i]])
        {
            update(i, 1, 1, n, root[i], root[i - 1]);
            update(vis[a[i]], -1, 1, n, root[i], root[i]);
            vis[a[i]] = i;
        }
        else
        {
            update(i, 1, 1, n, root[i], root[i - 1]);
            vis[a[i]] = i;
        }

    }

    scanf("%d", &q);
    while(q--)
    {
        int l, r; scanf("%d%d", &l, &r);
        printf("%d\n", query(l, r, 1, n, root[r]));
    }
}

