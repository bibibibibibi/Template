/*
 *算法引入：
 *给定一个无向图G，求它生成树的个数t(G);
 *
 *算法思想：
 *(1)G的度数矩阵D[G]是一个n*n的矩阵,并且满足:当i≠j时,dij=0;当i=j时,dij等于vi的度数;
 *(2)G的邻接矩阵A[G]是一个n*n的矩阵,并且满足:如果vi,vj之间有边直接相连,则aij=1,否则为0;
 *定义图G的Kirchhoff矩阵C[G]为C[G]=D[G]-A[G];
 *Matrix-Tree定理:G的所有不同的生成树的个数等于其Kirchhoff矩阵C[G]任何一个n-1阶主子式的行列式的绝对值；
 *所谓n-1阶主子式,就是对于r(1≤r≤n),将C[G]的第r行,第r列同时去掉后得到的新矩阵,用Cr[G]表示;
 *
 *Kirchhoff矩阵的特殊性质：
 *(1)对于任何一个图G,它的Kirchhoff矩阵C的行列式总是0,这是因为C每行每列所有元素的和均为0;
 *(2)如果G是不连通的,则它的Kirchhoff矩阵C的任一个主子式的行列式均为0;
 *(3)如果G是一颗树,那么它的Kirchhoff矩阵C的任一个n-1阶主子式的行列式均为1;
 *
 *算法举例：
 *SPOJ104(Highways)
 *
 *题目地址：
 *http://www.spoj.com/problems/HIGH/
 *
 *题目大意：
 *一个有n座城市的组成国家,城市1至n编号,其中一些城市之间可以修建高速公路;
 *需要有选择的修建一些高速公路,从而组成一个交通网络;
 *计算有多少种方案,使得任意两座城市之间恰好只有一条路径;
**/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

const int N=15;

typedef long long LL;

int degree[N];
LL C[N][N];

LL det(LL a[][N],int n)//生成树计数:Matrix-Tree定理(行列式的计算)
{
    LL ret=1;
    for(int i=1;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
            while(a[j][i])
            {
                LL t=a[i][i]/a[j][i];
                for(int k=i;k<n;k++)
                    a[i][k]=(a[i][k]-a[j][k]*t);
                for(int k=i;k<n;k++)
                    swap(a[i][k],a[j][k]);
                ret=-ret;
            }
        if(a[i][i]==0)
            return 0;
        ret=ret*a[i][i];
    }
    if(ret<0)
        ret=-ret;
    return ret;
}

int main()
{
    int tcase;
    scanf("%d",&tcase);
    while(tcase--)
    {
        memset(degree,0,sizeof(degree));
        memset(C,0,sizeof(C));
        int n,m;
        scanf("%d%d",&n,&m);
        int u,v;
        while(m--)
        {
            scanf("%d%d",&u,&v);
            u--;
            v--;
            C[u][v]=C[v][u]=-1;
            degree[u]++;
            degree[v]++;
        }
        for(int i=0; i<n; ++i)
            C[i][i]=degree[i];
        printf("%lld\n",det(C,n));
    }
    return 0;
}

