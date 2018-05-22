namespace SW
{
    const int N=510,INF=0x3f3f3f3f;
    int mpa[N][N],dis[N],v[N];//v数组是马甲数组，dis数组用来表示该点与A集合中所有点之间的边的长度之和    
    bool vis[N];//用来标记是否该点加入了A集合
    int stoer_wagner(int n)
    {
        int res=INF;
        for(int i=0;i<n;i++) 
            v[i]=i;//初始马甲为自己
        while(n>1)
        { 
            int k,pre=0;//pre用来表示之前加入A集合的点，我们每次都以0点为第一个加入A集合的点
            memset(vis,0,sizeof(vis));
            memset(dis,0,sizeof(dis));
            vis[v[pre]]=true;////
            for(int i=1;i<n;i++)
            {
                k=-1;
                for(int j=1;j<n;j++)//根据之前加入的点，要更新dis数组，并找到最大的dis
                    if(!vis[v[j]])
                    {
                        dis[v[j]]+=mpa[v[pre]][v[j]];
                        if(k==-1||dis[v[k]]<dis[v[j]])
                            k=j;
                    }
                vis[v[k]]=true;//标记该点已经加入A集合
                if(i==n-1)//最后一次加入的点就要更新答案了
                {
                    res=min(res,dis[v[k]]);
                    for(int j=0;j<n;j++)//将该点合并到pre上，相应的边权就要合并
                    {
                        mpa[v[pre]][v[j]]+=mpa[v[j]][v[k]];
                        mpa[v[j]][v[pre]]+=mpa[v[j]][v[k]];
                    }
                    v[k]=v[--n];//删除点v[k]，把最后一个点扔到v[k]上
                }
                pre=k;
            }
        }
        return res;
    }
}
