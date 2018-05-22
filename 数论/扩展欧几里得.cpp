ll exgcd(ll a,ll b,ll &x,ll &y)//扩展gcd
{
	ll r,t;
	if(b==0)
	{
		x=1;y=0;
		return a;
	}
	r=exgcd(b,a%b,x,y);
	t=x;x=y;
	y=t-a/b*y;
	return r;
}

ll cal(ll a,ll b,ll c)//求解ax+by=c的x的最小整数解
{
    ll x,y,ret,gcd;
    gcd=exgcd(a,b,x,y);
    if(c%gcd!=0) return -1;
    x*=c/gcd;b/=gcd;
    if(b<0) b=-b;
    ret=x%b;
    if(ret<=0) ret+=b;
    return ret;
}
