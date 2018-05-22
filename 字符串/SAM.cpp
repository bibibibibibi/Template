namespace SAM
{
	const int CHAR=26;
	const int MAXN=1e6+5;
	struct SAM_Node
	{
		SAM_Node *fa,*next[CHAR];
		int mx,mi;//当前状态下最长的子串和最短的子串
		bool prefix;
		int id;
		SAM_Node(){}
		SAM_Node(int _mx)
		{
			fa=0;prefix=false;
			mx=_mx;
			memset(next,0,sizeof(next));
		}
	};
	SAM_Node SAM_node[MAXN*2],*SAM_root,*SAM_last;
	int SAM_size;
	SAM_Node *newSAM_Node(int len)
	{
		SAM_node[SAM_size]=SAM_Node(len);
		SAM_node[SAM_size].id=SAM_size;
		return &SAM_node[SAM_size++];
	}
	SAM_Node *newSAM_Node(SAM_Node *p)
	{
		SAM_node[SAM_size]=*p;
		SAM_node[SAM_size].id=SAM_size;
		return &SAM_node[SAM_size++];
	}
	void SAM_init()
	{
		SAM_size=0;
		SAM_root=SAM_last=newSAM_Node(0);
	}
	void SAM_add(int c)
	{
		SAM_Node *u=SAM_last,*z=newSAM_Node(u->mx+1);
		z->prefix=true;
		SAM_last=z;
		for(;u&&!u->next[c];u=u->fa)
			u->next[c]=z;
		if(!u)
		{
			z->fa=SAM_root;
			z->mi=1;
			return;
		}
		SAM_Node *x=u->next[c];
		if(x->mx==u->mx+1)//不用拆分
		{
			z->fa=x;
			z->mi=x->mx+1;
			return;
		}
		SAM_Node *y=newSAM_Node(x);//拆分x
		y->mx=u->mx+1;
		y->prefix=false;
		x->fa=y;x->mi=y->mx+1;
		z->fa=y;z->mi=y->mx+1;
		for(;u&&u->next[c]==x;u=u->fa)
			u->next[c]=y;
		y->mi=y->fa->mx+1;
	}
	void SAM_build(char *s)
	{
		SAM_init();
		int len=strlen(s);
		for(int i=0;i<len;i++)
			SAM_add(s[i]-'a');
	}
	//topo排序后获得每个点的endpos大小
	int cnt[MAXN*2],endpos[MAXN*2];
	void topo()
	{
		queue<int> Q;
		for(int i=0;i<SAM_size;i++)
		{
			if(SAM_node[i].fa)
			{
				int id=SAM_node[i].fa->id;
				cnt[id]++;
			}
		}
		for(int i=0;i<SAM_size;i++)
		{
			if(cnt[i]==0)
				Q.push(i);
		}
		while(!Q.empty())
		{
			int now=Q.front();
			Q.pop();
			if(SAM_node[now].prefix) endpos[now]++;
			if(SAM_node[now].fa)
			{
				int id=SAM_node[now].fa->id;
				endpos[id]+=endpos[now];
				if(--cnt[id]==0)
					Q.push(id);
			}
		}
	}
}
//加入串后进行拓扑排序。
char str[MAXN];
int topocnt[MAXN];
SAM_Node *topsam[MAXN*2];
int n=strlen(str);
SAM_build(str);
memset(topocnt,0,sizeof(topocnt));
for(int i=0;i<SAM_size;i++)
	topocnt[SAM_node[i].len]++;
for(int i=1;i<=n;i++)
	topocnt[i]+=topocnt[i-1];
for(int i=0;i<SAM_size;i++)
	topsam[--topocnt[SAM_node[i].len]]=&SAM_node[i];
//多串的建立：
//多串的建立,注意SAM_init()的调用
void SAM_build(char *s)
{
	int len=strlen(s);
	SAM_last=SAM_root;
	for(int i=0;i<len;i++)
	{
		if(!SAM_last->next[s[i]-'0']||!(SAM_last->next[s[i]-'0']->len==i+1))
			SAM_add(s[i]-'0',i+1);
		else
			SAM_last=SAM_last->next[s[i]-'0'];
	}
}