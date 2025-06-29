/*
后缀数组SA是一个一维数组，它保存1..n的某个排列SA[1]，SA[2]，……，SA[n]，并且保证Suffix(SA[i])<Suffix(SA[i+1])，1≤i<n。
也就是将S的n个后缀从小到大进行排序之后把排好序的后缀的开头位置顺次放入SA中。

名次数组rk[i]保存的是Suffix(i)在所有后缀中从小到大排列的“名次”。

定义h[i]=suffix(sa[i-1])和suffix(sa[i])的最长公共前缀，也就是排名相邻的两个后缀的最长公共前缀。

其他数组都是辅助数组,n和m均从1开始
*/
namespace SA
{
	const int MAXN=5e5+5;
	int sa[MAXN],rk[MAXN],h[MAXN];
	int c[MAXN],x[MAXN],y[MAXN];
	void da(int n,int s[],int m=26)
	{
		for(int i=1;i<=n;i++)c[x[i]=s[i]]++;
		for(int i=2;i<=m;i++)c[i]+=c[i-1];
		for(int i=n;i;i--)sa[c[x[i]]--]=i;
		for(int k=1,j;j=0,k<n;k<<=1,m=j)
		{
			for(int i=n-k+1;i<=n;i++) y[++j]=i;
			for(int i=1;i<=n;i++)
				if(sa[i]>k)
					y[++j]=sa[i]-k;
			for(int i=1;i<=m;i++) c[i]=0;
			for(int i=1;i<=n;i++) c[x[i]]++;
			for(int i=2;i<=m;i++) c[i]+=c[i-1];
			for(int i=n;i;i--) sa[c[x[y[i]]]--]=y[i];
			swap(x,y);
			x[sa[1]]=j=1;
			for(int i=2;i<=n;x[sa[i++]]=++j)
				if(y[sa[i]]==y[sa[i-1]]&&y[sa[i]+k]==y[sa[i-1]+k])
					j--;
			if(j==n) break;
		}
		for(int i=1;i<=n;i++) rk[sa[i]]=i;
		for(int i=1,j,k=0;i<=n;i++)
		{
			if(k)k--;
			j=sa[rk[i]-1];
			while(s[i+k]==s[j+k]) k++;
			h[rk[i]]=k;
		}
	}
}
