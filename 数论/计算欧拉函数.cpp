int Phi(int x)
{
	int i,re=x;
	for(i=2;i*i<=x;i++)
		if(x%i==0)
		{
			re/=i;re*=i-1;
			while(x%i==0)
				x/=i;
		}
	if(x^1)
		re/=x,re*=x-1;
	return re;
}
