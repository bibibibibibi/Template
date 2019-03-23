#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=200005;
const int M=300005;
//hdu 4694
int n,m;
struct Graph
{
	struct edge
	{
		int v,nxt;
		edge(int _v=0,int _nxt=0):v(_v),nxt(_nxt){}
	}E[M];
	int tot,head[MAXN];
	void init()
	{
		tot=0;
		memset(head,-1,sizeof(head));
	}
	void addedge(int u,int v)
	{
		E[tot]=edge(v,head[u]);
		head[u]=tot++;
	}
}g,revg,ng,dt;

int dfn[MAXN],id[MAXN],fa[MAXN],dfs_clock;
void dfs(int u)
{
	id[dfn[u]=++dfs_clock]=u;
	for(int e=g.head[u],v;~e;e=g.E[e].nxt)
	{
		v=g.E[e].v;
		if(dfn[v])continue;
		fa[v]=u;dfs(v);
	}
}

int semi[MAXN],idom[MAXN],bel[MAXN],val[MAXN];
inline int getfa(int x)
{
	if(x==bel[x]) return x;
	int tmp=getfa(bel[x]);
	if(dfn[semi[val[bel[x]]]]<dfn[semi[val[x]]]) val[x]=val[bel[x]];
	return bel[x]=tmp;
}

void tarjan()
{
	for(int i=dfs_clock;i>1;--i)
	{
		int u=id[i];
		for(int e=revg.head[u],v;~e;e=revg.E[e].nxt)
		{
			v=revg.E[e].v;
			if(!dfn[v])continue;
			getfa(v);
			if(dfn[semi[val[v]]]<dfn[semi[u]])semi[u]=semi[val[v]];
		}
		ng.addedge(semi[u],u);
		bel[u]=fa[u];
		u=fa[u];
		for(int e=ng.head[u],v;~e;e=ng.E[e].nxt)
		{
			v=ng.E[e].v;
			getfa(v);
			if(semi[val[v]]==u) idom[v]=u;
			else idom[v]=val[v];
		}
	}
	for(int i=2;i<=dfs_clock;++i)
	{
		int u=id[i];
		if(idom[u]!=semi[u]) idom[u]=idom[idom[u]];
	}
}

ll ans[MAXN];
void dfs_ans(int u)
{
	ans[u]+=u;
	for(int e=dt.head[u],v;~e;e=dt.E[e].nxt)
	{
		v=dt.E[e].v;
		ans[v]+=ans[u];
		dfs_ans(v);
	}
}

int main()
{
	while(~scanf("%d%d",&n,&m))
	{
		dfs_clock=0;
		g.init();revg.init();ng.init();dt.init();
		memset(ans,0,sizeof(ans));
		memset(dfn,0,sizeof(dfn));
		memset(idom,0,sizeof(idom));
		for(int i=1;i<=m;++i)
		{
			int u,v;
			scanf("%d%d",&u,&v);
			g.addedge(u,v);
			revg.addedge(v,u);
		}
		for(int i=1;i<=n;++i) semi[i]=bel[i]=val[i]=i;
		dfs(n);
		tarjan();
		for(int i=1;i<n;++i) dt.addedge(idom[i],i);
		dfs_ans(n);
		printf("%lld",ans[1]);
		for(int i=2;i<=n;++i) printf(" %lld",ans[i]);
		puts("");
	}
	return 0;
}

