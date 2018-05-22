//1.5 判断：直线和线段相交 
bool Seg_inter_line(Line l1,Line l2) //判断直线l1和线段l2是否相交 
{
	return sgn((l2.s-l1.e)^(l1.s-l1.e))*sgn((l2.e-l1.e)^(l1.s-l1.e))<=0;
}
