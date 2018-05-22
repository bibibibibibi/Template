struct Trie
{
	int next[MAXN][2],fail[MAXN],end[MAXN];
	int root,L;
	int newnode()
	{
		for(int i=0;i<2;i++)
			next[L][i]=-1;
		end[L++]=0;
		return L-1;
	}
	void init()
	{
		L=0;
		root=newnode();
	}
	void insert(char buf[],int len)
	{
		int now=root;
		for(int i=0;i<len;i++)
		{
			if(next[now][buf[i]-'0']==-1)
				next[now][buf[i]-'0']=newnode();
			now=next[now][buf[i]-'0'];
		}
		end[now]=1;
	}
	void build()
	{
		queue<int>Q;
		fail[root]=root;
		for(int i=0;i<2;i++)
		{
			if(next[root][i]!=-1)
			{
				fail[next[root][i]]=root;
				Q.push(next[root][i]);
			}
		}
		while(!Q.empty())
		{
			int now=Q.front();
			Q.pop();
			for(int i=0;i<2;i++)
				if(next[now][i]!=-1)
				{
					int temp=fail[now];
					while(temp!=root&&next[temp][i]==-1)
					{
						temp=fail[temp];
					}
					fail[next[now][i]]=(next[temp][i]==-1)?root:next[temp][i];
					Q.push(next[now][i]);
				}
		}
	}
	int query(char buf[],int len)
	{
		int now=root;
		int res=0;
		for(int i=0;i<len;i++)
		{
			int temp=now;
			while(next[temp][buf[i]-'0']==-1&&temp!=root)
			{
				temp=fail[temp];
			}
			now=(next[temp][buf[i]-'0']==-1)?root:next[temp][buf[i]-'0'];
			temp=now;
			while(temp!=root)
			{
				res+=end[temp];
				temp=fail[temp];
			}
		}
		return res;
	}
}ac,tmp;