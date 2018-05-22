#include<bits/stdc++.h>
using namespace std;
const int MAXN=5010;//点数
const int MAXM=20010;//边数，因为是无向图，所以这个值要*2
struct Edge
{
	int to,next;
	bool cut;//是否是桥标记
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN],Belong[MAXN];//Belong数组的值是1~block
int Index,top;
int block;//边双连通块数
bool Instack[MAXN];
int bridge;//桥的数目
void addedge(int u,int v)
{
	edge[tot].to=v;edge[tot].next=head[u];edge[tot].cut=false;
	head[u]=tot++;
}
void Tarjan(int u,int pre)
{
	int v;
	bool flag=false;
	Low[u]=DFN[u]=++Index;
	Stack[top++]=u;
	Instack[u]=true;
	for(int i=head[u];~i;i=edge[i].next)
	{
		v=edge[i].to;
		if(v==pre&&(!flag))//或者标记边的id
		{
			flag=true;
			continue;
		}
		if(!DFN[v])
		{
			Tarjan(v,u);
			if(Low[u]>Low[v]) Low[u]=Low[v];
			if(Low[v]>DFN[u])
			{
				bridge++;
				edge[i].cut=true;
				edge[i^1].cut=true;
			}
		}
		else if(Instack[v]&&Low[u]>DFN[v])
			Low[u]=DFN[v];
	}
	if(Low[u]==DFN[u])
	{
		block++;
		do
		{
			v=Stack[--top];
			Instack[v]=false;
			Belong[v]=block;
		}
		while(v!=u);
	}
}
void init()
{
	tot=0;
	memset(head,-1,sizeof(head));
}
int du[MAXN];//缩点后形成树，每个点的度数
void solve(int n)
{
	memset(DFN,0,sizeof(DFN));
	memset(Instack,false,sizeof(Instack));
	memset(Belong,0,sizeof(Belong));
	Index=top=block=0;
	Tarjan(1,0);
	int ans=0;
	memset(du,0,sizeof(du));
	for(int i=1;i<=n;i++)
		for(int j=head[i];~j;j=edge[j].next)
			if(edge[j].cut)
				du[Belong[i]]++;
	for(int i=1;i<=block;i++)
		if(du[i]==1)
			ans++;
	//找叶子结点的个数ans,构造边双连通图需要加边(ans+1)/2
	printf("%d\n",(ans+1)/2);
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
			addedge(u,v);
			addedge(v,u);
		}
		solve(n);
	}
	return 0;
}