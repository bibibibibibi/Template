struct UFS
{
	
	stack<pair<int, int> > stk;
	int fa[MAXN],sz[MAXN];
	void init(int n)
	{
		for(int i=0;i<=n;i++) fa[i]=i,sz[i]=1;
	}
	int Find(int x)
	{
		while(x!=fa[x]) x=fa[x];
		return x;
	}
	void merge(int x,int y)
	{
		x=Find(x),y=Find(y);
		if(x==y) return ;
		if(sz[x]<sz[y]) swap(x,y);
		stk.push({y,fa[y]});
		fa[y]=x;
		sz[x]+=sz[y];
	}
	void undo(int x)
	{
		while(stk.size()>x)
		{
			fa[stk.top().first]=stk.top().second;
			sz[stk.top().second]-=sz[stk.top().first];
			stk.pop();
		}
		
	}
	int size(int x)
	{
		return sz[Find(x)];
	}
	int history()
	{
		return stk.size();
	}
};
