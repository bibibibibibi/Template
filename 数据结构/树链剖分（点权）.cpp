#include<bits/stdc++.h>
namespace Tree_chain
{
	typedef long long ll;
	const int MAXN=1e5+5;
	int cnt,tot;
	struct Edge
	{
		int v,nxt;
	}E[MAXN*2];
	int head[MAXN];
	inline void addedge(int u,int v) 
	{
		E[tot].v=v;E[tot].nxt=head[u];head[u]=tot++;
		E[tot].v=u;E[tot].nxt=head[v];head[v]=tot++;
	}
	ll sumv[MAXN<<2],addv[MAXN<<2];
	ll plc[MAXN<<2];
	void pushup(int o) 
	{
		sumv[o]=sumv[o<<1]+sumv[o<<1|1];
	}
	void paint(int o,int L,int R,ll v)
	{
		sumv[o]+=(ll(R-L+1))*v;
		addv[o]+=v;
	}
	void pushdown(int o,int L,int R)
	{
		if(addv[o]!=0LL) 
		{
			int M=(L+R)>>1;
			paint(o<<1,L,M,addv[o]);
			paint(o<<1|1,M+1,R,addv[o]);
			addv[o]=0;
		}
	}
	void build_tree(int o,int L,int R)
	{
		addv[o]=0;
		if(L==R)
			sumv[o]=plc[L];
		else 
		{
			int M=(L+R)>>1;
			build_tree(o<<1,L,M);
			build_tree(o<<1|1,M+1,R);
			pushup(o);
		}
	}
	ll query(int o,int L,int R,int ql,int qr) 
	{
		if(ql<=L&&R<=qr)
			return sumv[o];
		else 
		{
			int M=(L+R)>>1;
			pushdown(o,L,R);
			ll ans=0;
			if(ql<=M) ans+=query(o<<1,L,M,ql,qr);
			if(qr>M) ans+=query(o<<1|1,M+1,R,ql,qr);
			return ans;
		}
	}
	void update(int o,int L,int R,int ql,int qr,ll v) 
	{
		if(ql<=L&&R<=qr)
			paint(o,L,R,v);
		else 
		{
			int M=(L+R)>>1;
			pushdown(o,L,R);
			if(ql<=M) update(o<<1,L,M,ql,qr,v);
			if(qr>M) update(o<<1|1,M+1,R,ql,qr,v);
			pushup(o);
		}
	}

