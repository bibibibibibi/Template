namespace NTT
{
    typedef long long ll;
    const ll MOD=998244353;
    const ll g=3;
    ll qpow(ll a,ll k)
    {
        ll res=1LL;
        while(k>0)
        {
            if(k&1)res=res*a%MOD;
            a=a*a%MOD;
            k>>=1;
        }
        return res;
    }
    void change(ll y[],int len)
    {
        for(int i=1,j=len/2;i<len-1;i++)
        {
            if(i<j)swap(y[i],y[j]);
            int k=len/2;
            while(j>=k)
            {
                j-=k;
                k/=2;
            }
            if(j<k)j+=k;
        }
    }
    void ntt(ll y[],int len,int on)
    {
        change(y,len);
        for(int h=2;h<=len;h<<=1)
        {
            ll wn=qpow(g,(MOD-1)/h);
            if(on==-1)wn=qpow(wn,MOD-2);
            for(int j=0;j<len;j+=h)
            {
                ll w=1LL;
                for(int k=j;k<j+h/2;k++)
                {
                    ll u=y[k];
                    ll t=w*y[k+h/2]%MOD;
                    y[k]=(u+t)%MOD;
                    y[k+h/2]=(u-t+MOD)%MOD;
                    w=w*wn%MOD;
                }
            }
        }
        if(on==-1)
        {
            ll t=qpow(len,MOD-2);
            for(int i=0;i<len;i++)
                y[i]=y[i]*t%MOD;
        }
    }
    void cal(ll x1[],ll x2[],int tot)
    {
        int len=1;
        while(len<2*tot)len<<=1;
        ntt(x1,len,1);
        ntt(x2,len,1);
        for(int i=0;i<len;i++)
            x1[i]=x1[i]*x2[i]%MOD;
        ntt(x1,len,-1);
    }
}
