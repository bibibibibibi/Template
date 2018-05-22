#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
set<int> Left; 
int sv[maxn]={0};
map<int,int> l,r;
int cur=0,cul=0;
void fi(int i)
{
	set<int> :: iterator t;
	t=Left.lower_bound(sv[i]);
	if(t==Left.end())
	{
		t--;
		r[*t]=i;
	}
	else
	{
		if(l[*t]==0)
		{
			l[*t]=i;
		}
		else
		{
			t--;
			r[*t]=i;
		}
	}
	printf("%d ",*t);
	Left.insert(sv[i]);
}

int main()
{
	int n,i;
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%d",&sv[i]);
	}
	Left.insert(sv[0]);
	for(i=1;i<n;i++)
	{
		fi(i);
	}
}
