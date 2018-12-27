//查询二维平面一个子矩阵中点的个数
//其中Tree相当于set，但是可以查找小于某个数的数目
//如果允许插入重点，可以使用 pair<int,int> 作为 Key
/*
栗子：反复插入1这个点，可以打标签实现multiset的作用

Tree<pii> T;
T.insert({1,1});
cout<<T.order_of_key({1,INF})<<endl;
T.insert({1,2});
cout<<T.order_of_key({1,INF})<<endl;
*/

#include<bits/stdc++.h>
#include<ext/pb_ds/tree_policy.hpp>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/rope>
#define xx first
#define yy second
#define mp make_pair
#define pb push_back
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;
typedef long long ll;
typedef pair<int,int> pii;
template <class T> using Tree=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
const int MAXN=1e5+5;
const int INF=0x3f3f3f3f;

template<int SZ>
struct mstree
{ 
    Tree<int> val[SZ+1];// for offline queries use vector with binary search instead
    void upd(int x,int y,int opt=1)
    {// x-coordinate between 1 and SZ inclusive
        for(int i=x;i<=SZ;i+=i&-i) 
        {
            if(opt) val[i].insert(y);
            else val[i].erase(y);
        }
    }

    int query(int x,int y)
    { 
        int ret=0;    
        for(;x>0;x-=x&-x) ret+=val[x].order_of_key(y+1);
        return ret;
    }

    int query(int lox, int hix, int loy, int hiy)
    {// query number of elements within a rectangle
        return query(hix,hiy)-query(lox-1,hiy)
        -query(hix,loy-1)+query(lox-1,loy-1);
    }
};
int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	
	return 0;
}
