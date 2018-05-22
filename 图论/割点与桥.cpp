/*
*  求 无向图的割点和桥
*  可以找出割点和桥，求删掉每个点后增加的连通块。
*  需要注意重边的处理，可以先用矩阵存，再转邻接表，或者进行判重
*/
const int MAXN = 10010;
const int MAXM = 100010;
struct Edge
{
    int to,next; 
    bool cut;//是否为桥的标记
}edge[MAXM];
int head[MAXN],tot;
int Low[MAXN],DFN[MAXN],Stack[MAXN];
int Index,top;
bool Instack[MAXN];
bool cut[MAXN];
int add_block[MAXN];//删除一个点后增加的连通块
int bridge;
void addedge(int u,int v)
{
    edge[tot].to=v;edge[tot].next=head[u];edge[tot].cut=false;
    head[u]=tot++;
}
void Tarjan(int u,int pre) 
{ 
    int v;
    Low[u]=DFN[u]=++Index;
    Stack[top++]=u;
    Instack[u]=true;
    int son=0;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].to;
        if(v==pre)continue;
        if(!DFN[v]) 
        { 
            son++;
            Tarjan(v,u);
            if(Low[u]>Low[v])Low[u]=Low[v];
            //桥 
            //一条无向边(u,v)是桥，当且仅当(u,v)为树枝边，且满足DFS(u)<Low(v)。 
            if(Low[v]>DFN[u])
            {
                bridge++;
                edge[i].cut=true;
                edge[i^1].cut=true;
            }
            //割点 
            //一个顶点u是割点，当且仅当满足(1)或(2) (1) u为树根，且u有多于一个子树。 
            //(2) u不为树根，且满足存在(u,v)为树枝边(或称父子边， 
            //即u为v在搜索树中的父亲)，使得DFS(u)<=Low(v) 
            if(u!=pre&&Low[v]>=DFN[u])//不是树根
            {
                cut[u]=true;
                add_block[u]++;
            }
        }
        else if(Low[u]>DFN[v])
             Low[u]=DFN[v]; 
    }
    //树根，分支数大于1
    if(u == pre && son > 1)cut[u]=true;
    if(u == pre)add_block[u]=son-1;
    Instack[u]=false;
    top--;
}


void Tarjan(int u,int pre,int del) //无向图有重边求桥
{ 
    int v;
    int flag=0;
    Low[u]=DFN[u]=++Index;
    for(int i=head[u];i!=-1;i=edge[i].next)
    {
        v=edge[i].to;
        if(v==pre&&!flag)//考虑重边 
        {
            flag=1;
            continue;
        }
        if((i>>1)==del)continue;
        if(!DFN[v])
        {
            Tarjan(v,u,del);
            if(Low[u]>Low[v])Low[u]=Low[v];
            if(Low[v]>DFN[u])
            {
                bridge[i>>1]=1;
            }
        }
        else if(Low[u]>DFN[v])
             Low[u]=DFN[v];
    }
}