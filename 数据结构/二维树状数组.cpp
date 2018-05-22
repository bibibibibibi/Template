//v1:(×îÖµ)
const int maxn=3e2+10, INF=0x3f3f3f3f;
struct BIT
{
    int n;
    int bit[maxn][maxn];
    int tim[maxn][maxn];
    void init(int tn)
    {
        n=tn;
        memset(bit,0x3f,sizeof(bit));
        memset(tim,0,sizeof(tim));
    }
    void update(int nt,int x,int y,int val)
    {
        for(int i=x;i<=n;i+=i&-i)
            for(int j=y;j<=n;j+=j&-j)
            {
                if(tim[i][j]!=nt)
                {
                    tim[i][j]=nt;
                    bit[i][j]=INF;
                }
                bit[i][j]=min(bit[i][j],val);
            }
    }
    int query(int nt,int x,int y)
    {
        int res=INF;
        for(int i=x;i>0;i-=i&-i) 
            for(int j=y;j>0;j-=j&-j)
            {
                if(tim[i][j]==nt)
                    res=min(res,bit[i][j]);
            }
        return res;
    }
};

//
struct BIT
{
	ll d[MAXN][MAXN];
	int lowbit(int x)
	{
	    return x&(-x);
	}
	void update(int x,int y,int w)
	{
	    for(int i=x;i<MAXN;i+=lowbit(i))
	        for(int j=y;j<MAXN;j+=lowbit(j))
	            d[i][j]+=w;
	}
	ll get(int x,int y)
	{
	    long long ans=0;
	    for(int i=x;i;i-=lowbit(i))
	        for(int j=y;j;j-=lowbit(j))
	            ans+=d[i][j];
	    return ans;
	}
}B;
