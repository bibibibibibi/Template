const int MAXL=50;//位数
typedef long long ll;
template<typename Tp>
struct LinearBasis
{
	Tp v[MAXL+1];
	int sz,n;
	LinearBasis()
	{
		memset(v,0,sizeof(v));
	}
	//上三角矩阵
	void add(Tp x)
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
	Tp queryMax()
	{
		Tp x=0;
		for(int i=MAXL;i>=0;i--)
			x=max(x,x^v[i]);
		return x;
	}
	//第k大预处理，化成类对角矩阵形式
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
	Tp query(ll k)
	{
		if(sz!=n)//sz!=n 说明可以组合出0
			k--;
		if(k>(1ll<<sz)-1)
			return -1;
		Tp ans=0;
		for(int i=0;i<=MAXL;i++)
			if(k&(1LL<<i))
				ans^=v[i];
		return ans;
	}
};