template<int MAXN=15>
class Cantor
{
	ll fac[MAXN];
	void init()
	{
		fac[0]=1;
		for(int i=1;i<MAXN;i++)
			fac[i]=fac[i-1]*i;
	}
	ll encoder(const vector<int> &v)
	{
		int n=v.size();
		ll ret=0;
		for(int i=0;i<n;i++)
		{
			int sum=0;
			for(int j=i+1;j<n;j++)
				if(v[j]<v[i]) sum++;
			ret+=sum*fac[n-1-i];
		}
		return ret;
	}
	void decoder(ll x,int n,vector<int> &res)
	{
		res.clear();
		vector<int> v;
		for(int i=1;i<=n;i++)
			v.pb(i);
		for(int i=n-1;i>=0;i--)
		{
			int pos=x/fac[i];
			res.pb(v[pos]);
			v.erase(v.begin()+pos);
			x%=fac[i];
		}
	}
};
