//1.9 判断点在线段上 
//*判断点在线段上 
bool OnSeg(Point P,Line L) 
{
    return
    sgn((L.s-P)^(L.e-P))==0 && 
    sgn((P.x-L.s.x)*(P.x-L.e.x))<=0 && 
    sgn((P.y-L.s.y)*(P.y-L.e.y))<=0; 
}
