int MaxSubSequence(const int A[], int N)
{
	int ThisSum,MaxSum,j;
	ThisSum = MaxSum =0;
	for(j = 0;j < N;j++)
	{
		ThisSum += A[j]; 
		if(ThisSum > MaxSum)
			MaxSum = ThisSum;
		else if(ThisSum < 0)
			ThisSum = 0;
	}
	return MaxSum; 
}
