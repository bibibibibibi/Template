#include<cstdio>

int main()
{
    int n,i,j,num,h[1000],max[1000];
    while(~scanf("%d",&n))
    {
        num=0;
        for(i=0;i<n;++i)
        {
            scanf("%d",&h[i]);
            max[i]=1;
        }
        for(i=1;i<n;++i)
		{
			for(j=0;j<i;++j)
            {
                if(h[j]<=h[i]&&max[j]+1>max[i])
                {
                	max[i]=max[j]+1;
				} 
                if(num<max[i])
                {
				    num=max[i];
				}
            }
		}
        printf("%d\n",num);
    }
    return 0;
}
