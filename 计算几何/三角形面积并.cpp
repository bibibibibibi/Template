#include<algorithm>
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
using namespace std;
const int MAXN=105;
const double eps=1e-12;
const double INF=1e9;

int dcmp(double x)
{
    if(x<=eps&&x>=-eps) return 0;
    return (x>0)?1:-1;
}
struct Vector
{
    double x,y;
    Vector(double X=0,double Y=0)
    {
        x=X,y=Y;
    }
    bool operator < (const Vector &a)const
    {
        return x<a.x||(x==a.x&&y<a.y);
    }
    void read(){scanf("%lf%lf",&x,&y);}
};
typedef Vector Point;
struct Line
{
    Point p,q;
    Line(Point P=Point(0,0),Point Q=Point(0,0))
    {
        p=P,q=Q;
    }
};
Vector operator + (Vector a,Vector b) {return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (Vector a,Vector b) {return Vector(a.x-b.x,a.y-b.y);}
Vector operator * (Vector a,double b) {return Vector(a.x*b,a.y*b);}

int n,LSH;
double ans;
double lsh[MAXN*MAXN*10];
Point seg[MAXN];
Line line[MAXN][4];

double Cross(Vector a,Vector b)
{
    return a.x*b.y-a.y*b.x;
}
bool ins(Point A,Point B,Point C,Point D)
{
    Vector v,w,u;
    v=A-C,w=C-D,u=B-D;
    if(dcmp(Cross(v,w))==dcmp(Cross(u,w))) return 0;
    v=C-A,w=B-A,u=D-A;
    if(dcmp(Cross(v,w))==dcmp(Cross(u,w))) return 0;
    return 1;
}
Point GLI(Point P,Vector v,Point Q,Vector w)
{
    Vector u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}
double Plus(double x)
{
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if (dcmp(line[i][1].p.x-line[i][1].q.x)==0&&dcmp(x==line[i][1].p.x))
            continue;
        double Min=INF,Max=-INF;
        for(int j=1;j<=3;j++)
        {
            if(x<line[i][j].p.x||x>line[i][j].q.x) continue;
            if(dcmp(line[i][j].p.x-line[i][j].q.x)==0) continue;
            Point P=GLI(line[i][j].p,line[i][j].q-line[i][j].p,Point(x,-INF),Vector(0,INF));
            Min=min(Min,P.y),Max=max(Max,P.y);
        }
        if(Max-Min>eps) seg[++cnt]=Point(Min,Max);
    }
    sort(seg+1,seg+cnt+1);
    if(!cnt) return 0.0;
    double l=seg[1].x,r=seg[1].y,sum=0.0;
    for(int i=2;i<=cnt;i++)
    {
        if(seg[i].x-r>eps) sum+=r-l,l=seg[i].x,r=seg[i].y;
        else r=max(r,seg[i].y);
    }
    sum+=r-l;
    return sum;
}
double Minus(double x)
{
    int cnt=0;
    for(int i=1;i<=n;i++)
    {
        if(dcmp(line[i][2].p.x-line[i][2].q.x)==0&&dcmp(x==line[i][2].p.x))
            continue;
        double Min=INF,Max=-INF;
        for(int j=1;j<=3;j++)
        {
            if(x<line[i][j].p.x||x>line[i][j].q.x) continue;
            if(dcmp(line[i][j].p.x-line[i][j].q.x)==0) continue;
            Point P=GLI(line[i][j].p,line[i][j].q-line[i][j].p,Point(x,-INF),Vector(0,INF));
            Min=min(Min,P.y),Max=max(Max,P.y);
        }
        if(Max-Min>eps) seg[++cnt]=Point(Min,Max);
    }
    sort(seg+1,seg+cnt+1);
    if(!cnt) return 0.0;
    double l=seg[1].x,r=seg[1].y,sum=0.0;
    for(int i=2;i<=cnt;i++)
    {
        if(seg[i].x-r>eps) sum+=r-l,l=seg[i].x,r=seg[i].y;
        else r=max(r,seg[i].y);
    }
    sum+=r-l;
    return sum;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        Point A,B,C;A.read(),B.read(),C.read();
        if(A.x>B.x) swap(A.x,B.x),swap(A.y,B.y);
        if(B.x>C.x) swap(B.x,C.x),swap(B.y,C.y);
        if(A.x>B.x) swap(A.x,B.x),swap(A.y,B.y);
        lsh[++LSH]=A.x,lsh[++LSH]=B.x,lsh[++LSH]=C.x;
        line[i][1]=Line(A,B),line[i][2]=Line(B,C);line[i][3]=Line(A,C);
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=3;j++)
            for(int k=i+1;k<=n;k++)
                for(int l=1;l<=3;l++)
                {
                    Point A=line[i][j].p,B=line[i][j].q,C=line[k][l].p,D=line[k][l].q;
                    if(ins(A,B,C,D))
                    {
                        Point q=GLI(A,B-A,C,D-C);
                        lsh[++LSH]=q.x;
                    }
                }
    sort(lsh+1,lsh+LSH+1);LSH=unique(lsh+1,lsh+LSH+1)-lsh-1;
    double last=0.0,now;
    for(int i=1;i<=LSH;i++)
    {
        now=Plus(lsh[i]);
        if(i>1) ans+=(now+last)*(lsh[i]-lsh[i-1])/2.0;
        last=Minus(lsh[i]);
    }
    printf("%.2lf\n",ans-eps);
}
