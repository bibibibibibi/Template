/*
 * Next[]的含义：x[i-Next[i]...i-1]=x[0...Next[i]-1] 
 * Next[i]为满足x[i-z...i-1]=x[0...z-1]的最大z值（就是x的自身匹配） 
 */
void kmp_pre(char x[],int m,int Next[])
{
	int i,j;
	j=Next[0]=-1;
	i=0;
	while(i<m)
	{
		while(-1!=j && x[i]!=x[j])j=Next[j];
		Next[++i]=++j;
	}
}
/* 
 * kmpNext[]的意思：Next'[i]=Next[Next[...[Next[i]]]] (直到Next'[i]<0或者x[Next'[i]]!=x[i]) 
 * 这样的预处理可以快一些 
 */ 
void preKMP(char x[],int m,int kmpNext[])
{
	int i,j;
	j=kmpNext[0]=-1;
	i=0;
	while(i<m)
	{
		while(-1!=j && x[i]!=x[j])j=kmpNext[j];
		if(x[++i]==x[++j])kmpNext[i]=kmpNext[j];
		else kmpNext[i]=j;
	}
}
/* 
 * 返回x在y中出现的次数，可以重叠 
 */
int Next[10010];
int KMP_Count(char x[],int m,char y[],int n)//x是模式串，y是主串
{
	int i,j;
	int ans=0;
	preKMP(x,m,Next);
	//kmp_pre(x,m,Next);
	i=j=0;
	while(i<n)
	{
		while(-1!=j&&y[i]!=x[j])j=Next[j];
		i++;j++;
		if(j>=m)
		{
			ans++;
			j=Next[j];
		}
	}
	return ans;
}
