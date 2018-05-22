//1.11 判断点在任意多边形内 
//*判断点在任意多边形内 
//射线法，poly[]的顶点数要大于等于3,点的编号0~n-1 
//返回值 
//-1:点在凸多边形外 
//0:点在凸多边形边界上 
//1:点在凸多边形内 
int inPoly(Point p,Point poly[],int n)
{
	int cnt;
	Line ray,side;
	cnt=0;
	ray.s=p;
	ray.e.y=p.y;
	ray.e.x=-100000000000.0;//-INF,注意取值防止越界 
	for(int i=0;i<n;i++)
	{
		side.s=poly[i];
		side.e=poly[(i+1)%n];
		if(OnSeg(p,side))return 0;
		//如果平行轴则不考虑 
		if(sgn(side.s.y-side.e.y)==0)
			continue;
		if(OnSeg(side.s,ray))
		{
			if(sgn(side.s.y-side.e.y)>0)cnt++;
		}
		else if(OnSeg(side.e,ray))
		{
			if(sgn(side.e.y-side.s.y)>0)cnt++;
		}
		else if(inter(ray,side))
		cnt++;
	}
	if(cnt%2==1)return 1;
	else return -1;
}
