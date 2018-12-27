/* 
 * 给出一个序列，查询区间内有多少个不相同的数 
 */ 
//保存所有版本的线段树--主席树
const int MAXN=30010;
const int M=MAXN*100;
int a[MAXN];
template<typename Tp>
struct seg
{
	#define lson l,mid
	#define rson mid+1,r
	int tot;
	int T[MAXN];
	struct node
	{
		int ls,rs;
		Tp sum;
		void init()
		{
			sum=0;
		}
	}tr[M];
	void init()
	{
		tot=0;
	}
	int newnode()
	{
		return tot++;
	}
	int build(int l,int r)
	{
		int rt=newnode();
		tr[rt].init();
		if(l==r) return rt;
		int mid=(l+r)>>1;
		tr[rt].ls=build(lson);
		tr[rt].rs=build(rson);
		return rt;
	}
	int update(int pos,Tp val,int l,int r,int rt)
	{
		int nrt=newnode();
		tr[nrt].sum=tr[rt].sum+val;
		if(l==r) return nrt;
		int mid=(l+r)>>1;
		if(mid>=pos)
		{
			tr[nrt].rs=tr[rt].rs;
			tr[nrt].ls=update(pos,val,lson,tr[rt].ls);
		}
		if(mid<pos)
		{
			tr[nrt].ls=tr[rt].ls;
			tr[nrt].rs=update(pos,val,rson,tr[rt].rs);
		}
		return nrt;
	}
	Tp query(int L,int R,int l,int r,int rt)
	{
		if(L<=l&&r<=R) return tr[rt].sum;
		int mid=(l+r)>>1;
		Tp ret=0;
		if(L<=mid) ret+=query(L,R,lson,tr[rt].ls);
		if(mid<R) ret+=query(L,R,rson,tr[rt].rs);
		return ret;
	}
};
seg<int> se;
int main()
{
	//freopen("in.txt","r",stdin); 
	//freopen("out.txt","w",stdout); 
	while(scanf("%d",&n) == 1)
	{
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		se.T[n+1]=se.build(1,n);
		map<int,int> mp;
		for(int i=n;i>=1;i--)
		{
			if(mp.find(a[i])==mp.end())
			{
				se.T[i]=se.update(i,1,1,n,se.T[i+1]);
			}
			else
			{
				int tmp=se.update(mp[a[i]],-1,1,n,se.T[i+1]);
				se.T[i]=se.update(i,1,1,n,tmp);
			}
			mp[a[i]]=i;
		}
		scanf("%d",&q);
		while(q--)
		{
			int l,r;
			scanf("%d%d",&l,&r);
			printf("%d\n",se.query(l,r,1,n,se.T[l]));
		}
	}
	return 0;
}

