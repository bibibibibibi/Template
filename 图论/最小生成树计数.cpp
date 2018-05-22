/*
 *算法引入：
 *给定一个含有N个结点M条边的无向图,求它最小生成树的个数t(G);
 *
 *算法思想：
 *抛开“最小”的限制不看,如果只要求求出所有生成树的个数,是可以利用Matrix-Tree定理解决的;
 *Matrix-Tree定理此定理利用图的Kirchhoff矩阵,可以在O(N3)时间内求出生成树的个数;
 *
 *kruskal算法：
 *将图G={V,E}中的所有边按照长度由小到大进行排序,等长的边可以按照任意顺序;
 *初始化图G’为{V,?},从前向后扫描排序后的边,如果扫描到的边e在G’中连接了两个相异的连通块,则将它插入G’中;
 *最后得到的图G’就是图G的最小生成树;
 *
 *由于kruskal按照任意顺序对等长的边进行排序,则应该将所有长度为L0的边的处理当作一个阶段来整体看待;
 *令kruskal处理完这一个阶段后得到的图为G0,如果按照不同的顺序对等长的边进行排序,得到的G0也是不同;
 *虽然G0可以随排序方式的不同而不同,但它们的连通性都是一样的,都和F0的连通性相同(F0表示插入所有长度为L0的边后形成的图);
 *
 *在kruskal算法中的任意时刻,并不需要关注G’的具体形态,而只要关注各个点的连通性如何(一般是用并查集表示);
 *所以只要在扫描进行完第一阶段后点的连通性和F0相同,且是通过最小代价到达这一状态的,接下去都能找到最小生成树;
 *
 *经过上面的分析,可以看出第一个阶段和后面的工作是完全独立的;
 *第一阶段需要完成的任务是使G0的连通性和F0一样,且只能使用最小的代价;
 *计算出这一阶段的方案数,再乘上完成后续事情的方案数,就是最终答案;
 *
 *由于在第一个阶段中,选出的边数是一定的,所有边的长又都为L0;
 *所以无论第一个阶段如何进行代价都是一样的,那么只需要计算方案数就行了;
 *此时Matrix-Tree定理就可以派上用场了,只需对F0中的每一个连通块求生成树个数再相乘即可;
 *
 *Matrix-Tree定理:
 *G的所有不同的生成树的个数等于其Kirchhoff矩阵C[G]任何一个n-1阶主子式的行列式的绝对值；
 *n-1阶主子式就是对于r(1≤r≤n),将C[G]的第r行,第r列同时去掉后得到的新矩阵,用Cr[G]表示;
 *
 *算法举例：
 *HDU4408(Minimum Spanning Tree)
 *
 *题目地址：
 *http://acm.hdu.edu.cn/showproblem.php?pid=4408
 *
 *题目大意：
 *给定一个含有N个结点M条边的无向图,求它最小生成树的个数,所得结果对p取模;
**/

#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;
const int N=111;
const int M=1111;
typedef long long LL;
struct Edges
{
    int a,b,c;
    bool operator<(const Edges &x)const
    {
        return c<x.c;
    }
} edge[M];
int n,m;
int mod;
LL f[N],U[N],vist[N];//f,U都是并查集，U是每组边临时使用
LL G[N][N],C[N][N];//G顶点之间的关系，C为生成树计数用的Kirchhoff矩阵
vector<int>V[N];//记录每个连通分量
int Find(int x,LL f[])
{
    if(x==f[x])
        return x;
    else
        return Find(f[x],f);
}
LL det(LL a[][N],int n)//生成树计数:Matrix-Tree定理
{
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            a[i][j]%=mod;
    int ret=1;
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
            while(a[j][i])
            {
                int t=a[i][i]/a[j][i];
                for(int k=i; k<n; k++)
                    a[i][k]=(a[i][k]-a[j][k]*t)%mod;
                for(int k=i; k<n; k++)
                    swap(a[i][k],a[j][k]);
                ret=-ret;
            }
        if(a[i][i]==0)
            return 0;
        ret=ret*a[i][i]%mod;
    }
    return (ret+mod)%mod;
}
void Solve()
{
    sort(edge,edge+m);//按权值排序
    for(int i=1;i<=n;i++)//初始化并查集
    {
        f[i]=i;
        vist[i]=0;
    }
    LL Edge=-1;//记录相同的权值的边
    LL ans=1;
    for(int k=0;k<=m;k++)
    {
        if(edge[k].c!=Edge||k==m)//一组相等的边,即权值都为Edge的边加完
        {
            for(int i=1;i<=n;i++)
            {
                if(vist[i])
                {
                    LL u=Find(i,U);
                    V[u].push_back(i);
                    vist[i]=0;
                }
            }
            for(int i=1;i<=n;i++) //枚举每个连通分量
            {
                if(V[i].size()>1)
                {
                    for(int a=1;a<=n;a++)
                        for(int b=1;b<=n;b++)
                            C[a][b]=0;
                    int len=V[i].size();
                    for(int a=0;a<len;a++) //构建Kirchhoff矩阵C
                        for(int b=a+1;b<len;b++)
                        {
                            int a1=V[i][a];
                            int b1=V[i][b];
                            C[a][b]=(C[b][a]-=G[a1][b1]);
                            C[a][a]+=G[a1][b1];//连通分量的度
                            C[b][b]+=G[a1][b1];
                        }
                    LL ret=(LL)det(C,len);
                    ans=(ans*ret)%mod;//对V中的每一个连通块求生成树个数再相乘
                    for(int a=0; a<len; a++)
                        f[V[i][a]]=i;
                }
            }
            for(int i=1;i<=n;i++)
            {
                U[i]=f[i]=Find(i,f);
                V[i].clear();
            }
            if(k==m)
                break;
            Edge=edge[k].c;
        }
        int a=edge[k].a;
        int b=edge[k].b;
        int a1=Find(a,f);
        int b1=Find(b,f);
        if(a1==b1)
            continue;
        vist[a1]=vist[b1]=1;
        U[Find(a1,U)]=Find(b1,U);//并查集操作
        G[a1][b1]++;
        G[b1][a1]++;
    }
    int flag=0;
    for(int i=2;i<=n&&!flag;i++)
        if(U[i]!=U[i-1])
            flag=1;
    if(m==0)
        flag=1;
    printf("%lld\n",flag?0:ans%mod);
}
int main()
{
    //freopen("C:\\Users\\Administrator\\Desktop\\kd.txt","r",stdin);
    while(~scanf("%d%d%d",&n,&m,&mod))
    {
        memset(G,0,sizeof(G));
        for(int i=1; i<=n; i++)
            V[i].clear();
        for(int i=0; i<m; i++)
            scanf("%d%d%d",&edge[i].a,&edge[i].b,&edge[i].c);
        Solve();
    }
    return 0;
}
