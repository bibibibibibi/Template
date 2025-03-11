struct DSU
{
	stack<pair<int, int> > stk;
	int fa[MAXN],sz[MAXN];
	void init(int n)
	{
		for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;
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
		stk.push(make_pair(y,fa[y]));
		fa[y]=x;
		stk.push(make_pair(-x,sz[x]));
		sz[x]+=sz[y];
	}
	void undo(int T)
	{
		while(stk.size()>T)
		{
			int x=stk.top().first,y=stk.top().second;
			if(x>0) fa[x]=y;
			else sz[-x]=y;
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
