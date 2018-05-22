typedef double db;
const db PI=acos(-1.0);
db get(db l,int n)//边长,正n面体
{
    db r=l/2/sin(PI/n);
    db h=sqrt(l*l-r*r);
    return n*r*r*sin(2*PI/n)/2*h/3;
}
