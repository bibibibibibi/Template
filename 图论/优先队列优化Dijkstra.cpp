/* 
 * 使用优先队列优化Dijkstra算法 
 * 复杂度O(ElogE) 
 * 注意对vector<Edge>E[MAXN]进行初始化后加边 
 */ 
const int INF=0x3f3f3f3f;
const int MAXN=1000010;
struct qnode
{
	int v;
	int c;
	qnode(int _v=0,int _c=0):v(_v),c(_c){}
	bool operator <(const qnode &r)const
	{
		return c>r.c;
	}
};
struct Edge
{
	int v,cost;
	Edge(int _v=0,int _cost=0):v(_v),cost(_cost){}
};
vector<Edge>E[MAXN];
bool vis[MAXN];
int dist[MAXN];
void Dijkstra(int n,int start)//点的编号从1开始 
{
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++)dist[i]=INF;
	priority_queue<qnode>que;
	while(!que.empty())que.pop();
	dist[start]=0;
	que.push(qnode(start,0));
	qnode tmp;
	while(!que.empty())
	{
		tmp=que.top();
		que.pop();
		int u=tmp.v;
		if(vis[u])continue;
		vis[u]=true;
		for(int i=0;i<E[u].size();i++)
		{
			int v=E[tmp.v][i].v;
			int cost=E[u][i].cost;
			if(!vis[v]&&dist[v]>dist[u]+cost)
			{
				dist[v]=dist[u]+cost;
				que.push(qnode(v,dist[v]));
			}
		}
	}
}
void addedge(int u,int v,int w)
{
	E[u].push_back(Edge(v,w));
}


//邻接表版本 
typedef long long ll;
const ll INF=0x3f3f3f3f3f3f3f3f;
const int MAXN=20010;
int cnt=0;
struct qnode
{
	int v;
	ll c;
	qnode(int _v=0,ll _c=0):v(_v),c(_c){}
	bool operator <(const qnode &r)const
	{
		return c>r.c;
	}
};
struct Edge
{
	int u,v,nxt;
	ll cost;
	Edge(){}
	Edge(int _u,int _v,ll _cost,int _nxt):u(_u),v(_v),cost(_cost),nxt(_nxt){}
};
Edge E[MAXN];
bool book[MAXN],vis[MAXN];
int head[MAXN];
ll dist[MAXN];
void init()
{
	cnt=0;
	memset(head,-1,sizeof(head));
}
void Dijkstra(int n,int start)//点的编号从0开始 
{
	memset(vis,false,sizeof(vis));
	for(int i=0;i<n;i++)dist[i]=INF;
	priority_queue<qnode>que;
	while(!que.empty())que.pop();
	dist[start]=0;
	que.push(qnode(start,0));
	qnode tmp;
	while(!que.empty())
	{
		tmp=que.top();
		que.pop();
		int u=tmp.v;
		if(vis[u])continue;
		vis[u]=true;
		for(int i=head[u];~i;i=E[i].nxt)
		{
			int v=E[i].v;
			int cost=E[i].cost;
			if(!vis[v]&&dist[v]>dist[u]+cost)
			{
				dist[v]=dist[u]+cost;
				que.push(qnode(v,dist[v]));
			}
		}
	}
}
void addedge(int u,int v,ll w)
{
	E[cnt]=Edge(u,v,w,head[u]);
	head[u]=cnt++;
	E[cnt]=Edge(v,u,w,head[v]);
	head[v]=cnt++;
}
