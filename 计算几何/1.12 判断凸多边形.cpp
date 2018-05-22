//1.12 判断凸多边形 
//判断凸多边形 
//允许共线边 
//点可以是顺时针给出也可以是逆时针给出 
//点的编号1~n-1 
bool isconvex(Point poly[],int n)
{
	bool s[3];
	memset(s,false,sizeof(s));
	for(int i=0;i<n;i++)
	{
		s[sgn((poly[(i+1)%n]-poly[i])^(poly[(i+2)%n]-poly[i]))+1]=true;
		if(s[0]&&s[2])return false;
	}
	return true;
}
