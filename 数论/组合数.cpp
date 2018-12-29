ll fac[MAXN],inv[MAXN];
ll qpow(ll a,ll b)
{
    ll ret=1;a%=MOD;
    for(ll i=b;i;i>>=1,a=a*a%MOD)
        if(i&1) ret=ret*a%MOD;
    return ret;
}
ll C(ll n,ll m)
{
    if(m>n||m<0) return 0;
    ll s1=fac[n],s2=inv[n-m]*inv[m]%MOD;
    return s1*s2%MOD;
}
void init()
{
    fac[0]=1;
    for(int i=1;i<MAXN;i++)//阶乘打表 
        fac[i]=fac[i-1]*i%MOD;
    inv[0]=1;inv[MAXN-1]=qpow(fac[MAXN-1],MOD-2);//费马小定理求逆元 
    for(int i=MAXN-2;i>=1;i--)
        inv[i]=inv[i+1]*(i+1)%MOD;
}

//预处理版本
int fac[MAXN],C[MAXN][MAXN];
void init()
{
    fac[0]=1;
    for(int i=1;i<MAXN;i++)
    {
        fac[i]=(1LL*fac[i-1]*i)%MOD;
    }
    for(int i=0;i<MAXN;i++)
    {
        C[i][0]=1;
        for(int j=1;j<=i;j++)
            C[i][j]=(C[i-1][j]+C[i-1][j-1])%MOD
    }
}

//求逆元
ll _inv(int x)
{
    if(x==1) return 1;
    return 1LL*(MOD-MOD/x)*_inv(MOD%x)%MOD;
}