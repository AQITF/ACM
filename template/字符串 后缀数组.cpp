#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
const int MAXN = 1e5 + 10;
int n, k;//n���ܴ�����, k�Ǳ�������
int rank[MAXN+1];
int tmp[MAXN+1];
int sa[MAXN+1];

bool compare_sa(int i, int j)
{
    if(rank[i] != rank[j]) return rank[i] < rank[j];
    else
    {
        int ri = i + k <= n ? rank[i + k] : -1;
        int rj = j + k <= n ? rank[j + k] : -1;
        return ri < rj;
    }
}

void construct_sa(string s, int* sa)
{
    n = s.length();

    //��ʼ������Ϊ1��rankֱ��ȡ�ַ��ı���
    for(int i = 0; i <= n; i++)
    {
        sa[i] = i;
        rank[i] = i < n ? s[i] : -1;
    }

    //���öԳ���Ϊk������Ľ���Գ���Ϊ2k������
    for(k = 1; k <= n; k *= 2)
    {
        sort(sa, sa + n + 1, compare_sa);

        //����tmp����ʱ�洢�¼����rank����ת���rank��
        tmp[sa[0]] = 0; //�մ�����Ϊ0
        for(int i = 1; i <= n; i++)
        {
            tmp[sa[i]] = tmp[sa[i - 1]] + (compare_sa(sa[i - 1], sa[i]) ? 1 : 0);
        }
        for(int i = 0; i <= n; i++)
        {
            rank[i] = tmp[i];
        }
    }
}
bool contain(string& s, int* sa, string& t)
{
    int a = 0, b = s.length();
    while(b - a > 1)
    {
        int c = (a + b) / 2;
        //�Ƚ�s��λ��sa[c]��ʼ����Ϊt���Ӵ���t
        if(s.compare(sa[c], t.length(), t) < 0) a = c;
        else b = c;
    }
    return s.compare(sa[b], t.length(), t) == 0;
}
int main()
{
    string str;
    cin >> str;
    construct_sa(str, sa);
    return 0;
}