	int anc[MAXN][19];
	int siz[MAXN],dep[MAXN],hson[MAXN];
	void dfs_1(int x,int fa=-1,int depth=0) 
	{
		siz[x]=1;dep[x]=depth;anc[x][0]=fa;hson[x]=0;
		int max_siz=0;
		for(int i=head[x];~i;i=E[i].nxt)
		{
			int v=E[i].v;
			if(v!=fa) 
			{
				dfs_1(v,x,depth+1);
				siz[x]+=siz[v];
				if(siz[v]>max_siz) 
				{
					max_siz=siz[v];hson[x]=v;
				}
			}
		}
	}
	int top[MAXN],tid[MAXN],dfn[MAXN];ll A[MAXN];
	void dfs_2(int x,int a=1)
	{
		cnt++;
		dfn[x]=cnt;tid[cnt]=x;plc[cnt]=A[x];top[x]=a;
		if(hson[x]) dfs_2(hson[x],a);
		else return;
		for(int i=head[x];~i;i=E[i].nxt)
		{
			int v=E[i].v;
			if(v!=anc[x][0]&&v!=hson[x]) 
				dfs_2(v,v);
		}
	}
	int n;
	void process() 
	{
		memset(anc,-1,sizeof(anc));
		dfs_1(1);dfs_2(1);build_tree(1,1,n);
		for(int j=1;(1<<j)<n;j++) 
		{
			for(int i=1;i<=n;i++) 
			{
				int a=anc[i][j-1];
				if(a!=-1) anc[i][j]=anc[a][j-1];
			}
		}
	}
	int get_up(int v,int u)
	{
		for(int j=18;j>=0;j--) 
		{
			int a=anc[u][j];
			if(a!=-1&&dep[a]>dep[v]) u=a;
		}
		return u;
	}
	bool is_anc(int v,int u) 
	{
		for(int j=18;j>=0;j--) 
		{
			int a=anc[u][j];
			if(a!=-1&&dep[a]>=dep[v]) u=a;
		}
		return (u==v);
	}
	int now_rt;
	ll query_tree(int x) 
	{
		if(x==now_rt)
			return query(1,1,n,1,n);
		else
		{
			if(is_anc(x,now_rt)) 
			{
				int g=get_up(x,now_rt);
				return query(1,1,n,1,n)-query(1,1,n,dfn[g],dfn[g]+siz[g]-1);
			}
			else
			{
				return query(1,1,n,dfn[x],dfn[x]+siz[x]-1);
			}
		}
	}
	void update_tree(int x,ll v)
	{
		if(x==now_rt)
			update(1,1,n,1,n,v);
		else 
		{
			if(is_anc(x,now_rt))
			{
				int g=get_up(x,now_rt);
				update(1,1,n,1,n,v);
				update(1,1,n,dfn[g],dfn[g]+siz[g]-1,-v);
			} 
			else 
			{
				update(1,1,n,dfn[x],dfn[x]+siz[x]-1,v);
			}
		}
	}
	ll query_chain(int u,int v)
	{
		if(top[u]==top[v])
		{
			int l=dfn[u],r=dfn[v];
			if(l>r) std::swap(l, r);
			return query(1,1,n,l,r);
		}
		if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
		return query(1,1,n,dfn[top[u]],dfn[u])+query_chain(anc[top[u]][0],v);
	}
	void update_chain(int u,int v,ll delta)
	{
		if(top[u]==top[v]) 
		{
			int l=dfn[u],r=dfn[v];
			if(l>r) std::swap(l,r);
			update(1,1,n,l,r,delta);
			return;
		}
		if(dep[top[u]]<dep[top[v]]) std::swap(u,v);
		update(1,1,n,dfn[top[u]],dfn[u],delta);
	 	update_chain(anc[top[u]][0],v,delta);
	}
	void init()
	{
		cnt=tot=0;now_rt=1;
		memset(head,-1,sizeof(head));
	}
}
using namespace Tree_chain;

/*
换根：将一个指定的节点设置为树的新根。
修改路径权值：给定两个节点，将这两个节点间路径上的所有节点权值（含这两个节点）增加一个给定的值。
修改子树权值：给定一个节点，将以该节点为根的子树内的所有节点权值增加一个给定的值。
询问路径：询问某条路径上节点的权值和。
询问子树：询问某个子树内节点的权值和。

若类型为 1，则接下来一个整数 u，表示新根的编号。
若类型为 2，则接下来三个整数 u,v,k，分别表示路径两端的节点编号以及增加的权值。
若类型为 3，则接下来两个整数 u,k，分别表示子树根节点编号以及增加的权值。
若类型为 4，则接下来两个整数 u,v，表示路径两端的节点编号。
若类型为 5，则接下来一个整数 u，表示子树根节点编号。
*/

int main() 
{
	init();
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld", &A[i]);
	for(int i=2;i<=n;i++)
	{
		int f;
		scanf("%d",&f);
		addedge(i,f);
	}
	process();
	int q;
	scanf("%d",&q);
	while(q--) 
	{
		int op,u;
		scanf("%d%d",&op,&u);
		if(op==1) 
		{
			now_rt=u;
		} 
		else if(op==2)
		{
			int v;ll k;
			scanf("%d%lld",&v,&k);
			update_chain(u,v,k);
		} 
		else if(op==4)
		{
			int v;
			scanf("%d",&v);
			printf("%lld\n",query_chain(u,v));
		}
		else if(op==3)
		{
			ll k;
			scanf("%lld",&k);
			update_tree(u,k);
		} 
		else if(op==5)
		{
			printf("%lld\n",query_tree(u));
		}
	}
	return 0;
}