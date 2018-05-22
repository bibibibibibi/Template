//http://blog.csdn.net/u013368721/article/details/52983102
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair <ll,int> pli;
typedef pair <int,int> pii;
#define clr(a,x) memset(a,x,sizeof a)
#define st first
#define ed second
const int MAXN=150005;
const int MAXE=300005;
const ll INF=1e18;
namespace Leftist_Tree 
{
    struct Node 
    {
        int l,r,x,h;
        ll val;
    }T[MAXN*40];
    int Root[MAXN],node_num ;
    int newnode(const Node &o) 
    {
        T[node_num]=o;
        return node_num++;
    }
    void init() 
    {
        node_num=1;
        T[0].l=T[0].r=T[0].x=T[0].h=0;
        T[0].val=INF;
    }
    int merge(int x,int y) 
    {
        if(!x) 
            return y;
        if(T[x].val>T[y].val) 
            swap(x,y);
        int o=newnode(T[x]);
        T[o].r=merge(T[o].r,y);
        if(T[T[o].l].h<T[T[o].r].h) 
            swap(T[o].l,T[o].r);
        T[o].h=T[T[o].r].h+1;
        return o;
    }
    void insert(int& x,ll val,int v) 
    {
        int o=newnode(T[0]);
        T[o].val=val,T[o].x=v;
        x=merge(x,o);
    }
}
using namespace Leftist_Tree;
vector<pii> G[MAXN],E[MAXN];
int vis[MAXN];
int in[MAXN];
int p[MAXN];ll d[MAXN];
int s,t;
int n,k;
void addedge(int u,int v,int c) 
{
    G[u].push_back(pii(v,c));
    E[v].push_back(pii(u,c));
    in[u]++;
}
void topo()
{
    queue<int> q;
    q.push(t);
    d[t]=p[t]=0 ;
    while(!q.empty()) 
    {
        int u=q.front();
        q.pop();
        for (int i=0;i<E[u].size();i++)
        {
            int v=E[u][i].st,c=E[u][i].ed;
            if(d[v]>d[u]+c) 
            {
                d[v]=d[u]+c;
                p[v]=u;
            }
            if(0==--in[v]) 
                q.push(v);
        }
    }
}
void dfs(int u) 
{
    if(vis[u]) 
        return;
    vis[u]=1;
    if(p[u]) 
        Root[u]=Root[p[u]];
    for(int i=0;i<G[u].size();i++)
    {
        int v=G[u][i].st;
        if(d[v]==INF||p[u]==v) 
            continue;
        insert(Root[u],d[v]-d[u]+G[u][i].ed,v);
    }
    for(int i=0;i<E[u].size();i++) 
    {
        if(p[E[u][i].st]==u) 
            dfs(E[u][i].st);
    }
}
void solve()
{
    scanf("%d%d",&n,&k);
    s=n+1;
    t=3*n+1;
    for(int i=1;i<=t;++i)
    {
        in[i]=vis[i]=0 ;
        G[i].clear();
        E[i].clear();
        d[i]=INF;
    }
    for(int i=1;i<=n;i++) 
    {
        int x,y,c;
        scanf("%d%d%d",&x,&y,&c);
        addedge(i+n,i,-x);
        addedge(i+n+n,i,-y);
        if(i<n) 
        {
            addedge(i+n,i+n+1,0);
            addedge(i+n+n,i+n+n+1,0);
            if(!c) 
                addedge(i,i+n+1,0);
            else 
                addedge(i,i+n+n+1,0);
        }
    }
    addedge(n*1,t,0);
    addedge(n*2,t,0);
    addedge(n*3,t,0);
    topo();
    if(k==1)
    {
        printf("lld\n",-d[s]);
        return ;
    }
    init();
    Root[t]=0;
    dfs(t);
    priority_queue<pli,vector<pli>,greater<pli>> q;
    if(Root[s]) 
        q.push(pli(d[s]+T[Root[s]].val,Root[s]));
    while(k--)
    {
        pli u=q.top();
        q.pop();
        if(k==1) 
        {
            printf(" lld\n",-u.st);
            return ;
        }
        int x=T[u.ed].l,y=T[u.ed].r,v=T[u.ed].x;
        if(Root[v]) 
            q.push( pli(u.st+T[Root[v]].val,Root[v]));
        if(x) 
            q.push(pli(u.st+T[x].val-T[u.ed].val,x));
        if(y)
            q.push(pli(u.st+T[y].val-T[u.ed].val,y));
    }
}
int main()
{
    int T;
    scanf( "%d",&T);
    while(T--) 
        solve();
    return 0;
}