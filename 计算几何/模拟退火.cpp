#include<bits/stdc++.h>
using namespace std;
//hdu 3007 最小圆覆盖
namespace SA
{
	const double Lim=0.999999;//exp(-dif/T)为概率下降时候的阈值(或者可以用随机数)
	const double EPS=1e-3;
	const double PI=acos(-1.0);
	double Delta,maxx,minx,maxy,miny,lx,ly,dif;//Delta步长
	int n,ns,nc;//ns搜索点的个数，nc每次搜索每个点走的步数
	struct Point
	{
		double x,y;
	}P[505];
	struct Solution
	{
		double x,y;
		double f;
	}S[25];
	double Dis(double x1,double y1,double x2,double y2)
	{
		return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	}
	void Seed()
	{
		for(int i=1;i<=ns;i++)
		{
			S[i].x=minx+((double)(rand()%1000+1)/1000.0)*lx;
			S[i].y=miny+((double)(rand()%1000+1)/1000.0)*ly;
			S[i].f=0.0;
			for(int j=1;j<=n;j++) 
				S[i].f=max(S[i].f,Dis(S[i].x,S[i].y,P[j].x,P[j].y));
		}
	}
	void Trans()
	{
		for(int i=1;i<=ns;i++)
		{
			for(int j=1;j<=nc;j++)//移动次数
			{
				Solution A;
				double theta=(((double)(rand()%1000+1))/1000.0)*2.0*PI;
				//退火的方向，有的题目里设定为八个方向
				A.x=S[i].x+Delta*cos(theta);
				A.y=S[i].y+Delta*sin(theta);
				if(A.x<minx||A.x>maxx||A.y<miny||A.y>maxy) continue;
				A.f=0.0;
				for(int k=1;k<=n;k++)
					A.f=max(A.f,Dis(A.x,A.y,P[k].x,P[k].y));
				dif=A.f-S[i].f;
				if(dif<0.0)
					S[i]=A;
				else
				{
					dif=exp(-dif/Delta);
					if(dif>Lim)
						S[i]=A;
				}
			}
		}
	}
	void solve()
	{
		maxx=maxy=0;
		minx=miny=(1<<20);
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf",&P[i].x,&P[i].y);
			if(maxx<P[i].x) maxx=P[i].x;
			if(minx>P[i].x) minx=P[i].x;
			if(maxy<P[i].y) maxy=P[i].y;
			if(miny>P[i].y) miny=P[i].y;
		}
		lx=maxx-minx;
		ly=maxy-miny;
		Delta=sqrt(lx*lx+ly*ly)/3.0;
		ns=1,nc=1;
		Seed();
		while(Delta>EPS)
		{
			Trans();
			Delta=Delta*0.95;//0.95 0.9
		}
		int ans=1;
		for(int i=1;i<=ns;i++)
			if(S[ans].f>S[i].f)
				ans=i;
		printf("%.2lf %.2lf %.2lf\n",S[ans].x,S[ans].y,S[ans].f);
	}
}
int main()
{
	while(scanf("%d",&SA::n)==1&&SA::n)
	{
		SA::solve();
	}
	return 0;
}


//最小球覆盖
#include<bits/stdc++.h>
using namespace std;
namespace SA
{
	const double EPS=1e-8;
	const double PI=acos(-1.0);
	int n;
	double Delta,ans;
	struct Point
	{
		double x,y,z;
	}P[55];
	struct Solution
	{
		double x,y,z;
	}S;
	double Dis(double x1,double y1,double z1,double x2,double y2,double z2)
	{
		return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2));
	}
	void Trans()
	{
		int id=1;
		double mx=0;
		for(int k=1;k<=n;k++)
		{
			double dis=Dis(S.x,S.y,S.z,P[k].x,P[k].y,P[k].z);
			if(dis>mx) mx=dis,id=k;
		}
		//每次向半径最大的方向移动
		S.x=S.x+(P[id].x-S.x)/mx*Delta;
		S.y=S.y+(P[id].y-S.y)/mx*Delta;
		S.z=S.z+(P[id].z-S.z)/mx*Delta;
		ans=min(ans,mx);
	}
	void solve()
	{
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf%lf",&P[i].x,&P[i].y,&P[i].z);
		}
		S.x=S.y=S.z=0;
		Delta=100;ans=1e10;
		while(Delta>EPS)
		{
			Trans();
			Delta=Delta*0.98;//0.95 0.9
		}
		printf("%.5lf\n",ans);
	}
}
int main()
{
	while(scanf("%d",&SA::n)==1&&SA::n)
	{
		SA::solve();
	}
	return 0;
}
 
