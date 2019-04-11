/*
1���ô���ɸ����
2�����Ӷȣ�O��n��
3��ע�ͣ�
��1������˼�룺1��a Ϊ�κ����� b Ϊ������ ��ô a * b �������� 2������ÿһ������������ֻ������С������ɸ��һ��
��2��prime�����е����ǵ����ģ����� i % prime[j] == 0 ʱ�� break ����
    ��ô i * prime[j + 1] Ҳ�ᱻɸ���� Ȼ�� i * prime[j + 1] �ܱ� prime[j] ɸ����
*/
/*��ͨ��ŷ��������ɸ*/
const int MAXN = 1000;
bool notPrime[MAXN];
int prime[MAXN];
int cnt;
void primeSieve()
{
    notPrime[1] = 1;
    for(int i = 2; i < MAXN; i++)
    {
        if(notPrime[i] == 0)
        {
            prime[cnt++] = i;
        }
        for(int j = 0; j < cnt && prime[j] * i < MAXN; j++)
        {
            notPrime[ prime[j] * i ] = 1;
            if(i % prime[j] == 0) break;
        }
    }
}
