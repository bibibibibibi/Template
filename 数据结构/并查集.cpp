int par[MAXN],Rank[MAXN];

void init(int n)
{
    for(int i=0;i<n;i++)
    {
        par[i]=i;
        Rank[i]=0;
    }
}

int find(int x)
{
    if(par[x]==x)
        return x;
    else
        return par[x]=find(par[x]);
}

void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y)
        return;
    if(Rank[x]<Rank[y])
        par[x]=y;
    else
    {
        par[y]=x;
        if(Rank[x]==Rank[y])
            Rank[x]++;
    } 
}

bool same(int x,int y)
{
    return find(x)==find(y);
}

//Q
namespace DSU
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
}


