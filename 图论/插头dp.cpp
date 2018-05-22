#include<stdio.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;

const int HASH=10007;
const int STATE=1000010;//状态数
const int MAXD=15;
int N,M;
int code[MAXD],maze[MAXD][MAXD];

struct HASHMAP
{
    int head[HASH],next[STATE],state[STATE],size;
    long long f[STATE];
    void init()
    {
        size=0;
        memset(head,-1,sizeof(head));
    }
    void push(int st,long long ans)
    {
        int i,h=st%HASH;
        for(i=head[h];i!=-1;i=next[i])
          if(st==state[i])
          {
              f[i]+=ans;
              return;
          }
        f[size]=ans;
        state[size]=st;
        next[size]=head[h];
        head[h]=size++;
    }
}hm[2];

void decode(int *code,int m,int st)
{
    int i;
    for(i=m;i>=0;i--)
    {
        code[i]=st&1;
        st>>=1;
    }
}
int encode(int *code,int m)
{
    int i,st=0;
    for(int i=0;i<=m;i++)
    {
        st<<=1;
        st|=code[i];
    }
    return st;
}
void init()
{
    scanf("%d%d",&N,&M);
    for(int i=1;i<=N;i++)
      for(int j=1;j<=M;j++)
        scanf("%d",&maze[i][j]);
    for(int i=1;i<=N;i++)maze[i][M+1]=0;//边界补0
    for(int i=1;i<=M;i++)maze[N+1][i]=0;
}

void shift(int *code,int m)//换行的时候移位
{
    int i;
    for(i=m;i>0;i--)
      code[i]=code[i-1];
    code[0]=0;
}

void dpblank(int i,int j,int cur)
{
    int k,left,up;
    for(k=0;k<hm[cur].size;k++)
    {
        decode(code,M,hm[cur].state[k]);
        left=code[j-1];
        up=code[j];
        if(left&&up)//11  -> 00
        {
            code[j-1]=code[j]=0;
            if(j==M)shift(code,M);
            hm[cur^1].push(encode(code,M),hm[cur].f[k]);
        }
        else if(left||up)//01 或 10
        {
            if(maze[i][j+1])
            {
                code[j-1]=0;
                code[j]=1;
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
            if(maze[i+1][j])
            {
                code[j-1]=1;
                code[j]=0;
                if(j==M)shift(code,M);//这个不要忘了！
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
        else
        {
            if(maze[i][j+1]&&maze[i+1][j])
            {
                code[j]=code[j-1]=1;
                hm[cur^1].push(encode(code,M),hm[cur].f[k]);
            }
        }
    }
}

void dpblock(int i,int j,int cur)
{
    int k;
    for(k=0;k<hm[cur].size;k++)
    {
        decode(code,M,hm[cur].state[k]);
        code[j-1]=code[j]=0;
        if(j==M)shift(code,M);
        hm[cur^1].push(encode(code,M),hm[cur].f[k]);
    }
}

void solve()
{
    int i,j,cur=0;
    long long ans=0;
    hm[cur].init();
    hm[cur].push(0,1);
    for(i=1;i<=N;i++)
      for(j=1;j<=M;j++)
      {
          hm[cur^1].init();
          if(maze[i][j])dpblank(i,j,cur);
          else dpblock(i,j,cur);
          cur^=1;
      }
    for(i=0;i<hm[cur].size;i++)
      ans+=hm[cur].f[i];
    printf("There are %I64d ways to eat the trees.\n",ans);
}
int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    int T;
    int iCase=0;
    scanf("%d",&T);
    while(T--)
    {
        iCase++;
        printf("Case %d: ",iCase);
        init();
        solve();
    }
    return 0;
}
