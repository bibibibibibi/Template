#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN=1005;
ll a[MAXN],m[MAXN];
ll gcd(ll a,ll b)
{
    return b?gcd(b,a%b):a;
}

void extend_Euclid(ll a,ll b,ll &x,ll &y)
{
    if(b==0)
    {
        x=1;
        y=0;
        return;
    }
    extend_Euclid(b,a%b,x,y);
    ll tmp=x;
    x=y;
    y=tmp-(a/b)*y;
}

ll Inv(ll a,ll b)
{
    ll d=gcd(a,b);
    if(d!=1) return -1;
    ll x,y;
    extend_Euclid(a,b,x,y);
    return (x%b+b)%b;
}

bool merge(ll a1,ll m1,ll a2,ll m2,ll &a3,ll &m3)
{
    ll d=gcd(m1,m2);
    ll c=a2-a1;
    if(c%d) return false;
    c=(c%m2+m2)%m2;
    m1/=d;
    m2/=d;
    c/=d;
    c*=Inv(m1,m2);
    c%=m2;
    c*=m1*d;
    c+=a1;
    m3=m1*m2*d;
    a3=(c%m3+m3)%m3;
    return true;
}

ll CRT(ll a[],ll m[],int n)
{
    ll a1=a[1];
    ll m1=m[1];
    for(int i=2; i<=n; i++)
    {
        ll a2=a[i];
        ll m2=m[i];
        ll m3,a3;
        if(!merge(a1,m1,a2,m2,a3,m3))
            return -1;
        a1=a3;
        m1=m3;
    }
    return (a1%m1+m1)%m1;
}

int main()
{
    int n;
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=1;i<=n;i++)
            scanf("%I64d%I64d",&m[i],&a[i]);
        ll ans=CRT(a,m,n);
        printf("%I64d\n",ans);
    }
    return 0;
}
