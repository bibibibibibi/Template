bool pzs(int k)//judge whether a number is a prime or not 
{
	if(k==2)
		return 1;
	for(int i=2;i*i<=k;i++)
	{
	    if(k%i==0)
		{
			return 0;
		}
	}
	return 1;
}
