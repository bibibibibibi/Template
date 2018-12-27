template<typename Tp>
struct Edge
{
	static const int M=1e5+5;
	struct edge
	{
		int v,nxt;
		Tp w;
		edge(int _v=0,int _nxt=0,Tp _w=0):v(_v),nxt(_nxt),w(_w){}
	}E[M];
	int tot,head[M];
	void init()
	{
		tot=0;
		memset(head,-1,sizeof(head));
	}
	void addedge(int u,int v,int w)
	{
		E[tot]=edge(v,head[u],w);
		head[u]=tot++;
	}
	void addedge(int u,int v)
	{
		E[tot]=edge(v,head[u]);
		head[u]=tot++;
	}
	edge operator [] (const int id)const
	{
		return E[id];
	}
};