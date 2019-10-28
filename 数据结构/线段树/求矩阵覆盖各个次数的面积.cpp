#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=100005;
const ll INF=2000000000LL;
ll res[MAXN],xx[MAXN<<1],cnt[MAXN<<1],la[MAXN<<1];
struct Event
{
    ll l,r,y,v;
    Event(){}
    Event(ll _l,ll _r,ll _y,ll _v):l(_l),r(_r),y(_y),v(_v){}
    bool operator < (const Event &t)const
    {
        return y<t.y;
    }
}e[MAXN<<1];
int main()
{
    int n,k;
    scanf("%d%d",&n,&k);
    int tot=0;
    xx[tot++]=-INF;
    for(int i=0;i<n;i++)
    {
        ll x,y;
        scanf("%I64d%I64d",&x,&y);
        xx[tot++]=x;
        xx[tot++]=x+k;
        e[i<<1]=Event(x,x+k,y,1);
        e[i<<1|1]=Event(x,x+k,y+k,-1);
    }
    sort(xx,xx+tot);
    tot=unique(xx,xx+tot)-xx;
    sort(e,e+2*n);
    for(int i=0;i<tot;i++)
        la[i]=-INF;
    for(int i=0;i<2*n;i++)
    {
        int l=upper_bound(xx,xx+tot,e[i].l)-xx;
        int r=lower_bound(xx,xx+tot,e[i].r)-xx;
        for(int j=l;j<=r;j++)
        {
            res[cnt[j]]+=(xx[j]-xx[j-1])*(e[i].y-la[j]);
            cnt[j]+=e[i].v;
            la[j]=e[i].y;
        }
    }
    for(int i=1;i<=n;i++)
        printf("%I64d ",res[i]);
    return 0;
}
