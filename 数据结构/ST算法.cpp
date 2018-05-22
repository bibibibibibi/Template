/*
状态转移方程的含义是：先更新所有长度为F[i,0]即1个元素，然后通过2个1个元素的最值，
获得所有长度为F[i,1]即2个元素的最值，然后再通过2个2个元素的最值，获得所有长度为
F[i,2]即4个元素的最值，以此类推更新所有长度的最值。
然后是查询。
假如我们需要查询的区间为(i,j)，那么我们需要找到覆盖这个闭区间(左边界取i，右边界取j)的最小幂（可以重复，比如查询5，6，7，8，9，我们可以查询5678和6789）。
因为这个区间的长度为j - i + 1,所以我们可以取k=log2( j - i + 1)，则有：RMQ(A, i, j)=max{F[i , k], F[ j - 2 ^ k + 1, k]}。
举例说明，要求区间[2，8]的最大值，k = log2（8 - 2 + 1）= 2，即求max(F[2, 2]，F[8 - 2 ^ 2 + 1, 2]) = max(F[2, 2]，F[5, 2])；
*/ 
const int MAXN=1e5+5;
template<typename Tp>
struct RMQ
{
    int n;
    int len[MAXN];
    Tp mx[MAXN][21];
    Tp mi[MAXN][21];
    void build_rmq()
    {
        for(int j=1;(1<<j)<=n;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
            {
                mx[i][j]=max(mx[i][j-1],mx[i+(1<<(j-1))][j-1]);
                mi[i][j]=min(mi[i][j-1],mi[i+(1<<(j-1))][j-1]);
            }
    }
    int QueryMax(int L,int R)
    {
        int k=len[R-L+1];
        return max(mx[L][k],mx[R-(1<<k)+1][k]);
    }
    int QueryMin(int L,int R)
    {
        int k=len[R-L+1];
        return min(mi[L][k],mi[R-(1<<k)+1][k]);
    }
    void init(Tp *a,int sz)
    {
        n=sz;
        for(int i=1;i<=n;i++) 
            mx[i][0]=mi[i][0]=a[i];
        build_rmq();
        for(int i=0;i<=n;i++)
            len[i]=(i==0?-1:len[i>>1]+1);
    }
};
