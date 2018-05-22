//v1:(×îÖµ)
const int MAXN=3e2+10;
const int INF=0x3f3f3f3f;
template<typename Tp>
struct BIT
{
    int n;
    Tp bit[MAXN][MAXN];
    void init(int _n)
    {
        n=_n;
        memset(bit,0x3f,sizeof(bit));
    }
    void update(int x,int y,Tp val)
    {
        for(int i=x;i<=n;i+=i&-i)
            for(int j=y;j<=n;j+=j&-j)
            {
                bit[i][j]=min(bit[i][j],val);
            }
    }
    Tp query(int x,int y)
    {
        Tp res=INF;
        for(int i=x;i>0;i-=i&-i) 
            for(int j=y;j>0;j-=j&-j)
            {
                res=min(res,bit[i][j]);
            }
        return res;
    }
};

//
template<typename Tp>
struct BIT
{
	Tp d[MAXN][MAXN];
	int lowbit(int x)
	{
	    return x&(-x);
	}
	void update(int x,int y,Tp w)
	{
	    for(int i=x;i<MAXN;i+=lowbit(i))
	        for(int j=y;j<MAXN;j+=lowbit(j))
	            d[i][j]+=w;
	}
	Tp get(int x,int y)
	{
	    Tp ans=0;
	    for(int i=x;i;i-=lowbit(i))
	        for(int j=y;j;j-=lowbit(j))
	            ans+=d[i][j];
	    return ans;
	}
};
