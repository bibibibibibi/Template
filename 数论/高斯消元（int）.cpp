#include<bits/stdc++.h>
using namespace std;
const int MOD=3;
const int MAXN=1005;
int a[MAXN][MAXN];
int sv[MAXN],x[MAXN];
int Gauss(int equ,int var)
{
	int row,max_r,col;
	for(row=0,col=0;col<var&&row<equ;col++,row++)
	{
		max_r=row;
		for(int i=row+1;i<equ;i++)
		{
			if(abs(a[i][col])>abs(a[max_r][col]))
			{
				max_r=i;
			}
		}
		if(!a[max_r][col])
		{
			row--;
			continue;
		}
		if(row!=max_r)
		{
			for(int j=0;j<=var;j++)
			{
				swap(a[row][j],a[max_r][j]);
			}
		}
		for(int i=row+1;i<equ;i++)
		{
			if(a[i][col])
			{
				int lcm=a[i][col]/__gcd(a[i][col],a[row][col])*a[row][col];
				int t1=lcm/a[i][col];
				int t2=lcm/a[row][col];
				for(int j=col;j<=var;j++)
				{
					a[i][j]=((a[i][j]*t1-a[row][j]*t2)%MOD+MOD)%MOD;
				}
			}
		}
	}
	for(int i=var-1;i>=0;i--)
	{
		x[i]=a[i][var];
		for(int j=i+1;j<var;j++)
		{
			x[i]=((x[i]-a[i][j]*x[j])%MOD+MOD)%MOD;
		}
		x[i]=a[i][i]*x[i]%MOD;//mod 3下的逆元就是其本身
	}
}
int all;
bool check(int u)
{
	return u>=0&&u<all;
}

int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		int n,m;
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<m;j++)
			{
				scanf("%d",&sv[i*m+j]);
			}
		}
		all=m*n;
		memset(a,0,sizeof(a));
		for(int i=0;i<all;i++)
		{
			int d=i-m;
			int u=i+m;
			int l=i-1;
			int r=i+1;
			a[i][i]=2;
			a[i][all]=(3-sv[i])%MOD;
			if(check(u))
			{
				a[i][u]=1;
			}
			if(check(d))
			{
				a[i][d]=1;
			}
			if(check(l)&&i%m!=0)
			{
				a[i][l]=1;
			}
			if(check(r)&&i%m!=m-1)
			{
				a[i][r]=1;
			}
		}
		Gauss(all,all);
		vector<int> ans;
		for(int i=0;i<all;i++)
		{
			while(x[i])
			{
				x[i]--;
				ans.push_back(i);
			}
		}
		printf("%d\n",ans.size());
		for(int i=0;i<ans.size();i++)
		{
			int x=ans[i]/m;
			int y=ans[i]%m;
			printf("%d %d\n",x+1,y+1);
		}
	}
}
