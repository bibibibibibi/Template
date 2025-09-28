/* 
 * Tarjan算法 
 * 复杂度O(N+M) 
 */ 
namespace Tarjan
{
	const int MAXN=2e5+5;//点数
	const int MAXM=4e5+5;//边数
	struct Edge
	{
		int to,nxt;
	}edge[MAXM];
	int head[MAXN],low[MAXN],dfn[MAXN],st[MAXN],be[MAXN];//be是belong数组值是1~scc
	int tot,idx,top,scc; //scc 强连通分量的个数
	bool vis[MAXN]; 
	int num[MAXN];//各个强连通分量包含点的个数，数组编号1~scc 
	//num数组不一定需要，结合实际情况
	void addedge(int u,int v)
	{
		edge[tot].to=v;edge[tot].nxt=head[u];head[u]=tot++;
	}
	void Tarjan(int u)
	{
		int v;
		low[u]=dfn[u]=++idx;
		st[top++]=u;
		vis[u]=true;
		for(int i=head[u];~i;i=edge[i].nxt)
		{
			v=edge[i].to;
			// 求双联通的话在这里判断下是否是来的时候的边
			if(!dfn[v])
			{
				Tarjan(v);
				if(low[u]>low[v])low[u]=low[v];
			}
			else if(vis[v]&&low[u]>dfn[v])
				low[u]=dfn[v];
		}
		if(low[u]==dfn[u])
		{
			scc++;
			do
			{
				v=st[--top];
				vis[v]=false;
				be[v]=scc;
				num[scc]++;
			}
			while(v!=u);
		}
	}
	void solve(int n)
	{
		for(int i=1;i<=n;i++)
			if(!dfn[i])
				Tarjan(i);
	}
	void init(int n)
	{
		idx=scc=top=tot=0;
		fill(head+1,head+1+n,-1);
		fill(dfn+1,dfn+1+n,0);
		fill(vis+1,vis+1+n,0);
		fill(num+1,num+1+n,0);
	}
}
