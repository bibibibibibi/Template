#include<bits/stdc++.h>
#define xx first
#define yy second
using namespace std;
const int MAXN=200000+5;

int vis[MAXN];
int fa[MAXN];
vector<int> line,V[MAXN];

struct node
{
	int s,e,an;
	node(){}
	node(int _s,int _e,int _an):s(_s),e(_e),an(_an){}
};

int bfs(int s,int flag)
{
	queue<int> q;
	line.clear();
	memset(vis,0,sizeof(vis));
	memset(fa,-1,sizeof(fa));
	vis[flag]=1;
	int e=s;
	q.push(s);
	vis[s]=1;
	int ans=1;
	while(!q.empty())
	{
		int f=q.front();
		q.pop();
		for(int i=0;i<V[f].size();i++)
		{
			int k=V[f][i];
			if(vis[k])
			{
				continue;
			}
			vis[k]=vis[f]+1;
			fa[k]=f;
			if(vis[k]>ans)
			{
				e=k;
				ans=vis[k];
			}
			q.push(k);
		}
	}
	for(int i=e;~i;i=fa[i])
	{
		line.push_back(i);
	}
	return e;
}

pair<int,int> solve2(int fir,int sec)
{
	int p1=bfs(fir,sec);
	int p2=bfs(p1,sec);
	int len=line.size();
	return make_pair(line[len/2],len/2);
}

node solve(int fir,int sec)
{
	node pps;
	int ans=-1;
	pair<int,int> tt=solve2(fir,sec);
	pps.s=tt.xx;
	ans=max(ans,tt.yy);
	tt=solve2(sec,fir);
	pps.e=tt.xx;
	ans=max(ans,tt.yy);
	pps.an=ans;
	return pps;
}

int main()
{
	int n,T,i,x,y;
	scanf("%d",&T);
	while(T--)
	{
		node tt;
		scanf("%d",&n);
		for(i=0;i<n-1;i++)
		{
			scanf("%d%d",&x,&y);
			V[x].push_back(y);
			V[y].push_back(x);
		}
		int p1=bfs(1,n+1);
		int p2=bfs(p1,n+1);
		int len=line.size()/2;
		int a=line[len-1],b=line[len],c=line[len+1];
		if(line.size()%2==0)
		{
			tt=solve(a,b);
		}
		else
		{
			node tt1=solve(a,b);
			node tt2=solve(b,c);
			if(tt1.an>tt2.an)
			{
				tt=tt1;
			}
			else
			{
				tt=tt2;
			}
		}
		printf("%d %d %d\n",tt.an,tt.s,tt.e);
		for(i=0;i<=n;i++)
		{
			V[i].clear();
		}
	}
}
