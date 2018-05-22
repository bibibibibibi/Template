const int MAXN=1e5+5;
template<typename Tp>
struct Bit
{
    Tp bit[MAXN];
    int sz;
    void init(int n)
    {
        sz=n;
        memset(bit,0,sizeof(bit))
    }
    int lowbit(int x)
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
}bit;
