#include<bits/stdc++.h>
using namespace std;
namespace Point_divide
{
    const int MAXN=10010;
    int N,K;
    int ans,root,Max;
    struct node
    {
        int v,nxt,w;
    }edge[MAXN*2];
    int head[MAXN],tot;
    int size[MAXN];//树的大小
    int maxv[MAXN];//最大孩子节点的size
    int vis[MAXN];
    int dis[MAXN];
    int num;
    void init()
    {
        tot=0;
        ans=0;
        memset(head,-1,sizeof(head));
        memset(vis,0,sizeof(vis));
    }
    void addedge(int u,int v,int w)
    {
        edge[tot].v=v;
        edge[tot].w=w;
        edge[tot].nxt=head[u];
        head[u]=tot++;
    }
    //处理子树的大小
    void dfssize(int u,int f)
    {
        size[u]=1;
        maxv[u]=0;
        for(int i=head[u];i!=-1;i=edge[i].nxt)
        {
            int v=edge[i].v;
            if(v==f||vis[v])continue;
            dfssize(v,u);
            size[u]+=size[v];
            if(size[v]>maxv[u])maxv[u]=size[v];
        }
    }
    //找重心
    void dfsroot(int r,int u,int f)
    {
        if(size[r]-size[u]>maxv[u])//size[r]-size[u]是u上面部分的树的尺寸，跟u的最大孩子比，找到最大孩子的最小差值节点
            maxv[u]=size[r]-size[u];
        if(maxv[u]<Max)Max=maxv[u],root=u;
        for(int i=head[u];i!=-1;i=edge[i].nxt)
        {
            int v=edge[i].v;
            if(v==f||vis[v])continue;
            dfsroot(r,v,u);
        }
    }
    //求每个点离重心的距离
    void dfsdis(int u,int d,int f)
    {
        dis[num++]=d;
        for(int i=head[u];i!=-1;i=edge[i].nxt)
        {
            int v=edge[i].v;
            if(v!=f&&!vis[v])
                dfsdis(v,d+edge[i].w,u);
        }
    }
    //计算以u为根的子树中有多少点对的距离小于等于K
    int calc(int u,int d)
    {
        int ret=0;
        num=0;
        dfsdis(u,d,0);
        sort(dis,dis+num);
        int i=0,j=num-1;
        while(i<j)
        {
            while(dis[i]+dis[j]>K&&i<j)j--;
            ret+=j-i;
            i++;
        }
        return ret;
    }
    void dfs(int u)
    {
        Max=N;
        dfssize(u,0);
        dfsroot(u,u,0);
        ans+=calc(root,0);
        vis[root]=1;
        for(int i=head[root];i!=-1;i=edge[i].nxt)
        {
            int v=edge[i].v;
            if(!vis[v])
            {
                ans-=calc(v,edge[i].w);
                dfs(v);
            }
        }
    }
}
using namespace Point_divide;
int main()
{
    while(scanf("%d%d",&N,&K)!=EOF)
    {
        if(!N&&!K)break;
        int u,v,w;
        init();
        for(int i=1;i<N;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            addedge(u,v,w);
            addedge(v,u,w);
        }

        dfs(1);
        printf("%d\n",ans);
    }
    return 0;
}

