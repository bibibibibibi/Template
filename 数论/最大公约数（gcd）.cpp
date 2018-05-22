#include<bits/stdc++.h>
using namespace std;

int main()
{
	int x,y;
	scanf("%d%d",&x,&y);
	printf("%d\n",__gcd(x,y));
}

gcd(a^m-b^m,a^n-b^n)=a^(gcd(m,n))-b^(gcd(m,n))(a>b)//奇奇怪怪的gcd公式