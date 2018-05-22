typedef long long ll;
struct Tri
{
    int ch[MAXN][2];
    int sz[MAXN][2];
    int tot;
    void init()
    {
        memset(ch,0,sizeof(ch));
        memset(sz,0,sizeof(sz));
        tot=2;
    }
    void insert(int x)
    {
        int u=1;
        for(int i=30;i>=0;i--)
        {
            int p=(x>>i)&1;
            if(!ch[u][p])ch[u][p]=tot++;
            sz[u][p]++;
            u=ch[u][p];
        }
    }
    void del(int x)
    {
        int p;
        int u=1;
        for(int i=30;i>=0;i--)
        {
            p=(x>>i)&1;
            sz[u][p]--;
            if(sz[u][p]==0)
                ch[u][p]=0;
            u=ch[u][p];
        }
    }
    ll get(int x)
    {
        int u=1;
        ll ans=0;
        for(int i=30;i>=0;i--)
        {
            int p=(x>>i)&1;
            if(ch[u][p^1])
            {
                ans^=1<<i;
                u=ch[u][p^1];
            }
            else
            {
                u=ch[u][p];
            }
        }
        return ans;
    }
}T;
