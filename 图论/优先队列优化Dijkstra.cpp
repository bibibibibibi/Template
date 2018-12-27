 //邻接表版本 
//但是权值必须为非负 
typedef long long ll;
namespace Dij
{
	const ll INF=0x3f3f3f3f3f3f3f3f;
	const int MAXN=1e5+5;
	const int M=2e5+5;
	int tot=0;
	struct qnode
	{
		int v;
		ll c;
		qnode(int _v=0,ll _c=0):v(_v),c(_c){}
		bool operator < (const qnode &r)const {return c>r.c;}
	};
	struct Edge
	{
		int u,v,nxt;
		ll cost;
		Edge(int _u=0,int _v=0,int _nxt=0,ll _cost=0):u(_u),v(_v),nxt(_nxt),cost(_cost){}
	};
	Edge E[M];
	bool vis[MAXN];
	int head[MAXN];
	ll dist[MAXN];
	void init()
	{
		tot=0;
		memset(head,-1,sizeof(head));
	}
	void Dijkstra(int start)
	{
		memset(vis,false,sizeof(vis));
		memset(dist,0x3f,sizeof(dist));
		priority_queue<qnode> Q;
		dist[start]=0;
		Q.push(qnode(start,0));
		qnode tmp;
		while(!Q.empty())
		{
			tmp=Q.top();
			Q.pop();
			int u=tmp.v;
			if(vis[u]) continue;
			vis[u]=true;
			for(int i=head[u];~i;i=E[i].nxt)
			{
				int v=E[i].v;
				ll cost=E[i].cost;
				if(!vis[v]&&dist[v]>dist[u]+cost)
				{
					dist[v]=dist[u]+cost;
					Q.push(qnode(v,dist[v]));
				}
			}
		}
	}
	void addedge(int u,int v,ll w)
	{
		E[tot]=Edge(u,v,head[u],w);
		head[u]=tot++;
		E[tot]=Edge(v,u,head[v],w);
		head[v]=tot++;
	}
}