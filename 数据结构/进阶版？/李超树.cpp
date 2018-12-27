//维护区间最上面的那条直线
const int MAXN=1e5+5;
template<typename T>
struct seg
{
	#define lson l,mid,rt<<1
	#define rson mid+1,r,rt<<1|1
	struct node
	{
		T a,b;
		int id;
		node(T _a=0,T _b=0,int _id=0):a(_a),b(_b),id(_id){}
		void init(){a=b=id=0;}
	}tr[MAXN<<2];
	bool judge(int x,int rt,node o)
	{
		return tr[rt].a*x+tr[rt].b<o.a*x+o.b;
	}
	void build(int l,int r,int rt)
	{
		tr[rt].init();
		if(l==r)
		{
			return ;
		}
		int mid=(l+r)>>1;
		build(lson);
		build(rson);
	}
	void update(T a,T b,int id,int l,int r,int rt)
	{
		node o=node(a,b,id);
		int mid=(l+r)>>1;
		if(judge(mid,rt,o))
		{
			swap(o,tr[rt]);
		}
		if(l==r) return ;
		if(judge(l,rt,o)||judge(mid,rt,o))
		{
			update(o.a,o.b,o.id,lson);
		}
		if(judge(mid+1,rt,o)||judge(r,rt,o))
		{
			update(o.a,o.b,o.id,rson);
		}
	}
	//返回线段树节点的id
	int query(int pos,int l,int r,int rt)
	{
		if(l==r)
		{
			return rt;
		}
		int mid=(l+r)>>1;
		int ret;
		if(mid>=pos) ret=query(pos,lson);
		if(mid<pos) ret=query(pos,rson);
		if(judge(pos,ret,tr[rt])) ret=rt;
		return ret;
	}
};
