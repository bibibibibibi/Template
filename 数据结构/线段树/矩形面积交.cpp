#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#define xx first
#define yy second
using namespace std;
const int maxn=1000+5;
const double esp=1e-8;
int lenx=0,ls=0,cover[maxn<<3]={0};
double x[maxn<<1]={0},ans=0;
pair<double,double> sum[maxn<<3];
struct sege
{
	int flag;
	double x1,x2,h;
	sege (){}
	sege(double a,double b,double c,int d) :x1(a),x2(b),h(c),flag(d) {}
	friend bool operator < (sege a,sege b)
	{
		return a.h<b.h;
	}
}seg[maxn<<1];
void init()
{
	lenx=0,ls=0,ans=0;
	memset(cover,0,sizeof(cover));
	memset(sum,0,sizeof(sum));
}
void work(int l,int r,int root)
{
	if(cover[root]>0)
	{
		sum[root].xx=x[r]-x[l];
		if(cover[root]>1)
		{
			sum[root].yy=sum[root].xx;
		}
		else
		{
			if(l==r-1) sum[root].yy=0;
        	else sum[root].yy=sum[root<<1].xx+sum[root<<1|1].xx;
		}
	}
	else if(l==r-1) sum[root].xx=sum[root].yy=0;
	else sum[root].xx=sum[root<<1].xx+sum[root<<1|1].xx,sum[root].yy=sum[root<<1].yy+sum[root<<1|1].yy;
}
void merge()
{
	int len=lenx,i;
	lenx=1;
	for(i=1;i<len;i++)
	{
		if(x[i]-x[i-1]>=esp)
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
	int n,i,T;
	double x1,x2,y1,y2;
	scanf("%d",&T);
	while(T--)
	{
		init();
		scanf("%d",&n);
		for(i=0;i<n;i++)
		{
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
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
			ans+=(seg[i+1].h-seg[i].h)*sum[1].yy;
		}
		printf("%.2lf\n",ans);
	}
	return 0;
}
