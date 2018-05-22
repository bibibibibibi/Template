#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#define xx first
#define yy second
using namespace std;
const int maxn=5000+5;
int lenx=0,ls=0,cover[maxn<<3]={0};
int x[maxn<<1]={0},ans=0,last;
pair<int,int> sum[maxn<<3];
bool lcover[maxn<<3],rcover[maxn<<3];
struct sege
{
	int x1,x2,h,flag;
	sege (){}
	sege(int a,int b,int c,int d) :x1(a),x2(b),h(c),flag(d) {}
	friend bool operator < (sege a,sege b)
	{
		return a.h<b.h;
	}
}seg[maxn<<1];
void init()
{
	lenx=0,ls=0,ans=0,last=0;
	memset(cover,0,sizeof(cover));
	memset(sum,0,sizeof(sum));
	memset(lcover,false,sizeof(lcover));
	memset(rcover,false,sizeof(rcover));
}
void work(int l,int r,int root)
{
	if(cover[root]>0)
	{
		sum[root].xx=x[r]-x[l];
		sum[root].yy=1;
		lcover[root]=rcover[root]=true;
	}
	else if(l==r-1)
	{
		sum[root].xx=sum[root].yy=0;
		lcover[root]=rcover[root]=false;
	}
	else
	{
		sum[root].xx=sum[root<<1].xx+sum[root<<1|1].xx;
		sum[root].yy=sum[root<<1].yy+sum[root<<1|1].yy;
		lcover[root]=lcover[root<<1];
		rcover[root]=rcover[root<<1|1];
		if(rcover[root<<1]&&lcover[root<<1|1])
		{
			sum[root].yy--;
		}
	}
}
void merge()
{
	int len=lenx,i;
	lenx=1;
	for(i=1;i<len;i++)
	{
		if(x[i]!=x[i-1])
		{
			x[lenx++]=x[i];
		}
	}
}
void query(int L,int R,int l,int r,int root,int flag)
{
	int m=(l+r)>>1;
	if(L<=l&&r<=R)
	{
		cover[root]+=flag;
		work(l,r,root);
		return ;
	}
	if(l==r-1) return ;
	if(m>=L) query(L,R,l,m,root<<1,flag);
	if(m<R) query(L,R,m,r,root<<1|1,flag);
	work(l,r,root);
}
int main()
{
	int x1,x2,y1,y2,n,i;
	while(~scanf("%d",&n)&&n)
	{
		init();
		for(i=0;i<n;i++)
		{
			scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
			if(x1>x2||y1>y2)
			{
				swap(x1,x2);
				swap(y1,y2);
			}
			seg[ls++]=sege(x1,x2,y1,1);
			seg[ls++]=sege(x1,x2,y2,-1);
			x[lenx++]=x1;
			x[lenx++]=x2;
		}
		sort(x,x+lenx);
		merge();
		sort(seg,seg+ls);
		for(i=0;i<ls-1;i++)
		{
			x1=lower_bound(x,x+lenx,seg[i].x1)-x;
			x2=lower_bound(x,x+lenx,seg[i].x2)-x;
			query(x1,x2,0,lenx-1,1,seg[i].flag);
			ans+=(sum[1].yy*2*(seg[i+1].h-seg[i].h)+abs(sum[1].xx-last));
			last=sum[1].xx;
		}
		x1=lower_bound(x,x+lenx,seg[ls-1].x1)-x;
		x2=lower_bound(x,x+lenx,seg[ls-1].x2)-x;
		query(x1,x2,0,lenx-1,1,seg[ls-1].flag);
		ans+=abs(sum[1].xx-last);
		printf("%d\n",ans);
	}
	return 0;
}
