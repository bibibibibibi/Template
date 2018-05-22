const int MAXL=50;//位数
typedef long long ll;
struct LinearBasis
{
	ll v[MAXL+1];
	int sz,n;
	LinearBasis()
	{
		memset(v,0,sizeof(v));
	}
	void add(ll x)
	{
		for(int i=MAXL;i>=0;i--)
		{
			if(x&(1LL<<i))
			{
				if(!v[i])
				{
					v[i]=x;
					break;
				}
				x^=v[i];
			}
		}
	}
	ll queryMax()
	{
		ll x=0;
		for(int i=MAXL;i>=0;i--)
			if((x^v[i])>x)
				x^=v[i];
		return x;
	}
	//第k大预处理
	void init(int _n)//n加入的数的个数
	{
		n=_n;sz=0;
		for(int i=0;i<=MAXL;i++)
			for(int j=i+1;j<=MAXL;j++)
				if((v[j]>>i)&1) 
					v[j]^=v[i];
		for(int i=0;i<=MAXL;i++)
			if(v[i])
				v[sz++]=v[i];
	}
	ll query(ll k)
	{
		if(sz!=n)
			k--;
		if(k>(1ll<<sz)-1)
			return -1;
		ll ans=0;
		for(int i=0;i<=MAXL;i++)
			if(k&(1LL<<i))
				ans^=v[i];
		return ans;
	}
}lb;