//1.8 计算多边形面积 
//计算多边形面积 
//点的编号从0~n-1 
double CalcArea(Point p[],int n)
{
    double res=0;
	for(int i=0;i<n;i++) 
        res+=(p[i]^p[(i+1)%n])/2; 
    return fabs(res);
}
