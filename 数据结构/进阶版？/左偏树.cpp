template<typename Tp>
struct Heap
{
    /*大根堆*/
    struct node
    {
        int l,r,d,rt;
        Tp w;
        void reset()
        {
            l=r=d=w=rt=0;
        }
        void newnode(Tp _w=0)
        {
            reset();
            w=_w;
        }
    }h[MAXN];
    int tot;
    /*合并以x,y为根的堆*/
    Heap()
    {
        tot=0;
    }

    void reset()
    {
        tot=0;
    }

    inline int findrt(int now)
    {
        return now==h[now].rt?now:h[now].rt=findrt(h[now].rt);
    }

    int newnode(Tp w)
    {
        tot++;
        h[tot].newnode(w);
        h[tot].rt=tot;
        return tot;
    }
    
    int merge(int x,int y)
    {
        if(!x||!y) return x+y;
        if(h[x].w<h[y].w) swap(x,y);
        h[x].r=merge(h[x].r,y);
        h[h[x].r].rt=x;
        if(h[h[x].l].d<h[h[x].r].d)
            swap(h[x].l,h[x].r);
        h[x].d=h[h[x].r].d+1;
        return x;
    }

    Tp pop(int x)
    {
        x=findrt(x);
        int L=h[x].l,R=h[x].r;
        h[L].rt=L;h[R].rt=R;
        //todo增加节点回收机制
        //h[x].reset();没有回收机制暂时先不reset
        return merge(L,R);
    }

    Tp top(int x)
    {
        return h[findrt(x)].w;
    }

    int insert(int x,int v)
    {
        x=findrt(x);
        return merge(x,newnode(v));
    }
};
