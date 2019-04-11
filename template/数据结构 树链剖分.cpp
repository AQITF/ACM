//��Ȩ
//���ڵ�Ȩ����ѯ����ֵ���޸�·�����ϵĵ�Ȩ��HDU 3966 �����ʷ�+ ��״���飩
const int MAXN = 50010;
struct Edge
{
    int to, nxt;
}edge[MAXN * 2];
int head[MAXN], tot;
int top[MAXN];//v ���ڵ������Ķ��˽ڵ�
int fa[MAXN];//���׽ڵ�
int dep[MAXN];//���
int sz[MAXN];//�� v Ϊ���������Ľڵ���
int p[MAXN];//p[v] ��ʾ v ��Ӧ��λ��
int fp[MAXN];//fp �� p �����෴
int son[MAXN];//�ض���
int pos;//��״�����ָ��
void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    pos = 1;//ʹ����״���飬��Ŵ�ͷ 1 ��ʼ
    memset(son, -1, sizeof(son));
}
void addEdge(int u, int v)
{
    edge[tot].to = v;
    edge[tot].nxt = head[u];
    head[u] = tot++;
}
void dfs1(int u, int pre, int d)
{
    dep[u] = d;
    fa[u] = pre;
    sz[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v != pre)
        {
            dfs1(v, u, d + 1);
            sz[u] += sz[v];
            if(son[u] == -1 || sz[v] > sz[son[u]])
            {
                son[u] = v;
            }
        }
    }
}
void getPos(int u, int sp)
{
    // sp �������������ͷ���
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if(son[u] == -1) return;
    // �ȴ������ر�
    getPos(son[u], sp);
    // �ٴ������
    for(int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
        {
            getPos(v, v);
        }
    }
}
int lowbit(int x)
{
    return x & (-x);
}
int c[MAXN];
int a[MAXN];
int n, m, p;
int sum(int i)
{
    int res = 0;
    while(i > 0)
    {
        res += c[i];
        i -= lowbit(i);
    }
    return res;
}
void add(int i, int val)
{
    while(i <= n)
    {
        c[i] += val;
        i += lowbit(i);
    }
}
//u - > v ��·���ϵ��ֵ�ı� val
void change(int u, int v, int val)
{
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1, f2);
            swap(u, v);
        }
        add(p[f1], val);
        add(p[u] + 1, -val);
        u = fa[f1];
        f1 = top[u];
    }
    if(dep[u] > dep[v]) swap(u, v);//��ʱ v ����ȸ�� pos������
    add[p[u], val);
    add(p[v] + 1, -val);
}
void solve()
{
    int c1, c2, k;
    char op[10];
    dfs1(1, 0, 0);
    getPos(1, 1);
    memset(c, 0, sizeof(c));
    for(int i = 1; i <= n; i++)
    {
        add(p[i], a[i]);
        add(p[i] + 1, -a[i]);
    }
    while(p--)
    {
        scanf("%s", op);
        if(op[0] == 'Q')
        {
            scanf("%d", &u);
            printf("%d\n", sum[p[u]]);
        }
        else
        {
            scanf("%d%d%d", &c1, &c2, &k);
            if(op[0] == 'D')
            {
                k = -k;
            }
            change(c1, c2, k);
        }
    }
}
int main()
{
    while(~scanf("%d%d%d", &n, &m, &p))
    {
        int u, v;
        init();
        for(int i = 1; i <= n; i++)
        {
            scanf("%d", &a[i]);
        }
        for(int i = 1; i <= m; i++)
        {
            scanf("%d%d", &u, &v);
            addEdge(u, v);
            addEdge(v, u);
        }
        solve();
    }
}


//��Ȩ
//���ڱ�Ȩ���޸ĵ�����Ȩ����ѯ·����Ȩ���ֵ��SPOJ QTREE �����ʷ�+ �߶�����
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 10010;
struct Edge
{
    int to, nxt;
}edge[MAXN * 2];
int head[MAXN], tot;
int top[MAXN];//v ���ڵ������Ķ��˽ڵ�
int fa[MAXN];//���׽ڵ�
int dep[MAXN];//���
int sz[MAXN];//�� v Ϊ���������Ľڵ���
int p[MAXN];//p[v] ��ʾ v ���丸�׽ڵ���������߶����ж�Ӧ��λ��
int fp[MAXN];//fp �� p �����෴
int son[MAXN];//�ض���
int pos;//��״�����ָ��

