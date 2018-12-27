namespace convex_hull
{
	/*
	* 求凸包，Graham算法
	* 点的编号0~n-1
	* 返回凸包结果Stack[0~top-1]为凸包的编号
	*/
	const int MAXN=1010;
	const double eps=1e-8; 
	const double PI=acos(-1.0);
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
		Point operator - (const Point &b)const
		{
			return Point(x-b.x,y-b.y); 
		}
		double operator ^ (const Point &b)const//叉积
		{
			return x*b.y-y*b.x;
		}
		double operator * (const Point &b)const//点积
		{
			return x*b.x+y*b.y;
		}
	};
	Point p[MAXN];
	int Stack[MAXN],top;
	double dist(Point a,Point b) 
	{ 
	    return sqrt((a-b)*(a-b)); 
	}
	//相对于p[0]的极角排序
	bool _cmp(Point p1,Point p2)
	{
		double tmp=(p1-p[0])^(p2-p[0]);
		if(sgn(tmp)>0)
			return true;
		else if(sgn(tmp)==0&&sgn(dist(p1,p[0])-dist(p2,p[0]))<=0)
			return true;
		else
			return false;
	}
	void Graham(int n)
	{
		Point p0;
		int k=0;
		p0=p[0];
		//找最下边的一个点
		for(int i=1;i<n;i++)
		{
			if((p0.y>p[i].y)||(sgn(p0.y-p[i].y)==0&&p0.x>p[i].x))
			{
				p0=p[i];k=i;
			}
		}
		swap(p[k],p[0]);
		sort(p+1,p+n,_cmp);
		if(n==1)
		{
			top=1;Stack[0]=0;
			return ;
		}
		if(n==2)
		{
			top=2;Stack[0]=0;Stack[1]=1;
			return ;
		}
		Stack[0]=0;Stack[1]=1;top=2;
		for(int i=2;i<n;i++)
		{
			while(top>1&&sgn((p[Stack[top-1]]-p[Stack[top-2]])^(p[i]-p[Stack[top-2]]))<=0)
				top--;
			Stack[top++]=i;
		}
	}
}
