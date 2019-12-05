void FMT(int *A,int o)
{
	//o为识别因子
	for(int i=1;i<ST;i<<=1)//ST-1表示全集
		for(int j=0;j<ST;j++)
			if(i&j) (A[j]+=A[j^i]*o)%=MOD;
}
for(int i=0;i<=n;i++) FMT(g[i],1);
for(int i=0;i<=n;i++) FMT(f[i],1);
//h[i][k] 含有i个元素的集合k的结果i==__builtin_popcount(k)时状态有效,f和g同理
for(int i=0;i<=n;i++)
{
	for(int j=0;j<=i;j++)
		for(int k=0;k<ST;k++)
			(h[i][k]+=1ll*f[j][k]*g[i-j][k]%MOD)%=MOD;
	FMT(h[i],-1);
	for(int k=0;k<ST;k++) if(cnt[k]!=i) h[i][k]=0;//cnt[k]=__builtin_popcount(k)
	//if(i!=n) FMT(h[i],1);//cf 914G用不到，暂时不知道这句有啥用
}
