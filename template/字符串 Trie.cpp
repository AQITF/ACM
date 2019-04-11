const int MAXN = 26;
struct Trie
{
    int v;//������Ҫ�仯
    Trie* next[MAXN];
}* root;
void InsertTrie(char* str)
{
    int len = strlen(str);
    Trie* p = root, *q;
    for(int i = 0; i < len; i++)
    {
        int id = str[i] - 'a';
        if(p -> next[id] == NULL)
        {
            q = new Trie;
            q -> v = 1;
            for(int j = 0; j < MAXN; j++)
            {
                q->next[j] = NULL;
            }
            p->next[id] = q;
            p = p->next[id];
        }
        else
        {
            p -> next[id] -> v++;
            p = p -> next[id];
        }
    }
    p->v = -1;//��Ϊ��β����v�ĳ�-1��ʾ ��ط���������ģ�嶼���ã�С��
}
int SearchTrie(char* str)
{
    int len = strlen(str);
    Trie* p = root;
    for(int i = 0; i < len; i++)
    {
        int id = str[i] - 'a';
        p = p->next[id];
        if(p == NULL)
            return 0; //��Ϊ�ռ�����ʾ�������Դ�Ϊǰ׺�Ĵ�
        if(p->v == -1)
            return -1;//�ַ��������д��Ǵ˴���ǰ׺
    }
    return -1;//�˴����ַ�����ĳ����ǰ׺
}
int DelTrie(Trie* T)
{
    if(T == NULL)
        return 0;
    for(int i = 0; i < MAXN; i++)
    {
        if(T->next[i] != NULL)
            DelTrie(T->next[i]);
    }
    delete T;
    return 0;
}


























