const int MOD = 10007;
int INV[MOD];
//求ax = 1( mod m) 的x值，就是逆元(0<a<m)
long long inv(long long a,long long m)
{
    if(a==1)return 1;
    return inv(m%a,m)*(m-m/a)%m;
}
struct Matrix
{
    int mat[330][330];
    void init()
    {
        memset(mat,0,sizeof(mat));
    }
    int det(int n)//求行列式的值模上MOD，需要使用逆元
    {
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                mat[i][j]=(mat[i][j]%MOD+MOD)%MOD;
        int res=1;
        for(int i=0;i<n;i++)
        {
            for(int j=i;j<n;j++)
                if(mat[j][i]!=0)
                {
                    for(int k=i;k<n;k++)
                        swap(mat[i][k],mat[j][k]);
                    if(i!=j)
                        res=(-res+MOD)%MOD;
                    break;
                }
            if(mat[i][i]==0)
            {
                res = -1;//不存在(也就是行列式值为0)
                break;
            }
            for(int j=i+1;j<n;j++)
            {
                //int mut = (mat[j][i]*INV[mat[i][i]])%MOD;//打表逆元
                int mut = (mat[j][i]*inv(mat[i][i],MOD))%MOD;
                for(int k = i;k < n;k++)
                    mat[j][k] = (mat[j][k]-(mat[i][k]*mut)%MOD+MOD)%MOD;
            }
            res=(res*mat[i][i])%MOD;
        }
        return res;
    }
};
Matrix ret;
        ret.init();
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i!=j&&g[i][j])
                {
                    ret.mat[i][j]=-1;
                    ret.mat[i][i]++;
                }
        printf("%d\n",ret.det(n-1));
