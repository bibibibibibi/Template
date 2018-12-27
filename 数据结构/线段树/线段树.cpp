const int MAXN=1e5+5;
template<typename Tp>
struct seg
{
	#define lson l,mid,rt<<1
	#define rson mid+1,r,rt<<1|1
	#define root l,r,rt
	struct node
	{
		Tp sum,lazy;
		void init()
		{
			sum=0;lazy=0;
		}
	}tr[MAXN<<2];
	void add(int &x,int y){x=(x+y);}
	void mul(int &x,int y){x=(1LL*x*y);}
	inline void push_up(int rt)
	{
		tr[rt].sum=tr[rt<<1].sum+tr[rt<<1|1].sum;
	}
	inline void push_down(int l,int r,int rt)
	{
		if(tr[rt].lazy)
		{
			int mid=(l+r)>>1;
			tr[rt<<1].sum+=(mid-l+1)*tr[rt].lazy;
			tr[rt<<1|1].sum+=(r-mid)*tr[rt].lazy;
			tr[rt<<1].lazy+=tr[rt].lazy;
			tr[rt<<1|1].lazy+=tr[rt].lazy;
			tr[rt].lazy=0;
		}
	}
	void build(int l,int r,int rt)
	{
		tr[rt].init();
		if(l==r) return;
		int mid=(l+r)>>1;
		build(lson);
		build(rson);
		push_up(rt);
	}
	void update(int pos,Tp val,int l,int r,int rt)
	{
		if(l==r)
		{
			tr[rt].sum=val;
			return ;
		}
		push_down(l,r,rt);
		int mid=(l+r)>>1;
		if(pos<=mid)
			update(pos,val,lson);
		if(mid<pos)
			update(pos,val,rson);
		push_up(rt);
	}
	void update(int L,int R,Tp val,int l,int r,int rt)
	{
		if(L>R) return ;
		if(L<=l&&r<=R)
		{
			tr[rt].sum+=(r-l+1)*val;
			tr[rt].lazy+=val;
			return ;
		}
		push_down(l,r,rt);
		int mid=(l+r)>>1;
		if(L<=mid)
			update(L,R,val,lson);
		if(mid<R)
			update(L,R,val,rson);
		push_up(rt);
	}
	Tp query(int L,int R,int l,int r,int rt)
	{
		if(L>R) return 0;
		if(L<=l&&r<=R)
			return tr[rt].sum;
		push_down(l,r,rt);
		int mid=(l+r)>>1;
		Tp ret=0;
		if(L<=mid)
			ret+=query(L,R,lson);
		if(mid<R)
			ret+=query(L,R,rson);
		return ret;
	}
};
