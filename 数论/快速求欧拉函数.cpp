
ll phi[MAXN];
void init()
{
	int i,j;
	for(i=1;i<MAXN;i++)
		phi[i]=i;
	for(i=2;i<MAXN;i++)
		if(i==phi[i]) //此时i为素数
			for(j=i;j<MAXN;j+=i)  //j累加i
				phi[j]=(phi[j]/i)*(i-1); //j有因子i,而且i是素数,正是欧拉函数
}

//利用积性函数性质，分解素因子之后进行求解
ll phi(ll n)
{
	ll ret=n;
	for(ll i=2;i*i<=n;i++)
	{
		if(n%i==0) ret=ret/i*(i-1);
		while(n%i==0) n/=i;
	}
	if(n>1) ret=ret/n*(n-1);
	return ret;
}
