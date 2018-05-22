bool is_prime(int n)
{
    for(int i=2;i*i<=n;i++)
	{
        if(n%i==0) return false;
    }
    return n!=1;
}
  
void init_prime()  
{  
    int i,j,k;  
    prime[0]=prime[1]=1;  
    for(i=2;i<=MAXN;i++) 
	{  
        if(!prime[i])  
            for(j=i*i;j<=MAXN;j+=i)  
                prime[j]=1;  
    }
}
