const int MAXN=1e5+5;//点数
const int MAXM=2e5+5;//边数，因为是无向图，所以这个值要*2
struct node
{
	int next,to,id;
}edge[MAXM];

bool Instack[MAXN],cut[MAXN],vis[MAXM];
int head[MAXN],DFN[MAXN],Low[MAXN],Belong[MAXM],Stack[MAXM];//Belong表示第i条边属于第一个联通分量
int tot,Index,root,top,block;//block为联通分量的个数

void addedge(int u,int v,int id)
{
	edge[tot].to=v;edge[tot].id=id;edge[tot].next=head[u];
	head[u]=tot++;
}

void Tarjan(int u,int fa)//fa初值一定要为-1
{
	int cnt=0;
	DFN[u]=Low[u]=++Index;
	Instack[u]=1;
	for(int i=head[u];~i;i=edge[i].next)
	{
		int v=edge[i].to;
		if(vis[edge[i].id]) continue;
		vis[edge[i].id]=true;
		Stack[++top]=edge[i].id;
		if(DFN[v]==-1)
		{
			Tarjan(v,u);
			cnt++;
			if(Low[u]>Low[v]) Low[u]=Low[v];
			if(fa<0&&cnt>1) cut[u]=1;
			else if(fa>=0&&Low[v]>=DFN[u]) cut[u]=1;
			if(Low[v]>=DFN[u])
			{
				int t;
				block++;
				do
				{
					t=Stack[top--];
					Belong[t]=block;
				}while(t!=edge[i].id);
			}
		}
		else if(Instack[v]&&Low[u]>DFN[v])
			Low[u]=DFN[v];
	}
}

void init()
{
	memset(DFN,-1,sizeof(DFN));
	memset(Low,0,sizeof(Low));
	memset(Instack,0,sizeof(Instack));
	memset(cut,0,sizeof(cut));
	memset(head,-1,sizeof(head));
	memset(vis,false,sizeof(vis));
	tot=0;Index=0;top=0;block=0;
}