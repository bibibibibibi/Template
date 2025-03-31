struct DSU
{
    int fa[MAXN];
    void init(int n)
    {
        for(int i=1;i<=n;i++) fa[i]=i;
    }
    int Find(int x)
    {
        return x==fa[x]?x:fa[x]=Find(fa[x]);
    }
    bool Union(int x,int y)
    {
        x=Find(x),y=Find(y);
        if(x==y) return 0;
        return fa[x]=y,1;
    }
};
