void exgcd(ll a,ll b,ll& d,ll& x,ll& y)
{
    if(!b)
	{
		d=a;x=1;y=0;
	}
    else
	{
		exgcd(b,a%b,d,y,x);
		y-=x*(a/b);
	}
}
ll inv(ll a, ll n) //mod n a逆元 
{
    ll d,x,y;
    exgcd(a,n,d,x,y);
    return d==1?(x+n)%n:-1;
}
/*
x = ai(mod mi)
m1 * m2 * ... * mi = M
mi之间互素
x = sigma(ai * Mi * Mi(-1)) % M
Mi = M / mi
Mi(-1) = Mi 模mi的逆
*/
ll mul(ll a,ll b,ll M)
{
    ll ret=0;
    while(b)
	{
        if(b&1)
			ret=(ret+a)%M;
        a=a*2%M;
        b>>=1;
    }
    return ret;
}
ll CRT(ll a[],ll m[],ll n)//a余数，m模数 
{
    ll M=1;
    ll ans=0;
    for(int i=1;i<=n;i++)
        M*=m[i];
    for(int i=1;i<=n;i++)
	{
        ll Mi=M/m[i];
        ll x,y,d;
        exgcd(Mi,m[i],d,x,y);
        ans=(ans+mul(x,mul(a[i],Mi,M),M))%M;
    }
    if(ans<0)
		ans+=M;
    return ans;
}
