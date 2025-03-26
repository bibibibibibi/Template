namespace SAM
{
	const int CHAR=26;
	const int MAXN=1e6+5;
	struct node
	{
		int len,link,firstpos;
		int next[CHAR];
	}st[MAXN*2];
	int sz,last;
	void init()
	{
		st[0].len=0;
		st[0].link=-1;
		st[0].firstpos=0;
		sz++;
		last=0;
	}
	void extend(int c)
	{
		int cur=sz++;
		st[cur].len=st[last].len+1;
		st[cur].firstpos=st[cur].len;//firstpos从1开始
		int p=last;
		while(p!=-1&&!st[p].next[c])
		{
			st[p].next[c]=cur;
			p=st[p].link;
		}
		if(p==-1)
			st[cur].link=0;
		else
		{
			int q=st[p].next[c];
			if(st[p].len+1==st[q].len)
				st[cur].link=q;
			else
			{
				int clone=sz++;
				st[clone].len=st[p].len+1;
				st[clone].link=st[q].link;
				st[clone].firstpos=st[q].firstpos;
				memcpy(st[clone].next,st[q].next,sizeof(st[q].next));
				while(p!=-1&&st[p].next[c]==q)
				{
					st[p].next[c]=clone;
					p=st[p].link;
				}
				st[q].link=st[cur].link=clone;
			}
		}
		last=cur;
	}
}
