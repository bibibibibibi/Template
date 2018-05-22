//用'临点填色法'判断，相邻点异色，发现同色则不成立
bool BFS()//二分图BFS判断
{
    queue<int> Q;
    int judge[MAXN];// 判断二分图时 0-1表
    int v;
    for(int i=0;i<=n;i++) 
        judge[i]=-1;
    for(int j=1;j<=n;j++)
    {
        if(judge[j]==-1)
        {
            Q.push(j);
            judge[j]=0;
            uN.push_back(j);//加入左半部分
            while(!Q.empty())
            {
                v=Q.front();
                Q.pop();
                for(int i=1;i<=n;i++)
                {
                    if(g[v][i])
                    {
                        if(judge[i]==-1)
                        {
                            judge[i]=(judge[v]+1)%2;
                            Q.push(i);
                            if(judge[i]==0)
                            {
                                uN.push_back(i);//加入左半部分
                            }
                            else
                            {
                                vN.push_back(i);//加入右半部分
                            }
                        }
                        else
                        {
                            if(judge[i]==judge[v])
                                return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}