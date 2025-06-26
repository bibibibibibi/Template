/*
 * Next[]的含义：x[i-Next[i]...i-1]=x[0...Next[i]-1] 
 * Next[i]为满足x[i-z...i-1]=x[0...z-1]的最大z值（就是x的自身匹配） 
 */
int j;
j=kmpNext[0]=0;
for(int i=1;i<n;i++)
{
	while(j>0 && x[i]!=x[j])j=kmpNext[j-1];
	if(x[i]==x[j]) j++;
	kmpNext[i]=j;
}
