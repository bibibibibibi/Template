/* 
 * 给出一个序列，查询区间内有多少个不相同的数 
 */ 
//保存所有版本的线段树--主席树
const int MAXN=30010;
const int M=MAXN*100;
int n,q,tot;
int a[MAXN];
int T[MAXN],lson[M],rson[M],c[M];
int build(int l,int r)
{
	int root=tot++;
	c[root]=0;
	if(l!=r)
	{
		int mid=(l+r)>>1;
		lson[root]=build(l,mid);
		rson[root]=build(mid+1,r);
	}
	return root;
}
int update(int root,int pos,int val)
{
	int newroot=tot++,tmp=newroot;
	c[newroot]=c[root]+val;
	int l=1,r=n;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			lson[newroot]=tot++;rson[newroot]=rson[root];
			newroot=lson[newroot];root=lson[root];
			r=mid;
		}
		else
		{
			rson[newroot]=tot++;lson[newroot]=lson[root];
			newroot=rson[newroot];root=rson[root];
			l=mid+1;
		}
		c[newroot]=c[root]+val;
	}
	return tmp;
}
//递归写查询好一点？
int query(int root,int pos)
{
	int ret=0;
	int l=1,r=n;
	while(pos<r)
	{
		int mid=(l+r)>>1;
		if(pos<=mid)
		{
			r=mid;
			root=lson[root];
		}
		else
		{
			ret+=c[lson[root]];
			root=rson[root];
			l=mid+1;
		}
	}
	return ret+c[root];
}
int main()
{
	//freopen("in.txt","r",stdin); 
	//freopen("out.txt","w",stdout); 
	while(scanf("%d",&n) == 1)
	{
		tot=0;
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		T[n+1]=build(1,n);
		map<int,int>mp;
		for(int i=n;i>=1;i--)
		{
			if(mp.find(a[i])==mp.end())
			{
				T[i]=update(T[i+1],i,1);
			}
			else
			{
				int tmp=update(T[i+1],mp[a[i]],-1);
				T[i]=update(tmp,i,1);
			}
			mp[a[i]]=i;
		}
		scanf("%d",&q);
		while(q--)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%d\n",query(T[l],r));
		}
	}
	return 0;
}
