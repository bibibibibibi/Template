const int MAXN=500+10;
const int MAXM=4e4+10;
const int INF=0x3f3f3f3f;
typedef long long ll;
namespace DINIC
{
	struct Edge
	{
		int u,v,cap,nxt;
		Edge(){}
		Edge(int _u,int _v,int _cap,int _nxt):u(_u),v(_v),cap(_cap),nxt(_nxt){}
	}E[MAXM];
	int head[MAXN],dis[MAXN],vis[MAXN];
	int tol;
	void init()
	{
		tol=0;
		memset(head,-1,sizeof(head));
	}
	void addedge(int u,int v,int cap)
	{
		E[tol]=Edge(u,v,cap,head[u]);//正向边
		head[u]=tol++;
		E[tol]=Edge(v,u,0,head[v]);//反向边容量为0
		head[v]=tol++;
	}
	bool BFS(int S,int T)
	{
		queue<int> q;
		q.push(S);
		memset(dis,0x3f,sizeof(dis));
		dis[S]=0;
		while(!q.empty())
		{
			int x=q.front();
			q.pop();
			for(int i=head[x];~i;i=E[i].nxt)
			{
				if(E[i].cap>0&&dis[E[i].v]==INF)
				{
					dis[E[i].v]=dis[x]+1;
					if(E[i].v==T)
						return true;
					q.push(E[i].v);
				}
			}
		}
		return dis[T]<INF; //返回是否能够到达汇点
	}
	int dfs(int x,int maxflow,int T)
	{
		if(x==T||maxflow<=0)
			return maxflow;
		//i=vis[x]当前弧优化
		int ret=0;
		for(int &i=vis[x];~i;i=E[i].nxt)
		{
			if(dis[E[i].v]==dis[x]+1&&E[i].cap>0)
			{
				int flow=dfs(E[i].v,min(maxflow,E[i].cap),T);
				if(flow)
				{
					ret+=flow;
					maxflow-=flow;
					E[i].cap-=flow;//正向边流量降低
					E[i^1].cap+=flow; //反向边流量增加
				}
				if(maxflow==0)
					break;
			}
		}
		return ret;//找不到增广路退出
	}
	ll dinic(int S,int T,int N)
	{
		ll ans=0;
		while(BFS(S,T))//建立分层图
		{
			int flow;
			for(int i=1;i<=N;i++)//初始化vis，注意点的标号从0开始的时候要修改
			{
				vis[i]=head[i];
			}
			while(flow=dfs(S,INF,T))//一次BFS可以进行多次增广
				ans+=(ll)flow;
		}
		return ans;
	}
}
