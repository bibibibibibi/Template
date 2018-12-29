const int MAXN=1e5+5;
template<typename Tp>
struct BIT
{
    Tp a[MAXN];
    int sz;
    void init(int n)
    {
        sz=n;
        memset(a,0,sizeof(a));
    }
    inline int lowbit(int x)
    {
        return x&(-x);
    }
    Tp query(int x)
    {
        Tp ans=0;
        for(;x;x-=lowbit(x))ans+=a[x];
        return ans;
    }
    void update(int x,Tp v)
    {
        for(;x<=sz;x+=lowbit(x))
            a[x]+=v;
    }
};
