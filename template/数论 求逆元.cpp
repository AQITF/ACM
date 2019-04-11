//��һ
//��p�Ǹ�������ʱ����
//inv(a) = (p - p / a) * inv(p % a) % p
typedef long long ll;
ll inv(ll t, ll p)
{
    //��t����p����Ԫ��ע��:tҪС��p����ô���ǰ�Ȱ�t%pһ��.
    return t == 1 ? 1 : (p - p / t) * inv(p % t, p) % p;
}
//��������������󵥸���Ԫ����������O(n)�ĸ��Ӷ������n��������Ԫ
ll inv[N];
void init()
{
    inv[1] = 1;
    for(int i = 2; i < N; i++)
    {
        inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
    }
}
//--------------------------------------------

//���� ��չŷ�����
//��a����m����Ԫ��a��m����
ll exgcd(ll a, ll b, ll &x, ll &y)
{
    ll d = a;
    if(b != 0LL)
    {
        d = extgcd(b, a % b, y, x);
        y -= (a / b) * x;
    }
    else
    {
        x = 1; y = 0;
    }
    return d;
}
ll mod_inverse(ll a, ll m)
{
    ll x, y;
    extgcd(a, m, x, y);
    return (m + x % m) % m;
}
//--------------------------------------------

//���� ŷ����������С����
//��������Ĵ�ǰ�᣺��a,m) = 1
//��pΪ����ʱ��inv(a) = a^(p-2) (mod p)
//��pΪ����(��һ��������ʱ�� inv(a) = a^(euler(p) - 1) (mod p)
//����ֻҪ��������ݼ���

LL pow_mod(ll a, ll b, ll p){//a��b�η�����p
    ll ret = 1;
    a = a % p;
    while(b){
        if(b & 1) ret = (ret * a) % p;
        a = (a * a) % p;
        b >>= 1;
    }
    return ret;
}
ll Fermat(ll a, ll p){
    //������a����b����Ԫ
    return pow_mod(a, p-2, p);
}































