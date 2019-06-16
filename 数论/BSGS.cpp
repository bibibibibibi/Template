// a^x = b (mod n) n 是素数和不是素数都可以
const int M=76543;
int hs[M],head[M],next[M],id[M],top;
void insert(int x,int y)
{
	int k=x%M;
	hs[top]=x,id[top]=y,next[top]=head[k],head[k]=top++;
}
int find(int x)
{
	int k=x%M;
	for(int i=head[k];i!=-1;i=next[i])
		if(hs[i]==x)
			return id[i];
	return -1;
}
int BSGS(int a,int b,int n)
{
	memset(head,-1,sizeof(head));
	top=1;
	if(b==1) return 0;
	int m=sqrt(n*1.0),j;
	long long x=1,p=1;
	for(int i=0;i<m;++i,p=p*a%n) insert(p*b%n,i);
	for(long long i=m; ;i+=m)
	{
		if((j=find(x=x*p%n))!=-1) return i-j;
		if(i>n) break;
	}
	return -1;
}
