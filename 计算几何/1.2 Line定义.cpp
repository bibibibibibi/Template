//1.2 Line定义
struct Line
{
	Point s,e;
	Line(){}
	Line(Point _s,Point _e):s(_s),e(_e){}
    //两直线相交求交点
    //第一个值为0表示直线重合，为1表示平行,为2是相交
    //只有第一个值为2时，交点才有意义
    pair<int,Point> operator &(const Line &b)const 
    { 
        Point res=s; 
        if(sgn((s-e)^(b.s-b.e))==0) 
        { 
            if(sgn((s-b.e)^(b.s-b.e))==0)
                return make_pair(0,res);//重合
            else return make_pair(1,res);//平行 
        } 
        double t=((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e)); 
        res.x+=(e.x-s.x)*t; 
        res.y+=(e.y-s.y)*t; 
        return make_pair(2,res); 
    } 
};
