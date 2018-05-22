/*后缀数组SA是一个一维数组，它保存1..n的某个排列SA[1]，
SA[2]，……，SA[n]，并且保证Suffix(SA[i])<Suffix(SA[i+1])，1≤i<n。
也就是将S的n个后缀从小到大进行排序之后把排好序的后缀的开头位置顺
次放入SA中。

名次数组Rank[i]保存的是Suffix(i)在所有后缀中从小到大排
列的“名次”。

定义height[i]=suffix(sa[i-1])和suffix(sa[i])的最长公
共前缀，也就是排名相邻的两个后缀的最长公共前缀。

其他数组都是辅助数组*/
const int MAXN=1000001;
int WA[MAXN],WB[MAXN],WV[MAXN],WS[MAXN];
int cmp(int *r,int a,int b,int l)
{
	return r[a]==r[b]&&r[a+l]==r[b+l];
}
void da(int *r,int *sa,int n,int m)
{
	int i,j,p,*x=WA,*y=WB,*t;
	for(i=0;i<m;i++) WS[i]=0;
	for(i=0;i<n;i++) WS[x[i]=r[i]]++;
	for(i=1;i<m;i++) WS[i]+=WS[i-1];
	for(i=n-1;i>=0;i--) sa[--WS[x[i]]]=i;
	for(j=1,p=1;p<n;j*=2,m=p)
	{
		for(p=0,i=n-j;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;i++) WV[i]=x[y[i]];
		for(i=0;i<m;i++) WS[i]=0;
		for(i=0;i<n;i++) WS[WV[i]]++;
		for(i=1;i<m;i++) WS[i]+=WS[i-1];
		for(i=n-1;i>=0;i--) sa[--WS[WV[i]]]=y[i];
		for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
		x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
	}
	return;
}
int Rank[MAXN],height[MAXN];
void calheight(int *r,int *sa,int n)
{
	int i,j,k=0;
	for(i=1;i<=n;i++) 
		Rank[sa[i]]=i;
	for(i=0;i<n;height[Rank[i++]]=k)
		for(k?k--:0,j=sa[Rank[i]-1];r[i+k]==r[j+k];k++);
	return;
}
int r[MAXN],sa[MAXN];
int RMQ[MAXN];
int mm[MAXN];
int best[20][MAXN];
void initRMQ(int n)
{
	int i,j,a,b;
	for(mm[0]=-1,i=1;i<=n;i++)
		mm[i]=((i&(i-1))==0)?mm[i-1]+1:mm[i-1];
	for(i=1;i<=n;i++)
		best[0][i]=i;
	for(i=1;i<=mm[n];i++)
	for(j=1;j<=n+1-(1<<i);j++)
	{
		a=best[i-1][j];
		b=best[i-1][j+(1<<(i-1))];
		if(RMQ[a]<RMQ[b]) 
			best[i][j]=a;
		else best[i][j]=b;
	}
	return;
}
int askRMQ(int a,int b)
{
	int t;
	t=mm[b-a+1];b-=(1<<t)-1;
	a=best[t][a];b=best[t][b];
	return RMQ[a]<RMQ[b]?a:b;
}
int lcp(int a,int b)
{
	int t;
	a=Rank[a];b=Rank[b];
	if(a>b)
	{
		t=a;a=b;b=t;
	}
	return(height[askRMQ(a+1,b)]);
}
