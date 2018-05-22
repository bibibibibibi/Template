//第一类Stirling数 表示将n个不同元素构成m个圆排列的
const int MOD=1e9+7
int s[MAXN][MAXN];

void init()
{
	memset(s,0,sizeof(s));
	s[0][0]=1;
	for(int i=1;i<MAXN;i++)
		for(int j=1;j<=i;j++)
			s[i][j]=(s[i-1][j-1]+1LL*(i-1)*s[i-1][j]%MOD)%MOD;
}

//第二类Stirling数 表示将n个不同的元素拆分成m个无序集合的方案数
//可以通过fft快速求解
const int MOD=1e9+7;
int s[MAXN][MAXN];//存放要求的

void init()
{
	memset(s,0,sizeof(s));
	s[0][0]=1;
	for(int i=1;i<MAXN;i++)
		for(int j=1;j<=i;j++)
			s[i][j]=(s[i-1][j-1]+1LL*j*s[i-1][j]%MOD)%MOD;
}
