//1.10 判断点在凸多边形内 
//*判断点在凸多边形内 
//点形成一个凸包，而且按逆时针排序（如果是顺时针把里面的<0改为>0） 
//点的编号:0~n-1 
//返回值： 
//-1:点在凸多边形外 
//0:点在凸多边形边界上 
//1:点在凸多边形内 
int inConvexPoly(Point a,Point p[],int n)
{
	for(int i=0;i<n;i++)
	{
		if(sgn((p[i]-a)^(p[(i+1)%n]-a)) < 0)return -1;
		else if(OnSeg(a,Line(p[i],p[(i+1)%n])))return 0;
	}
	return 1;
}
