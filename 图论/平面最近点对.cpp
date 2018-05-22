struct Point
{
    long long x,y;
    bool operator < (const Point &rhs) const
    {
        return x<rhs.x||(x==rhs.x&&y<rhs.y);
    }
};

typedef pair<long long, pair<int, int> > llii;

Point point[100000];
int tmpt[100000];


bool cmpy(const int &a, const int &b) { return point[a].y < point[b].y; }

llii dis(int i, int j)
{
    return make_pair((point[i].x-point[j].x)*(point[i].x-point[j].x)+(point[i].y-point[j].y)*(point[i].y-point[j].y),make_pair(i, j));
}

llii Closest_Pair(int left, int right)
{
    llii d=make_pair(INF,make_pair(-1, -1));
    if(left==right)
        return d;
    if(left+1==right)
        return dis(left, right);
    int mid=(left+right)>>1;
    llii d1=Closest_Pair(left,mid);
    llii d2=Closest_Pair(mid+1,right);
    d=min(d1,d2);
    int i,j,k=0;
    for(i=left;i<=right;i++)
    {
        if(abs(point[mid].x-point[i].x)<=d.first)
            tmpt[k++]=i;
    }
    sort(tmpt,tmpt+k,cmpy);
    for(i=0;i<k;i++)
    {
        for(j=i+1;j<k&&point[tmpt[j]].y-point[tmpt[i]].y<d.first;j++)
        {
            llii d3=dis(tmpt[i],tmpt[j]);
            if(d>d3)
                d=d3;
        }
    }
    return d;
}
//首先先按照x排序！！！！！然后再用