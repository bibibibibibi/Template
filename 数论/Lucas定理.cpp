const int MOD;
ll qpow(ll x,ll k)
{
	int res=1;
	while(k)
	{
		if(k&1)
			res=res*x%MOD;
		x=x*x%MOD;
		k>>=1;
	}
	return res;
}
ll fact[MOD+10],inv[MOD+10];
void init()
{
	fact[0]=1;
	inv[0]=1;
	for(int i=1;i<=MOD;i++)
	{
		fact[i]=fact[i-1]*i%MOD;
		inv[i]=qpow(fact[i],MOD-2,MOD);
	}
}
ll Lucas(ll n,ll m)
{
	ll a,b,res=1LL;
	while(n&&m)
	{
		a=n%MOD,b=m%MOD;
		if(a<b)
			return 0LL;
		res=res*fact[a]%MOD*inv[b]%MOD*inv[a-b]%MOD;
		n/=MOD,m/=MOD;
	}
	return res;
}
