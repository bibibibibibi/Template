#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int N=1e5+10;
typedef long long ll;
template <class T>
inline bool rd(T &ret)
{
	char c;
	int sgn;
	if(c=getchar(),c==EOF) return 0;
	while(c!='-'&&(c<'0'||c>'9'))
		c=getchar();
	sgn=(c=='-')?-1:1;
	ret=(c=='-')?0:(c-'0');
	while(c=getchar(),c>='0'&&c<='9')
		ret=ret*10+(c-'0');
	ret*=sgn;
	return 1;
}
template <class T>
inline void pt(T x)
{
	if(x<0)
	{
		putchar('-');
		x=-x;
	}
	if(x>9) 
		pt(x/10);
	putchar(x%10+'0');
}
class MST
{
	struct Edge
	{
		int from, to, dis;
		Edge(int _from = 0,int _to=0,int _dis=0):from(_from),to(_to),dis(_dis){}
		bool operator < (const Edge &x) const
		{
			return dis<x.dis;
		}
	}edge[N<<3];
	int f[N],tot;
	int find(int x)
	{
		return x==f[x]?x:f[x]=find(f[x]);
	}
	bool Union(int x,int y)
	{
		x=find(x);y=find(y);
		if(x==y)
			return false;
		if(x>y)
			swap(x,y);
		f[x]=y;
		return true;
	}
public:
	void init(int n)
	{
		for(int i=0;i<=n;i++)f[i]=i;
		tot=0;
	}
	void add(int u,int v,int dis)
	{
		edge[tot++]=Edge(u,v,dis);
	}
	ll work()
	{//计算最小生成树，返回花费
		sort(edge,edge+tot);
		ll cost=0;
		for(int i=0;i<tot;i++)
			if(Union(edge[i].from,edge[i].to))
				cost+=edge[i].dis;
		return cost;
	}
}mst;
struct Point
{//二维平面的点
	int x,y,id;
	bool operator < (const Point&a) const
	{
		return x==a.x?y<a.y:x<a.x;
	}
}p[N];
class BIT
{//树状数组
	int c[N],id[N],maxn;
	int lowbit(int x)
	{
		return x&-x;
	}
public:
	void init(int n)
	{
		maxn=n+10;
		fill(c,c+maxn+1,inf);
		fill(id,id+maxn+1,-1);
	}
	void updata(int x, int val, int _id)
	{
		while(x)
		{
			if(val<c[x])
			{
				c[x]=val;id[x]=_id;
			}
			x-=lowbit(x);
		}
	}
	int query(int x)
	{
		int val=inf,_id=-1;
		while (x<=maxn)
		{
			if(val>c[x])
			{
				val=c[x];_id=id[x];
			}
			x+=lowbit(x);
		}
		return _id;
	}
}tree;
inline bool cmp(int *x, int *y)
{
	return *x<*y;
}
class Manhattan_MST
{//复杂度 O(max(N*1.5,Nlog(N)))
	int A[N], B[N];
public:
	ll work(int l, int r)
	{
		mst.init(r);
		for(int dir = 1; dir <= 4; dir++)
		{
			if(dir%2==0)
				for(int i=l;i<=r;i++)
					swap(p[i].x, p[i].y);
			else if(dir == 3)
				for(int i=l;i<=r;i++)p[i].y=-p[i].y;
			sort(p+l,p+r+1);
			for(int i=l;i<=r;i++) 
				A[i]=B[i]=p[i].y-p[i].x; //离散化
			sort(B+1,B+N+1);
			int sz=unique(B+1,B+N+1)-B-1;
			//初始化反树状数组
			tree.init(sz);
			for(int i=r;i>=l;i--)
			{
				int pos=lower_bound(B+1,B+sz+1, A[i])-B;
				int id=tree.query(pos);
				if (id!=-1)
					mst.add(p[i].id,p[id].id,abs(p[i].x-p[id].x)+abs(p[i].y-p[id].y));
				tree.updata(pos, p[i].x + p[i].y,i);
			}
		}
		for(int i=l;i<=r;i++)
			p[i].y=-p[i].y;
		return mst.work();
	}
}m_mst;
int n;
int main()
{
	int Cas=1;
	while(cin>>n,n)
	{
		for(int i=1;i<=n;i++)
			rd(p[i].x),rd(p[i].y),p[i].id=i;
		printf("Case %d: Total Weight = ",Cas++);
		cout<<m_mst.work(1,n)<<endl;
	}
	return 0;
}
