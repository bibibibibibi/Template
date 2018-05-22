typedef long long ll;
int pri[MAXN],phi[MAXN];
bool vis[MAXN];
int tot;
ll sum[MAXN];
void init()
{
    int n=MAXN;
    tot=0;
    memset(vis,false,sizeof(vis));
    phi[1]=1;
    for(int i=2;i<n;i++)
    {
        if(!vis[i])
        {
            pri[tot++]=i;
            phi[i]=i-1;
        }
        for(int j=0;j<tot&&i*pri[j]<n;j++)
        {
            vis[i*pri[j]]=true;
            if(i%pri[j]==0)
            {
                phi[i*pri[j]]=phi[i]*pri[j];
                break;
            }
            else phi[i*pri[j]]=phi[i]*(pri[j]-1);
        }
    }
    sum[0]=0;
    for(int i=1;i<MAXN;i++)
        sum[i]=(sum[i-1]+phi[i])%M;
}
