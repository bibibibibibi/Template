struct UFS
{
	stack<pair<int*, int>> stk;
	int fa[MAXN],rnk[MAXN];
	inline void init(int n)
	{
		for(int i=0;i<=n;i++) fa[i]=i,rnk[i]=0;
	}
	inline int Find(int x)
	{
		while(x^fa[x]) x=fa[x];
		return x;
	}
	inline void Merge(int x,int y)
	{
		x=Find(x),y=Find(y);
		if(x==y) return ;
		if(rnk[x]<=rnk[y])
		{
			stk.push({fa+x,fa[x]});
			fa[x]=y;
			if(rnk[x]==rnk[y])
			{
				stk.push({rnk+y,rnk[y]});
				rnk[y]++;
			}
		}
		else
		{
			stk.push({fa+y,fa[y]});
			fa[y]=x;
		}
	}
	inline void Undo()
	{
		*stk.top().xx=stk.top().yy;
		stk.pop();
	}
};
