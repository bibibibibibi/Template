//1.7 点到线段距离 
//点到线段的距离 
//返回点到线段最近的点 
Point NearestPointToLineSeg(Point P,Line L) 
{ 
    Point result; 
    double t=((P-L.s)*(L.e-L.s))/((L.e-L.s)*(L.e-L.s)); 
    if(t>=0&&t<=1) 
    {
       result.x=L.s.x+(L.e.x-L.s.x)*t;
       result.y=L.s.y+(L.e.y-L.s.y)*t;
    }
    else
    { 
        if(dist(P,L.s)<dist(P,L.e)) 
            result=L.s; 
        else result=L.e; 
    } 
    return result;
}
