#include<bits/stdc++.h>
#define xx first
#define yy second
#define mp make_pair
#define pb push_back
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const double pi=acos(-1);
const double eps=1e-8;
struct Point
{
	double x,y,z;
	void input(){scanf("%lf%lf%lf",&x,&y,&z);}
	Point(double _x=0,double _y=0,double _z=0):x(_x),y(_y),z(_z){}
	Point operator + (const Point &o)const
	{
		Point ret=Point(x+o.x,y+o.y,z+o.z);
		return ret;
	}
	Point operator - (const Point &o)const
	{
		Point ret=Point(x-o.x,y-o.y,z-o.z);
		return ret;
	}
	Point operator * (const double &o)const
	{
		Point ret=Point(x*o,y*o,z*o);
		return ret;
	}
	double operator * (const Point &o)const
	{
		return x*o.x+y*o.y+z*o.z;
	}
}s,t,mv;
struct Line
{
	Point s,e;
	Line(){}
	Line(Point _s,Point _e):s(_s),e(_e){}
};
double sqr(const double &x)
{
	return x*x;
}
double dis(const Point &x,const Point &y)
{
	return sqrt(sqr(x.x-y.x)+sqr(x.y-y.y)+sqr(x.z-y.z));
}
struct Matrix
{
	double c[3][3];
	Matrix(const Point &p)
	{
		memset(c,0,sizeof(c));
		c[0][0]=p.x;
		c[1][0]=p.y;
		c[2][0]=p.z;
	}
	Matrix(){memset(c,0,sizeof(c));}
	Matrix operator * (const Matrix &o)const 
	{
		Matrix ret;
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					ret.c[i][j]+=c[i][k]*o.c[k][j];
		return ret;
	}
	void init()
	{
		memset(c,0,sizeof(c));
		c[0][0]=c[1][1]=c[2][2]=1;
	}
	void setX(double seta)
	{
		c[0][0]=1;c[0][1]=0;c[0][2]=0;
		c[1][0]=0;c[1][1]=cos(seta);c[1][2]=-sin(seta);
		c[2][0]=0;c[2][1]=sin(seta);c[2][2]=cos(seta);
	}
	void setY(double seta)
	{
		c[0][0]=cos(seta);c[0][1]=0;c[0][2]=sin(seta);
		c[1][0]=0;c[1][1]=1;c[1][2]=0;
		c[2][0]=-sin(seta);c[2][1]=0;c[2][2]=cos(seta);
	}
	void setZ(double seta)
	{
		c[0][0]=cos(seta);c[0][1]=-sin(seta);c[0][2]=0;
		c[1][0]=sin(seta);c[1][1]=cos(seta);c[1][2]=0;
		c[2][0]=0;c[2][1]=0;c[2][2]=1;
	}
	Matrix inverse(int _n)//¾ØÕóÇóÄæ
	{
		Matrix ret;
		Matrix tmp=(*this);
		ret.init();
		int i,j,k,col,max_r;
		int equ=_n,var=_n;
		for(k=0,col=0;k<equ&&col<var;k++,col++)
		{
			max_r=k;
			for(i=k+1;i<equ;i++)
				if(fabs(c[i][col])>fabs(c[max_r][col]))
					max_r=i;
			if(fabs(c[max_r][col])<eps)
			{
				memset(ret.c,0,sizeof(ret.c));
				return ret;
			}
			if(k!=max_r)
			{
				for(j=col;j<var;j++)
					swap(c[k][j],c[max_r][j]);
				for(j=0;j<var;j++)
					swap(ret.c[k][j],ret.c[max_r][j]);
			}
			for(j=col+1;j<var;j++)
				c[k][j]/=c[k][col];
			for(j=0;j<var;j++)
				ret.c[k][j]/=c[k][col];
			c[k][col]=1;
			for(i=0;i<equ;i++)
				if(i!=k)
				{
					for(j=col+1;j<var;j++)
						c[i][j]-=c[k][j]*c[i][col];
					for(j=0;j<var;j++)
						ret.c[i][j]-=c[i][col]*ret.c[k][j];
					c[i][col]=0;
				}
		}
		(*this)=tmp;
		return ret;
	}
	void debug()
	{
		for(int i=0;i<3;i++,puts(""))
			for(int j=0;j<3;j++)
				printf("%lf ",c[i][j]);
	}
}dir,back,trans;
double NearestPointToLineSeg(Point P,Line L) 
{ 
    Point result; 
    double tmp=((P-L.s)*(L.e-L.s))/((L.e-L.s)*(L.e-L.s)); 
    if(tmp>=0&&tmp<=1) 
    {
       result.x=L.s.x+(L.e.x-L.s.x)*tmp;
       result.y=L.s.y+(L.e.y-L.s.y)*tmp;
       result.z=L.s.z+(L.e.z-L.s.z)*tmp;
    }
    else
    { 
        if(dis(P,L.s)<dis(P,L.e)) 
            result=L.s; 
        else result=L.e; 
    } 
    return dis(result,P);
}
void solve()
{
	int n;
	char op[2];
	s.input();t.input();
	mv=Point(1,0,0);
	scanf("%d",&n);
	dir.init();
	double ans=1e9;
	while(n--)
	{
		double d,an;
		scanf("%lf%s%lf",&d,op,&an);
		Point ns=s;
		s=s+(mv*d);
		if(op[0]=='R') trans.setZ(-an);
		if(op[0]=='L') trans.setZ(an);
		if(op[0]=='U') trans.setY(-an);
		if(op[0]=='D') trans.setY(an);
		dir=dir*trans;
		back=Matrix(Point(1,0,0));
		back=dir*back;
		mv.x=back.c[0][0];mv.y=back.c[1][0];mv.z=back.c[2][0];
		ans=min(ans,NearestPointToLineSeg(t,Line(s,ns)));
	}
	printf("%.2lf\n",ans);
}
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		solve();
	}
	return 0;
}
