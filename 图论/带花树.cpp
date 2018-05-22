#include<bits/stdc++.h>
using namespace std;
namespace Flower
{
	//O(n^3)
	const int MAXN=250;
	bool Graph[MAXN][MAXN];
	int Match[MAXN];
	bool InQueue[MAXN],InPath[MAXN],InBlossom[MAXN];
	int Head,Tail;
	int Queue[MAXN];
	int Start,Finish;
	int NewBase;
	int Father[MAXN],Base[MAXN];
	int Count,N;//匹配数，匹配对数是Count/2
	void CreateGraph()
	{
		memset(Graph,false,sizeof(Graph));
		//建图
	}
	void Push(int u)
	{
		Queue[Tail]=u;
		Tail++;
		InQueue[u]=true;
	}
	int Pop()
	{
		int res=Queue[Head];
		Head++;
		return res;
	}
	int FindCommonAncestor(int u,int v)
	{
		memset(InPath,false,sizeof(InPath));
		while(true)
		{
			u=Base[u];
			InPath[u]=true;
			if(u==Start) break;
			u=Father[Match[u]];
		}
		while(true)
		{
			v=Base[v];
			if(InPath[v]) break;
			v=Father[Match[v]];
		}
		return v;
	}
	void ResetTrace(int u)
	{
		int v;
		while(Base[u]!=NewBase)
		{
			v=Match[u];
			InBlossom[Base[u]]=InBlossom[Base[v]]=true;
			u=Father[v];
			if(Base[u]!=NewBase) Father[u]=v;
		}
	}
	void BloosomContract(int u,int v)
	{
		NewBase=FindCommonAncestor(u,v);
		memset(InBlossom,false,sizeof(InBlossom));
		ResetTrace(u);
		ResetTrace(v);
		if(Base[u]!=NewBase) Father[u]=v;
		if(Base[v]!=NewBase) Father[v]=u;
		for(int tu=1;tu<=N;tu++)
			if(InBlossom[Base[tu]])
			{
				Base[tu]=NewBase;
				if(!InQueue[tu]) Push(tu);
			}
	}
	void FindAugmentingPath()
	{
		memset(InQueue,false,sizeof(InQueue));
		memset(Father,0,sizeof(Father));
		for(int i=1;i<=N;i++)
			Base[i]=i;
		Head=Tail=1;
		Push(Start);
		Finish=0;
		while(Head<Tail)
		{
			int u=Pop();
			for(int v=1;v<=N;v++)
				if(Graph[u][v]&&(Base[u]!=Base[v])&&(Match[u]!=v))
				{
					if((v==Start)||((Match[v]>0)&&Father[Match[v]]>0))
						BloosomContract(u,v);
					else if(Father[v]==0)
					{
						Father[v]=u;
						if(Match[v]>0)
							Push(Match[v]);
						else
						{
							Finish=v;
							return;
						}
					}
				}
		}
	}
	void AugmentPath()
	{
		int u,v,w;
		u=Finish;
		while(u>0)
		{
			v=Father[u];
			w=Match[v];
			Match[v]=u;
			Match[u]=v;
			u=w;
		}
	}
	void Edmonds()
	{
		memset(Match,0,sizeof(Match));
		for(int u=1;u<=N;u++)
			if(Match[u]==0)
			{
				Start=u;
				FindAugmentingPath();
				if(Finish>0) AugmentPath();
			}
	}
	void PrintMatch()
	{
		Count=0;
		for(int u=1;u<=N;u++)
			if(Match[u]>0)
				Count++;
		printf("%d\n",Count);
		for(int u=1;u<=N;u++)
			if(u<Match[u])
				printf("%d %d\n",u,Match[u]);
	}
}
void solve()
{
	Flower::CreateGraph();//建图
	Flower::Edmonds();//进行匹配
	Flower::PrintMatch();//输出匹配数和匹配
}
int main()
{
	int T;
	scanf("%d",&T);
	while(T--)
	{
		solve();
	}
	return 0;
}
