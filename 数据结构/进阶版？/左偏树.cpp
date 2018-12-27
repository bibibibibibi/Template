template<typename Tp>
struct Leftist_Tree
{
    /*大根堆*/
    struct heap
    {
        int l,r,d;
        Tp w;
    }h[MAXN];
    int rt[MAXN];//第i个堆的根的下标 
    /*合并以x,y为根的堆*/
    inline int merge(int x,int y)
    {
        //int t;
        //其中一个堆为空
        if(!x||!y) return x+y;
        //使得x,y两个根中x大
        if(h[x].w<h[y].w) swap(x,y);//int t=x;x=y;y=t;
        //保持堆两边的平衡
        h[x].r=merge(y,h[x].r);
        if(h[h[x].l].d<h[h[x].r].d) swap(h[x].l,h[x].r);//t=h[x].l;h[x].l=h[x].r;h[x].r=t;
        h[x].d=h[h[x].r].d+1;
        return x;
    }
    inline Tp pop(int x)
    {
        int l=h[x].l,r=h[x].r;
        h[x].l=h[x].r=h[x].w=0;
        return merge(l,r);
    }
    inline Tp top(x)
    {
        return h[x].w;
    }
};
