#define x first
#define y second
const int MAXN=2e5+5;
const int inf=2e9;
namespace KD_Tree
{
    struct node
    {
        node *ch[2];
        int d[2],mx[2],my[2],size;//d表示这个点的坐标[0]->x,[1]->y,mx表示这个平面的x的范围，my表示这个平面的y的范围
        inline void push_up()
        {
            size=1;
            for(int i=0;i<=1;i++)
            {
                if(ch[i])
                {
                    mx[0]=min(mx[0],ch[i]->mx[0]);
                    mx[1]=max(mx[1],ch[i]->mx[1]);
                    my[0]=min(my[0],ch[i]->my[0]);
                    my[1]=max(my[1],ch[i]->my[1]);
                    size+=ch[i]->size;
                }
            }
        }
    }pool_node[MAXN],*pool_top=pool_node;
    node *del_pool[MAXN],**del_top=del_pool;
    inline node* newnode()
    {
        return del_top==del_pool?++pool_top:*(del_top--);
    }
    typedef pair<int,int> Point;
    inline bool cmp_x(const Point &a,const Point &b) {return a.x<b.x;}
    inline bool cmp_y(const Point &a,const Point &b) {return a.y<b.y;}
    node **rebuild_need;
    int rebuild_d;
    Point stk[MAXN];
    int point_cnt;
    //用于最开始建树，可以不用直接插点，方法为build(1,point_cnt,0),保证点在stk数组中
    node* build(int l,int r,bool f)
    {
        int mid=(l+r)>>1;
        node *o=newnode();
        nth_element(stk+l,stk+mid,stk+r+1,!f?cmp_x:cmp_y);
        o->d[0]=o->mx[0]=o->mx[1]=stk[mid].x;
        o->d[1]=o->my[0]=o->my[1]=stk[mid].y;
        o->ch[0]=l<mid?build(l,mid-1,f^1):0;
        o->ch[1]=mid<r?build(mid+1,r,f^1):0;
        o->push_up();
        return o;
    }
    void remove(node *o)
    {
        if(o->ch[0])
            remove(o->ch[0]);
        if(o->ch[1])
            remove(o->ch[1]);
        stk[++point_cnt]=Point(o->d[0],o->d[1]);
        *(++del_top)=o;
    }
    /*
    插入以及重构代码如下
    insert(root,x,y,0);
    if(rebuild_need)
        rebuild();
    */
    void rebuild()
    {
        point_cnt=0;
        remove(*rebuild_need);
        *rebuild_need=build(1,point_cnt,rebuild_d);
        rebuild_need=0;
    }
    void insert(node *&o,int x,int y,bool f)
    {
        if(!o)
        {
            o=newnode();
            o->d[0]=o->mx[0]=o->mx[1]=x;
            o->d[1]=o->my[0]=o->my[1]=y;
        }
        else if(o->d[0]!=x||o->d[1]!=y)
        {
            int d=!f?o->d[0]<x:o->d[1]<y;
            insert(o->ch[d],x,y,f^1);
            o->push_up();
            if(o->ch[d]->size*10>=o->size*7)
                rebuild_need=&o,rebuild_d=f;
        }
    }
    Point P;
    int ans;
    int calc_mx(node *o)//同下calc_mn
    {
        int ret=0;
        ret+=max(abs(o->mx[0]-P.x),abs(o->mx[1]-P.x));
        ret+=max(abs(o->my[0]-P.y),abs(o->my[1]-P.y));
        return ret;
    }
    int calc_mn(node *o)//Manhattan距离下进行计算，如果是欧氏距离，则为max(P.x-o->mx[1],0)+max(o->mx[0]-P.x,0)的平方（本处表示到这个子树平面的最短距离）
    {
        int ret=0;
        ret+=max(P.x-o->mx[1],0)+max(o->mx[0]-P.x,0);
        ret+=max(P.y-o->my[1],0)+max(o->my[0]-P.y,0);
        return ret;
    }
    void Query_Max(node *o)//查询平面中到目标点最远的点
    {
        ans=max(ans,abs(o->d[0]-P.x)+abs(o->d[1]-P.y));
        int dl=o->ch[0]?calc_mx(o->ch[0]):-inf;
        int dr=o->ch[1]?calc_mx(o->ch[1]):-inf;
        if(dl>dr)
        {
            if(dl>ans)
                Query_Max(o->ch[0]);
            if(dr>ans)
                Query_Max(o->ch[1]);
        }
        else
        {
            if(dr>ans)
                Query_Max(o->ch[1]);
            if(dl>ans)
                Query_Max(o->ch[0]);
        }
    }
    void Query_Min(node *o)//查询平面中到目标点最近的点
    {
        ans=min(ans,abs(o->d[0]-P.x)+abs(o->d[1]-P.y));
        int dl=o->ch[0]?calc_mn(o->ch[0]):inf;
        int dr=o->ch[1]?calc_mn(o->ch[1]):inf;
        if(dl<dr)
        {
            if(dl<ans)
                Query_Min(o->ch[0]);
            if(dr<ans)
                Query_Min(o->ch[1]);
        }
        else
        {
            if(dr<ans)
                Query_Min(o->ch[1]);
            if(dl<ans)
                Query_Min(o->ch[0]);
        }
    }
    node *root;
    int Query(int x,int y,bool f)
    {
        P=Point(x,y);
        if(f)
            ans=-inf,Query_Max(root);
        else 
            ans=inf,Query_Min(root);
        return ans;
    }
    //以下三个函数为本人手写，所以可靠性有待验证，不过过过题....
    void debug(node *&a)
    {
        if(a->ch[0])
        {
            debug(a->ch[0]);
        }
        printf("%d %d\n",a->d[0],a->d[1]);
        if(a->ch[1])
        {
            debug(a->ch[1]);
        }
    }
    void del(node *&a)//用于清空整颗树
    {
        for(int i=0;i<=1;i++)
        {
            if(a->ch[i])
            {
                del(a->ch[i]);
            }
        }
        a=NULL;
    }
    void init()//用于初始化
    {
        del_top=del_pool,pool_top=pool_node;
    }
}