int e[MAXN][3];
int n;

//�߶���
int tree[(MAXN * 2) << 2];
void pushUp(int rt)
{
    tree[rt] = max(tree[rt << 1], tree[rt << 1 | 1]);
}
void build(int l, int r, int rt)
{
    if(l == r)
    {
        tree[rt] = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(l, mid, rt << 1);
    build(mid + 1, r, rt << 1 | 1);
    pushUp(rt);
}
void update(int L, int c, int l, int r, int rt)
{
    if(l == r)
    {
        tree[rt] = c;
        return;
    }
    int mid = (l + r) >> 1;
    if(L <= mid) update(L, c, l, mid, rt << 1);
    else update(L, c, mid + 1, r, rt << 1 | 1);
    pushUp(rt);
    return;
}
int query(int L, int R, int l, int r, int rt)
{
    if(L <= l && r <= R)
    {
        return tree[rt];
    }
    int mid = (l + r) >> 1;
    int ans = -1;
    if(L <= mid) ans = max(ans, query(L, R, l, mid, rt << 1));
    if(R > mid) ans = max(ans, query(L, R, mid + 1, r, rt << 1 | 1));
    return ans;
}

void init()
{
    tot = 0;
    memset(head, -1, sizeof(head));
    pos = 0;//��Ϊ�Ǵ洢�ߣ���Ŵ�ͷ 0 ��ͷ
    memset(son, -1, sizeof(son));
}
void addEdge(int u, int v)
{
    edge[tot].to = v;
    edge[tot].nxt = head[u];
    head[u] = tot++;
}
void dfs1(int u, int pre, int d)
{
    dep[u] = d;
    fa[u] = pre;
    sz[u] = 1;
    for(int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v != pre)
        {
            dfs1(v, u, d + 1);
            sz[u] += sz[v];
            if(son[u] == -1 || sz[v] > sz[son[u]])
            {
                son[u] = v;
            }
        }
    }
}
void getPos(int u, int sp)
{
    // sp �������������ͷ���
    top[u] = sp;
    p[u] = pos++;
    fp[p[u]] = u;
    if(son[u] == -1) return;
    // �ȴ������ر�
    getPos(son[u], sp);
    // �ٴ������
    for(int i = head[u]; ~i; i = edge[i].nxt)
    {
        int v = edge[i].to;
        if(v != son[u] && v != fa[u])
        {
            getPos(v, v);
        }
    }
}
//��ѯ u -> v �ߵ����ֵ
int queryPath(int u, int v)
{
    int f1 = top[u], f2 = top[v];
    int tmp = 0;
    while(f1 != f2)
    {
        if(dep[f1] < dep[f2])
        {
            swap(f1, f2);
            swap(u, v);
        }
        tmp = max(tmp, query(p[f1], p[u], 1, n, 1));
        u = fa[f1];
        f1 = top[u];
    }
    if(u == v) return tmp;
    if(dep[u] > dep[v]) swap(u, v);//��ʱ v ����
    return max(tmp, query(p[son[u]], p[v], 1, n, 1));
}

void solve()
{
    dfs1(1, 0, 0);
    getPos(1, 1);
    build(1, n, 1);
    for(int i = 0; i < n - 1; i++)
    {
        if(dep[e[i][0]] > dep[e[i][1]])
        {
            swap(e[i][0], e[i][1]);// 0 �Ǹ��� 1 �Ƕ���
        }
        update(p[e[i][1]], e[i][2], 1, n, 1);
    }
    char op[10];
    int u, v;
    while(~scanf("%s", op))
    {
        if(op[0] == 'D') break;
        scanf("%d%d", &u, &v);
        if(op[0] == 'Q')
        {
            printf("%d\n", queryPath(u, v));
        }
        else
        {
            update(p[e[u - 1][1]], v, 1, n, 1);
        }
    }
}
int main()
{
    int t; scanf("%d", &t);
    while(t--)
    {
        init();
        scanf("%d", &n);
        for(int i = 0; i < n - 1; i++)
        {
            scanf("%d%d%d", &e[i][0], &e[i][1], &e[i][2]);
            addEdge(e[i][0], e[i][1]);
            addEdge(e[i][1], e[i][0]);
        }
        solve();
    }
}
