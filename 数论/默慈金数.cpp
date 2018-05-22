#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
const long long int mod=1e9+7,maxn=1e6+5;
long long int f[maxn]={0,1},mo[maxn]={0};

int main()
{
	int i,T,n;
	for(i=2;i<=1000000;i++)
	{
		f[i]=(((mod-mod/i)%mod)*(f[mod%i]%mod))%mod;
	}
	mo[0]=1,mo[1]=1;
	for(i=2;i<=1000000;i++)
	{
		mo[i]=(((((2*i+1)*f[i+2])%mod)*mo[i-1])%mod+(((3*(i-1)*f[i+2])%mod)*mo[i-2])%mod)%mod;
	}
}
