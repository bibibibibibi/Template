//别用了，假板子，有空我找个新的
#include<cstdio>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

const double eps=1e-8;
inline int dcmp(const double &x)
{
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}

struct Point
{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
};

typedef Point Vector;

Vector operator +(const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator -(const Vector &A,const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
Vector operator *(const Vector &A,const double &p) {return Vector(A.x*p,A.y*p);}

double Dot(const Vector &A,const Vector &B)
{ 
    return A.x*B.x+A.y*B.y;
}
double Cross(const Vector &A,const Vector &B)
{
    return A.x*B.y-A.y*B.x;
}
double Length(const Vector &A)
{
    return sqrt(Dot(A,A));
}
double Angle(const Vector &A,const Vector &B)
{ 
    return acos(Dot(A,B)/Length(A)/Length(B));
}

bool OnSegment(const Point &p,const Point &a1,const Point &a2)
{
    return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dot(a1-p,a2-p))<=0;
}

double DistanceToLine(const Point &p,const Point &a,const Point &b)
{
    Vector v1=b-a,v2=p-a;
    return fabs(Cross(v1,v2))/Length(v1);
}

struct Line
{
    Point p;
    Vector v;
    Line(){}
    Line(Point p,Vector v):p(p),v(v){}
    Point point(double t)
    {
        return p+v*t;
    }
};

struct Circle
{
    Point c;
    double r;
    Circle(){}
    Circle(Point c,double r):c(c),r(r){}
};

int getLineCircleIntersection(Line L,Circle C,vector<Point>& sol)
{
    double a=L.v.x,b=L.p.x-C.c.x,c=L.v.y,d=L.p.y-C.c.y;
    double e=a*a+c*c,f=2*(a*b+c*d),g=b*b+d*d-C.r*C.r;
    double delta=f*f-4*e*g;
    if(dcmp(delta)<0) return 0;

    double t1,t2;
    if (dcmp(delta)==0)
    {
        t1=t2=-f/(2*e);
        sol.push_back(L.point(t1));
        return 1;
    }

    t1=(-f-sqrt(delta))/(2*e);sol.push_back(L.point(t1));
    t2=(-f+sqrt(delta))/(2*e);sol.push_back(L.point(t2));
    return 2;
}

double get_Circle_polygon_Intersect_area(Point A,Point B,Circle C)
{
    Vector CA=C.c-A,CB=C.c-B;
    double da=Length(CA),db=Length(CB);

    da=dcmp(da-C.r);
    db=dcmp(db-C.r);

    if(da<=0&&db<=0)
    {
        return fabs(Cross(CA,CB))*0.5;
    }

    vector<Point> sol;
    int num=getLineCircleIntersection(Line(A,B-A),C,sol);
    double cnt=C.r*C.r;
    Point q;

    if(da<=0&&db>0)
    {
        q=OnSegment(sol[0],A,B)?sol[0]:sol[1];
        double area=fabs(Cross(CA,C.c-q))*0.5;
        double ang=Angle(CB,C.c-q);
        return area+cnt*ang*0.5;
    }

    if(db<=0&&da>0) 
    {
        q=OnSegment(sol[0],A,B)?sol[0]:sol[1];
        double area=fabs(Cross(CB,C.c-q))*0.5;
        double ang=Angle(CA,C.c-q);
        return area+cnt*ang*0.5;
    }

    if(num==2)
    {
        double big_area=cnt*Angle(CA,CB)*0.5;
        double small_area=cnt*Angle(C.c-sol[0],C.c-sol[1])*0.5;
        double delta_area=fabs(Cross(C.c-sol[0],C.c-sol[1]))*0.5;
        return big_area+delta_area-small_area;
    }

    return cnt*Angle(CA,CB)*0.5;
}

Circle C;
double X1,Y1,R;
double X0,Y0,h;
double x,y;
const int MAXN=100000+5;
Point p[MAXN];
int n;

int main()
{
    while(~scanf("%lf%lf%lf",&X0,&Y0,&h))
    {
        scanf("%lf%lf",&X1,&Y1);
        scanf("%lf",&R);
        double t=sqrt(0.2*h);
        C=Circle(Point(X0+X1*t,Y0+Y1*t),R);
        scanf("%d",&n);
        for(int i=0;i<n;i++) 
        {
            scanf("%lf%lf",&x,&y);
            p[i]=Point(x,y);
        }
        p[n]=p[0];
        double area=0;
        for(int i=0;i<n;i++)
        {
            //若干个三角形的有向面积
            double tmp=get_Circle_polygon_Intersect_area(p[i],p[i+1],C);
            if (Cross(p[i]-C.c,p[i+1]-C.c)<0) tmp=-tmp;
            area+=tmp;
        }
        if(area<0) area=-area;
        printf("%.2f\n",area);
    }
    return 0;
}
/*
小白最近被空军特招为飞行员，参与一项实战演习。演习的内容是轰炸某个岛屿。。。
作为一名优秀的飞行员，任务是必须要完成的，当然，凭借小白出色的操作，顺利地将炸弹投到了岛上某个位置，可是长官更关心的是，小白投掷的炸弹到底摧毁了岛上多大的区域？
岛是一个不规则的多边形，而炸弹的爆炸半径为R。
小白只知道自己在（x，y，h）的空间坐标处以（x1,y1,0）的速度水平飞行时投下的炸弹，请你计算出小白所摧毁的岛屿的面积有多大. 重力加速度G = 10.
*/