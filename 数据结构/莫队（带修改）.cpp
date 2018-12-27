namespace MO
{
    const int MAXN=10005;
    const int MAXM=10005;
    const int MAXC=1000005;
    const int BLK=250;

    struct Q
    {
        int l,r,t,id;
        Q(int _l=0,int _r=0,int _t=0,int _id=0):l(_l),r(_r),t(_t),id(_id){}
    }Query[MAXM];

    struct E
    {
        int x,u,v;
        E(int _x=0,int _u=0,int _v=0):x(_x),u(_u),v(_v){}
    }Modify[MAXM];

    int co[MAXN],ct[MAXN],be[MAXN];
    int n,m,q,e,now;
    int ans[MAXM];
    int cnt[MAXC];

    bool operator < (Q x,Q y)
    {
        return be[x.l]<be[y.l]||
            be[x.l]==be[y.l]&&
            ((be[x.r]<be[y.r])||
            be[x.r]==be[y.r]&&x.t<y.t);
    }

    void add(int x)
    {
        now+=!(cnt[co[x]]++);
    }

    void erase(int x)
    {
        now-=!(--cnt[co[x]]);
    }

    void change(int x,int l,int r,bool tp)
    {
        int y=Modify[x].x;
        if(l<=y&&y<=r) 
            erase(y);
        co[y]=tp?Modify[x].v:Modify[x].u;
        if(l<=y&&y<=r) 
            add(y);
    }

    void solve()
    {
        now=0;
        int lcur=1,rcur=0,mcur=0;
        for(int i=1;i<=q;i++)
        {
            while(lcur<Query[i].l) erase(lcur++);
            while(Query[i].l<lcur) add(--lcur);
            while(Query[i].r<rcur) erase(rcur--);
            while(rcur<Query[i].r) add(++rcur);
            while(mcur<Query[i].t) change(++mcur,lcur,rcur,1);
            while(Query[i].t<mcur) change(mcur--,lcur,rcur,0);
            ans[Query[i].id]=now;
        }
    }
}
//bzoj2453
//区间中有多少个不同的颜色，带修改
using namespace MO;
char op[2];
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    while(~scanf("%d%d",&n,&m))
    {
        q=e=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&co[i]);
            ct[i]=co[i];be[i]=(i-1)/BLK;
        }
        for(int i=1;i<=m;i++)
        {
            scanf("%s",op);
            if(op[0]=='Q')
            {
                int L,R;
                scanf("%d%d",&L,&R);
                Query[++q]=Q(L,R,e,q);
            }
            else if(op[0]=='R')
            {
                int x,c;
                scanf("%d%d",&x,&c);
                Modify[++e]=E(x,ct[x],c);ct[x]=c;
            }
        }
        sort(Query+1,Query+1+q);
        solve();
        for(int i=1;i<=q;i++)
        {
            printf("%d\n",ans[i]);
        }
    }
    return 0;
}