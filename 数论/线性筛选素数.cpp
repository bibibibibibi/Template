int prime[MAXN];//保存素数 
bool vis[MAXN];//初始化 
int cnt=0;
void Prime(int n=MAXN)
{
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	for(int i=2;i<n;i++)
	{
		if(!vis[i])
			prime[cnt++]=i;
		for(int j=0;j<cnt&&i*prime[j]<n;j++)
		{
			vis[i*prime[j]]=1;
			if(i%prime[j]==0)//关键 
				break;
		}
	}
}
