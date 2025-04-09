struct Tri
{
    int ch[MAXN*32][2];
	int cnt[MAXN*32];
    int tot;
    void init()
    {
        memset(ch,0,sizeof(ch));
		memset(cnt,0,sizeof(cnt));
        tot=2;
    }
    void add(int x,int v)
    {
        int u=1;
        for(int i=30;i>=0;i--)
        {
            int p=(x>>i)&1;
            if(!ch[u][p])ch[u][p]=tot++;
            u=ch[u][p];
			cnt[u]+=v;
        }
    }
	int get(int x)
    {
        int u=1;
        int ans=0;
        for(int i=30;i>=0;i--)
        {
            int p=(x>>i)&1;
            if(cnt[ch[u][p^1]])
            {
				p^=1;
                ans^=1<<i;
            }
			u=ch[u][p];
        }
        return ans;
    }
}trie;
