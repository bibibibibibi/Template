const double eps=1e-8;
const double PI=acos(-1.0);
const int MAXN=105;
int sgn(double x)
{
	if(fabs(x)<eps) return 0;
	if(x<0) return -1;
	else return 1;
}
struct Point
{
	double x,y;
	Point(double _x=0.0,double _y=0.0):x(_x),y(_y){}
	Point operator -(const Point &b)const
	{
		return Point(x-b.x,y-b.y);
	}
	double operator ^(const Point &b)const
	{
		return x*b.y-y*b.x;
	}
	double operator *(const Point &b)const
	{
		return x*b.x+y*b.y;
	}
};
struct Line
{
	Point s,e;
	double k;
	Line(){}
	Line(Point _s,Point _e)
	{
		s=_s;e=_e;
		k=atan2(e.y-s.y,e.x-s.x);
	}
	Point operator &(const Line &b)const
	{
		Point res=s;
		double t=((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e));
		res.x+=(e.x-s.x)*t;
		res.y+=(e.y-s.y)*t;
		return res;
	}
};

//半平面交，直线的左边代表有效区域
bool HPIcmp(const Line &a,const Line &b)
{
	if(fabs(a.k-b.k)>eps)return a.k<b.k;
	return ((a.s-b.s)^(b.e-b.s))<0;
}
Line Q[MAXN];
void HPI(Line line[],int n,Point res[],int &resn)
{
	int tot=n;
	sort(line,line+n,HPIcmp);
	tot=1;
	for(int i=1;i<n;i++)
		if(fabs(line[i].k-line[i-1].k)>eps)
			line[tot++]=line[i];
	int head=0,tail=1;
	Q[0]=line[0];
	Q[1]=line[1];
	resn=0;
	for(int i=2;i<tot;i++)
	{
		if(fabs((Q[tail].e-Q[tail].s)^(Q[tail-1].e-Q[tail-1].s))<eps ||
		fabs((Q[head].e-Q[head].s)^(Q[head+1].e-Q[head+1].s))<eps)
			return;
		while(head<tail&&(((Q[tail]&Q[tail-1])-
		line[i].s)^(line[i].e-line[i].s))>eps)
			tail--;
		while(head<tail&&(((Q[head]&Q[head+1])-
		line[i].s)^(line[i].e-line[i].s))>eps)
			head++;
		Q[++tail]=line[i];
	}
	while(head<tail&&(((Q[tail]&Q[tail-1])-
	Q[head].s)^(Q[head].e-Q[head].s))>eps)
		tail--;
	while(head<tail&&(((Q[head]&Q[head-1])-
	Q[tail].s)^(Q[tail].e-Q[tail].e))>eps)
		head++;
	if(tail<=head+1)return;
	for(int i=head;i<tail;i++)
		res[resn++]=Q[i]&Q[i+1];
	if(head<tail-1)
		res[resn++]=Q[head]&Q[tail];//凸包的形式表示半平面交
}