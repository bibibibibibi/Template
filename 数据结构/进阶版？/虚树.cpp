#include<bits/stdc++.h>
#define xx first
#define yy second
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int MAXN=1e5+5;
struct Graph
{
	struct Edge
	{
		int v,nxt,id;
	}E[MAXN*2];
	int tot;
	int head[MAXN];
	void init()
	{
		tot=0;
		memset(head,-1,sizeof(head));
	}
	void addedge(int u,int v,int id=-1)
	{
		E[tot].v=v;E[tot].nxt=head[u];E[tot].id=id;
		head[u]=tot++;
		E[tot].v=u;E[tot].nxt=head[v];E[tot].id=id;
		head[v]=tot++;
	}
	void addedgeV(int u,int v,int id=-1)
	{
		addedge(u,v);
	}
	void debug(int n)
	{
		puts("DEBUG................");
		for(int i=1;i<=n;i++)
			for(int j=head[i];~j;j=E[j].nxt)
				printf("%d %d\n",i,E[j].v);
		puts("");
	}
}G,V;
struct vtree
{
	Graph *G,*V;
	int dep[MAXN],dfn[MAXN],fa[MAXN][20];
	int tag;
	bool key[MAXN];
	void init(Graph *g,Graph *v)
	{
		tag=0;
		G=g;G->init();
		V=v;V->init();
		memset(key,false,sizeof(key));
	}
	void dfs(int now,int f=1)
	{
		dfn[now]=++tag;dep[now]=dep[f]+1;fa[now][0]=f;
		for(int i=1;i<20;i++)
			fa[now][i]=fa[fa[now][i-1]][i-1];
		for(int i=G->head[now];~i;i=G->E[i].nxt)
		{
			int v=G->E[i].v;
			if(v==f) continue;
			dfs(v,now);
		}
	}
	int lca(int x,int y)
	{
		if(dep[x]<dep[y]) swap(x,y);
		for(int i=19;i>=0;i--)
			if(dep[fa[x][i]]>=dep[y])
				x=fa[x][i];
		if(x==y) return x;
		for(int i=19;i>=0;i--)
			if(fa[x][i]!=fa[y][i])
				x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	int stk[MAXN];
	void build(int v[],int sz)
	{
		int top=0;
		sort(v,v+sz,[&](const int &x,const int &y)->bool{return dfn[x]<dfn[y];});
	    int _nt=sz;
		for (int i=0;i<sz;i++)
		{
	        int x=v[i];
	        if(!top){stk[++top]=x;continue;}
	        int plca=lca(stk[top],x);
	        while(dep[stk[top-1]]>dep[plca]&&top>1)
			{
	            V->addedge(stk[top-1],stk[top]);
	            top--;
	        }
	        if(dep[plca]<dep[stk[top]])
			{
	            V->addedge(plca,stk[top]);
	            top--;
	        }
	        if(!top||dep[stk[top]]<dep[plca]) stk[++top]=plca;
	        stk[++top]=x;
	        if(!key[plca]){key[plca]=1;v[_nt++]=plca;}
	    }
	    while(top>1)
		{
	        V->addedge(stk[top-1],stk[top]);
	        top--;
	    }
		sz=_nt;
		for(int i=0;i<sz;i++)
			key[v[i]]=false;
	}
}vt;
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	return 0;
}

