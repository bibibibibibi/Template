struct Point
{
	double x,y,z;
	Point(){}
	Point(double _x,double _y,double _z)
	{
		x=_x;y=_y;z=_z;
	}
	int input()
	{
		return scanf("%lf%lf%lf",&x,&y,&z); 
	}
	Point operator - (const Point b)const 
	{
		return Point((x-b.x),(y-b.y),(z-b.z));
	}
	double operator % (const Point b)const//两点距离 
	{
		return sqrt((x-b.x)*(x-b.x)+(y-b.y)*(y-b.y)+(z-b.z)*(z-b.z));
	}
	double operator * (const Point b)const//内积 
	{
		return (x*b.x)+(y*b.y)+(z*b.z);
	}
	Point operator ^ (const Point b)const//外积 
	{
		return Point((y*b.z-z*b.y),(z*b.x-x*b.z),(x*b.y-y*b.x));
	}
}a,b,c,d;
