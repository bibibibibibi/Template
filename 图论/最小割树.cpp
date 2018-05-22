#include <set>
#include <cstdio>
#include <cstring>
#include <algorithm>

#define Rep(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i<=(i##_END);i++)
#define For(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i!=(i##_END);i++)
#define Lop(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i>=(i##_END);i--)
#define Dnt(i, _begin, _end) for(int i=(_begin),i##_END=(_end);i!=(i##_END);i--)

using std :: max;
using std :: min;

const int maxx=1000+25;
const int maxm=10000+25;
const int Inf=(-1u)>>1;

int n,m,x,y,z,k,num=1;
int s,t,front,back,ans;

int head[maxx],cur[maxx],quq[maxx],deep[maxx];
int A[maxx],tmp[maxx];
int to[maxm<<1],nxt[maxm<<1],cap[maxm<<1];

bool vis[maxx];

std :: set<int> Cut;

namespace Dinic
{
	void Ins(int x,int y,int c)
	{
		to[++num]=y;nxt[num]=head[x];cap[num]=c;head[x]=num;
		to[++num]=x;nxt[num]=head[y];cap[num]=c;head[y]=num;
	}
	bool Bfs()
	{
		int x;
		Rep(i,1,n) 
			deep[i]=0;
		deep[quq[front=0]=s]=back=1;
		while(front!=back)
			for(int i=head[x=quq[front ++]];i;i=nxt[i])
				if(!deep[to[i]]&&cap[i])
				{
					deep[quq[back++]=to[i]]=deep[x]+1;
					if(to[i]==t)
						return true;
				}
		return deep[t];
	}
	int Dfs(int x, int v)
	{
		int f;
		if(x==t||!v) 
			return v;
		for(int &i=cur[x];i;i=nxt[i])
			if(deep[to[i]]==deep[x]+1&&cap[i])
				if(f=Dfs(to[i],min(v,cap[i])))
					return cap[i]-=f,cap[i^1]+=f,f;
		return 0;
	}
	int dinic()
	{
		int flow,ans=0;
		while(Bfs())
		{
			memcpy(cur,head,sizeof(cur));
			while(flow=Dfs(s,Inf))
				ans+=flow;
		}
		return ans;
	}
	
}

namespace Gomory_Hu_Tree
{
	using namespace Dinic;
	void init()
	{
		for(int i=2;i<=num;i+=2) 
			cap[i]=cap[i^1]=(cap[i]+cap[i^1])>>1;
		for(int i=1;i<=n;i++)
			vis[i]=0;
	}
	void Dfs(int x)
	{
		vis[x] = 1;
		for(int i=head[x];i;i=nxt[i])
			if(!vis[to[i]] && cap[i])
				Dfs(to[i]);
	}
	void Get(int L, int R)
	{
		if(L>=R)
			return;
		init();
		s=A[L];t=A[R];
		int f=dinic();
		Cut.insert(f);
		int l=L,r=R;
		Dfs(s);
		for(int i=L;i<=R;i++)
			if(vis[A[i]]) 
				tmp[l++]=A[i];
			else 
				tmp[r--]=A[i];
		for(int i=L;i<=R;i++)
			A[i]=tmp[i];
		Get(L, l-1);Get(r+1, R);
	}
}

using namespace Gomory_Hu_Tree;

int main()
{
	scanf("%d%d", &n, &m);
	Rep(i, 1, m) scanf("%d%d%d", &x, &y, &z),Ins(x, y, z);
	Rep(i, 1, n) A[i] = i;
	Get(1, n);
	printf("%d\n",Cut.size());
	return 0;
}
