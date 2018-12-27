#include<bits/stdc++.h>
#define xx first
#define yy second
using namespace std;
const int MAXN=1e5+5;
struct Treap
{
    struct node
    {
        int fix,key,size;
        int l,r;
        node(){}
        node(int _key):fix(rand()),key(_key),l(0),r(0),size(1){}
    }tr[MAXN];
    typedef pair<int,int> Droot;//用来Split返回两个根 
    inline void updata(int o)
    {
        tr[o].size=1+(tr[o].l?tr[tr[o].l].size:0)+(tr[o].r?tr[tr[o].r].size:0);
    }
    inline int Size(int x)
    {
        return x?tr[x].size:0;
    }//这样求size可以防止访问空指针 
    int tot,root;
    void init()
    {
        tot=0;
    }
    inline int newnode(int val)
    {
        int ret=++tot;
        tr[tot]=node(val);
        return ret;
    }
    //合并操作
    int Merge(int A,int B)
    {
        if(!A)
            return B;
        if(!B)
            return A;
        if(tr[A].fix<tr[B].fix)
        {
            tr[A].r=Merge(tr[A].r,B);
            updata(A);
            return A;
        }
        else
        {
            tr[B].l=Merge(A,tr[B].l);
            updata(B);
            return B;
        }
    }
    //拆分操作 
    Droot Split(int x,int k)
    {
        if(!x)
            return Droot(0,0);
        Droot ret;
        if(Size(tr[x].l)>=k)
        {
            ret=Split(tr[x].l,k);
            tr[x].l=ret.yy;
            updata(x);
            ret.yy=x;
        }
        else
        {
            ret=Split(tr[x].r,k-Size(tr[x].l)-1);
            tr[x].r=ret.xx;
            updata(x);
            ret.xx=x;
        }
        return ret;
    }
    //建造操作 
    int stack[MAXN],x,last;
    int Build(int *a,int n)
    {
        int p=0;
        for(int i=1;i<=n;i++)
        {
            x=newnode(a[i]);
            last=0;
            while(p&&tr[stack[p]].fix>tr[x].fix)
            {
                updata(stack[p]);
                last=stack[p];
                stack[p--]=0;
            }
            if(p)
                tr[stack[p]].r=x;
            tr[x].l=last;
            stack[++p]=x;
        }
        while(p) 
            updata(stack[p--]);
        return stack[1];
    }
    //查找第K小 
    int Findkth(int k)
    {        
        Droot x=Split(root,k-1);
        Droot y=Split(x.yy,1);
        int ret=y.xx;
        root=Merge(Merge(x.xx,ret),y.yy);
        return tr[ret].key;
    }
    //询问有多少数比v小，如果是排名则要+1
    int Getkth(int x,int v)
    {
        if(!x)
            return 0;
        return v<=tr[x].key?Getkth(tr[x].l,v):Getkth(tr[x].r,v)+Size(tr[x].l)+1;
    }
    //插入操作 
    void Insert(int v)
    {
        int k=Getkth(root,v);
        Droot x=Split(root,k);
        int o=newnode(v);
        root=Merge(Merge(x.xx,o),x.yy);
    }
    //删除操作 
    void Delete(int k)
    {
        Droot x=Split(root,k-1);
        Droot y=Split(x.yy,1);
        root=Merge(x.xx,y.yy);
    }
};
