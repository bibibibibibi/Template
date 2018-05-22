struct Bit
{
    vector<int> a;
    int sz;
    void init(int n)
    {
        sz=n;
        for(int i=1;i<=n+5;i++)
            a.push_back(0);
    }
    int lowbit(int x)
    {
        return x&(-x);
    }
    int query(int x)
    {
        int ans=0;
        for(;x;x-=lowbit(x))ans+=a[x];
        return ans;
    }
    void update(int x,int v)
    {
        for(;x<=sz;x+=lowbit(x))
            a[x]+=v;
    }
}bit;
