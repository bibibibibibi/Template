const int MAXN=3e5+5;
const int DEG=20;
struct LCA
{	
	struct Edge 
	{
		int v,nxt; 
	}E[MAXN*2]; 
	int head[MAXN],tot; 
	void addedge(int u,int v) 
	{
		E[tot].v=v;
		E[tot].nxt=head[u];
		head[u]=tot++;
	}
	void init(int n)
	{
		tot=0;
		fill(head,head+1+n,-1);
	}
	int fa[MAXN][DEG];//fa[i][j]表示结点i的第2^j个祖先 
	int dep[MAXN];//深度数组
	void bfs(int root)
	{
		queue<int> Q;
		dep[root]=0;
		fa[root][0]=root;
		Q.push(root);
		while(!Q.empty())
		{
			int tmp=Q.front();
			Q.pop();
			for(int i=1;i<DEG;i++)
				fa[tmp][i]=fa[fa[tmp][i-1]][i-1];
			for(int i=head[tmp];~i;i=E[i].nxt) 
			{
				int v=E[i].v;
				if(v==fa[tmp][0])continue;
				dep[v]=dep[tmp]+1;
				fa[v][0]=tmp;
				Q.push(v);
			}
		}
	}
	int lca(int u,int v) 
	{
		if(dep[u]>dep[v])swap(u,v);
		int hu=dep[u],hv=dep[v];
		int tu=u,tv=v;
		for(int det=hv-hu,i=0;det;det>>=1,i++)
			if(det&1)
				tv=fa[tv][i];
		if(tu==tv)return tu;
		for(int i=DEG-1;i>=0;i--)
		{
			if(fa[tu][i]==fa[tv][i])
				continue;
			tu=fa[tu][i];
			tv=fa[tv][i];
		}
		return fa[tu][0]; 
	}
}lca;
