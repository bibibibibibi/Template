struct Matrix
{
    int n;
    ll a[MAXN][MAXN];
    Matrix(int _n=MAXN)
    {
        n=_n;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                a[i][j]=0;
    }
    Matrix operator * (const Matrix &B)const
    {
        Matrix C;C.n=n;
        for(int i=0;i<n;i++)
            for(int k=0;k<n;k++)
                for(int j=0;j<n;j++)
                    C.a[i][j]=(C.a[i][j]+(a[i][k]*B.a[k][j])%MOD)%MOD;
        return C;
    }
    Matrix operator + (const Matrix &B)const
    {
        Matrix C;C.n=n;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                C.a[i][j]=(a[i][j]+B.a[i][j])%MOD;
        return C;
    }
    Matrix operator % (const ll &t)const
    {
        Matrix A=(*this);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                A.a[i][j]%=MOD;
            }
        }
        return A;
    }
    Matrix operator ^ (const ll &t)const
    {
        Matrix A=(*this),res;
        ll p=t;
        res.n=n;
        for(int i=0;i<n;i++)
            res.a[i][i]=1;
        while(p)
        {
            if(p&1)res=res*A;
            A=A*A;
            p>>=1;
        }
        return res;
    }
    void debug()
    {
        for(int i=0;i<n;i++,printf("\n"))
            for(int j=0;j<n;j++)
                printf("%lld ",a[i][j]);
    }
    void reset()
    {
        for(int i=0;i<n;i++)
            a[i][i]=0;
    }
    bool judge()
    {
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                if((a[i][j]&&(i!=j))||((!a[i][j])&&(i==j)))
                    return false;
            }
        }
        return true;
    }
};
