void pri(ll x)//寻找x的所有素因子 
{
    for(ll i=2;i*i<=x;i++)
    {
        if(x%i==0) gcd.push_back(i);
        while(x%i==0) x=x/i;
    }
    if(x!=1) gcd.push_back(x);
    gcd.erase(unique(gcd.begin(),gcd.end()),gcd.end());//清除重复元素
}
