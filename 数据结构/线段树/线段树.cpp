const int MAXN=1e5+5;
template<typename Tp>
struct seg
{
	#define lson l,mid,rt<<1
	#define rson mid+1,r,rt<<1|1
	#define root l,r,rt
	Tp tr[MAXN<<2],lazy[MAXN<<2];
	inline void push_up(int rt)
	{
		tr[rt]=tr[rt<<1]+tr[rt<<1|1];
	}
	inline void push_down(int rt)
	{
		if(lazy[rt])
		{
			tr[rt<<1]+=lazy[rt];
			tr[rt<<1|1]+=lazy[rt];
			lazy[rt<<1]+=lazy[rt];
			lazy[rt<<1|1]+=lazy[rt];
			lazy[rt]=0;
		}
	}
	void build(int l,int r,int rt)
	{
		tr[rt]=0;
		lazy[rt]=0;
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
			tr[rt]=val;
			return ;
		}
		push_down(rt);
		int mid=(l+r)>>1;
		if(pos<=mid)
			update(pos,val,lson);
		if(mid<pos)
			update(pos,val,rson);
		push_up(rt);
	}
	void update(int L,int R,Tp val,int l,int r,int rt)
	{
		if(L<=l&&r<=R)
		{
			tr[rt]+=val;
			lazy[rt]+=val;
			return ;
		}
		push_down(rt);
		int mid=(l+r)>>1;
		if(L<=mid)
			update(L,R,val,lson);
		if(mid<R)
			update(L,R,val,rson);
		push_up(rt);
	}
	Tp query(int L,int R,int l,int r,int rt)
	{
		if(L<=l&&r<=R)
			return tr[rt];
		push_down(rt);
		int mid=(l+r)>>1;
		Tp ret=0;
		if(L<=mid)
			ret+=query(L,R,lson);
		if(mid<R)
			ret+=query(L,R,rson);
		return ret;
	}
};
