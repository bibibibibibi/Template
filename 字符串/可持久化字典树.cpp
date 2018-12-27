#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
const int MAXN=500005;
const int M=MAXN*64;
int ch[M][2];
int root[MAXN];
int np;
ull sz[M];
 
char c;
void scan(ull &x)
{
	for(c=getchar();c<'0'||c>'9';c=getchar());
	for(x=0;c>='0'&&c<='9';c=getchar()) x=x*10+c-'0';
}
 
char num[50];int ct;
void print(ull x)
{
	ct=0;
	if(x==0) num[ct++]='0';
	while(x) num[ct++]=x%10+'0',x/=10;
	while(ct--) putchar(num[ct]);
	putchar('\n');
}
 
void init()
{
	memset(sz,0,sizeof(sz));
	memset(root,0,sizeof(root));
	memset(ch,0,sizeof(ch));
	np=0;
}
 
void pushup(int now)
{
	sz[now]=sz[ch[now][0]]+sz[ch[now][1]];
}
 
void insert(int pre,int &now,int i,ull x)
{
	now=++np;//新建一个版本 
	sz[now]=sz[pre];//复制前一个版本 
	if(i<0)
	{
		sz[now]++;//这个版本自己本身有一个元素 
		return;
	}
	int d=(x>>i)&1;
	ch[now][d^1]=ch[pre][d^1];//d^1子树与前一个版本共用，因为当前元素不走这边 
	insert(ch[pre][d],ch[now][d],i-1,x);//d子树新建 ，当前元素走的是这边 
	pushup(now);//更新这个节点上的值，用于后面查询判断 
}
 
ull ques(int l,int r,int i,ull x)
{
	if(i<0) return 0;
	int d=(x>>i)&1;
	int t=sz[ch[r][d^1]]-sz[ch[l][d^1]]; //说明r这边确实有d^1这条路（因为它比之前的版本大） 
	if(t>0) return ques(ch[l][d^1],ch[r][d^1],i-1,x)+((ull)1<<i);
	else return ques(ch[l][d],ch[r][d],i-1,x);
}
 
int main()
{
	ull N,M,i,j,L,R,x;
	init();
	scan(N);
	for(i=1;i<=N;i++)
	{
		scan(x);
		insert(root[i-1],root[i],63,x);//以元素下标作为版本号 
	}
	cin>>M;
	for(i=1;i<=M;i++)
	{
		scan(L);scan(R);scan(x);
		print(ques(root[L-1],root[R],63,x));//询问这个版本区间 
	}
	return 0;
}
