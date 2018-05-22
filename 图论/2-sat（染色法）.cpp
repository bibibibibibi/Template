const int MAXN=20020;
const int MAXM=100010;
struct Edge
{
	int to,next;
}edge[MAXM];
int head[MAXN],tot;
void init()
{
	tot=0;
	memset(head,-1,sizeof(head));
}
void addedge(int u,int v)
{
	edge[tot].to=v;edge[tot].next=head[u];head[u]=tot++;
} 
bool vis[MAXN];//染色标记，为true表示选择
int S[MAXN],top;//栈
bool dfs(int u)
{
	if(vis[u^1])return false;
	if(vis[u])return true;
	vis[u]=true;
	S[top++]=u;
	for(int i=head[u];i!=-1;i=edge[i].next)
		if(!dfs(edge[i].to))
			return false;
	return true;
}
bool Twosat(int n)
{
	memset(vis,false,sizeof(vis));
	for(int i=0;i<n;i+=2)
	{
		if(vis[i]||vis[i^1])continue;
		top=0;
		if(!dfs(i))
		{
			while(top)vis[S[--top]]=false;
			if(!dfs(i^1)) return false;
		}
	}
	return true;
}
int main()
{
	int n,m;
	int u,v;
	while(~scanf("%d%d",&n,&m))
	{
		init();
		while(m--)
		{
			scanf("%d%d",&u,&v);
			u--;v--;
			addedge(u,v^1);
			addedge(v,u^1);
		}
		if(Twosat(2*n))
		{
			for(int i=0;i<2*n;i++)
				if(vis[i])
					printf("%d\n",i+1);
		}
		else printf("NIE\n");
	} 
	return 0;
}
