/* 
 * Kosaraju算法，复杂度O(N+M)
 */ 
const int MAXN = 20010;
const int MAXM = 50010;
struct Edge
{
	int to,next;
}edge1[MAXM],edge2[MAXM];
//edge1是原图G，edge2是逆图GT 
int head1[MAXN],head2[MAXN];
bool mark1[MAXN],mark2[MAXN];
int tot1,tot2;
int cnt1,cnt2;
int st[MAXN];//对原图进行dfs，点的结束时间从小到大排序
int Belong[MAXN];//每个点属于哪个连通分量(0~cnt2-1)
int num;//中间变量，用来数某个连通分量中点的个数
int setNum[MAXN];//强连通分量中点的个数，编号0~cnt2-1
void addedge(int u,int v)
{
	edge1[tot1].to=v;edge1[tot1].next=head1[u];head1[u]=tot1++;
	edge2[tot2].to=u;edge2[tot2].next=head2[v];head2[v]=tot2++;
}
void DFS1(int u)
{
	mark1[u] = true;
	for(int i=head1[u];i!=-1;i=edge1[i].next)
	if(!mark1[edge1[i].to])
		DFS1(edge1[i].to);
	st[cnt1++]=u;
}
void DFS2(int u)
{
	mark2[u]=true;
	num++;
	Belong[u]=cnt2;
	for(int i=head2[u];i!=-1;i=edge2[i].next)
	if(!mark2[edge2[i].to])
		DFS2(edge2[i].to);
}
void solve(int n)//点的编号从1开始 
{
	memset(mark1,false,sizeof(mark1));
	memset(mark2,false,sizeof(mark2));
	cnt1=cnt2=0;
	for(int i=1;i<=n;i++)
	if(!mark1[i])
	DFS1(i);
	for(int i=cnt1-1;i>=0;i--)
	if(!mark2[st[i]])
	{
		num=0;
		DFS2(st[i]);
		setNum[cnt2++]=num;
	}
}
