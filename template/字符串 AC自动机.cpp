//��̬����
const int MAXN = 26;
const int MAX = 1e6 + 10;
struct Trie
{
    Trie* next[MAXN];
    Trie* fail;
    int sum;
}* root;
int cnt;
Trie* q[MAX];//�ɸ�
void Insert(char* s)
{
    Trie* p = root;
    for(int i = 0; s[i]; i++)
    {
        int id = s[i] - 'a';
        if(p -> next[id] == NULL)
        {
            Trie* t;
            t = new Trie;
            for(int j = 0; j < MAXN; j++)
            {
                t -> next[j] = NULL;
            }
            t -> sum = 0;
            t -> fail = NULL;
            p -> next[id] = t;
        }
        p = p -> next[id];
    }
    p -> sum++;
}
void BuildFailPointer()//BFS
{
    int head = 0;
    int tail = 1;
    q[head] = root;
    Trie* p;
    Trie* temp;
    while(head < tail)
    {
        temp = q[head++];//ȡ����
        for(int i = 0; i < MAXN; i++)
        {
            if(temp -> next[i])//��ǰ�ڵ�������ӽڵ�
            {
                if(temp == root)
                {
                    temp -> next[i] -> fail = root;
                }
                else
                {
                    p = temp -> fail;//��ʼѰ�� ����temp��ָ�ַ� �ĺ�׺
                    while(p)//root -> fail = NULL�� ֱ��root����һ���ַ�Ҳû�����ǵ�Ŀ�꣨��next��i����
                    {
                        if(p -> next[i])//���ĳ����׺����һλ����temp����һλ
                        {
                            temp -> next[i] -> fail = p -> next[i];
                            break;
                        }
                        p = p -> fail;//����Ѱ����ȥ
                    }
                    if(p == NULL) temp -> next[i] -> fail = root;
                }
                q[tail++] = temp -> next[i];//�ѵ�ǰ�ڵ���ӽڵ�����β
            }
        }
    }
}
void acAutomation(char* ch)
{
    Trie* p = root;
    for(int i = 0; ch[i]; i++)
    {
        int id = ch[i] - 'a';
        while(!p -> next[id] && p != root)//ֱ��p��ָ�ڵ���ӽڵ�����Ҫ�ַ�����p��ָΪ���ڵ�
            p = p -> fail;
        p = p -> next[id];
        if(!p) p = root;

        Trie* temp = p;
        while(temp != root)//���� ��p��ָ�ڵ��ַ� Ϊ��׺�ĵ����� �Ƿ��ǵ��ʽ�β
        {
            if(temp -> sum >= 0)
            {
                cnt += temp -> sum;
                temp -> sum = -1;//�����Ѿ��������� �����ظ�����
            }
            else break;//�����Ѿ��������� �����ظ�����
            temp = temp -> fail;
        }
    }
}
void DelTrie(Trie* T)
{
    if(T == NULL) return;
    for(int i = 0; i < MAXN; i++)
    {
        if(T -> next[i] != NULL)
            DelTrie(T -> next[i]);
    }
    delete T;
    return;
}



//��̬����
const int MAXN = 1e5 + 10;
struct Trie
{
    int next[MAXN][26], fail[MAXN], end[MAXN];
    int root, L;
    int newnode()
    {
        for(int i = 0; i < 26; i++)
            next[L][i] = -1;
        end[L++] = 0;
        return L-1;
    }
    void init()
    {
        L = 0;
        root = newnode();
    }
    void insert(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        for(int i = 0; i < len; i++)
        {
            if(next[now][buf[i]-'a'] == -1)
                next[now][buf[i]-'a'] = newnode();
            now = next[now][buf[i]-'a'];
        }
        end[now]++;
    }
    void build()//����failָ��
    {
        queue<int> Q;
        fail[root] = root;
        for(int i = 0; i < 26; i++)
            if(next[root][i] == -1)
                next[root][i] = root;
            else
            {
                fail[next[root][i]] = root;
                Q.push(next[root][i]);
            }
        while(!Q.empty())
        {
            int now = Q.front(); Q.pop();
            for(int i = 0; i < 26; i++)
                if(next[now][i] == -1)
                    next[now][i] = next[fail[now]][i];
                else
                {
                    fail[next[now][i]] = next[fail[now]][i];
                    Q.push(next[now][i]);
                }
        }
    }
    int query(char buf[])
    {
        int len = strlen(buf);
        int now = root;
        int res = 0;
        for(int i = 0; i < len; i++)
        {
            now = next[now][buf[i]-'a'];
            int temp = now;
            while( temp != root )
            {
                res += end[temp];
                end[temp] = 0;
                temp = fail[temp];
            }
        }
        return res;
    }
    void debug()
    {
        for(int i = 0; i < L; i++)
        {
            printf("id = %3d,fail = %3d,end = %3d,chi = [",i,fail[i],end[i]);
            for(int j = 0;j < 26;j++)
                printf("%2d",next[i][j]);
            printf("]\n");
        }
    }
}ac;
char buf[1000010];
int main()
{
    int T;
    int n;
    scanf("%d",&T);
    while( T-- )
    {
        scanf("%d",&n);
        ac.init();
        for(int i = 0;i < n;i++)
        {
            scanf("%s",buf);
            ac.insert(buf);
        }
        ac.build();
        scanf("%s",buf);
        printf("%d\n",ac.query(buf));
    }
    return 0;
}
