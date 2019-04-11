/*
1���÷����ַ���ƥ��
2�����Ӷȣ�O(|S|) S Ϊ�ܴ�
3��ע�ͣ�
��1��ԭ��H(C) = (c[1] * b^(m-1) + c[2] * b^(m-2) + ... + c[m] * b^0) % h;
            H(S[k + 1 ... k + m]) = H(S[k ... k + m - 1] * b - S[k] * b^m + s[k + m]) % h;
            b �� hΪ�������ʵĻ��س�����ȡ h Ϊ 2^64 ��ͨ����Ȼ���ʡȥ��ģ���㡣
*/
typedef unsigned long long ull;
const ull B = 1e8 + 7; //��ϣ�Ļ���

//a�Ƿ���b�г���
bool contain(string& a, string& b)
{
    int al = a.length(), bl = b.length();
    if(al > bl) return false;

    //����B��al�η�
    ull t = 1;
    for(int i = 0; i < al; i++) t *= B;

    //����a��b����Ϊal��ǰ׺��Ӧ�Ĺ�ϣֵ
    ull ah = 0, bh = 0;
    for(int i = 0; i < al; i++) ah = ah * B + a[i];
    for(int i = 0; i < al; i++) bh = bh * B + b[i];

    //��b��������һλ�����¹�ϣֵ���ж�
    for(int i = 0 ; i + al <= bl; i++)
    {
        if(ah == bh) return true; //b��λ��i��ʼ����Ϊal���ַ����Ӵ�����a
        if(i + al < bl) bh = bh * B + b[i + al] - b[i] * t;
    }
    return false;
}

//a�ĺ�׺��b��ǰ׺��ȵ���󳤶�
int overlap(string& a, string& b)
{
    int al = a.length(), bl = b.length();
    int ans = 0;
    ull ah = 0, bh = 0, t = 1;
    for(int i = 1; i <= min(al, bl); i++)
    {
        ah = ah + a[al - i] * t;
        bh = bh * B + b[i - 1];
        if(ah == bh) ans = i;
        t *= B;
    }
    return ans;
}

//BKDR hash
unsigned int BKDRHash(char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int Hash = 0;

    while (*str)
    {
        Hash = Hash * seed + (*str++);
    }

    return (Hash & 0x7FFFFFFF);
}
