template<size_t N,typename T>
struct Persistent_Treap
{
	inline static int ran()
	{
		static int ret=1237;
		return ret=ret*12371237&0x7fffffff;
	}
	struct Node
	{
		int siz;
		T key,value,lazy;
		bool flip;
		Node* child[2];
		inline bool cmp(Node* x)const
		{
			return ran()%(siz+x->siz)<siz;
		}
		inline int size(int dir)const
		{
			return child[dir]?child[dir]->siz:0;
		}
		inline void maintain()
		{
			siz=1;
			value=key;
			for(int i=0;i<2;i++) 
				if(child[i])
				{
					siz+=child[i]->siz;
					value=min(value,child[i]->value);
				}
		}
		inline void update(T v)
		{
			key+=v;
			value+=v;
			lazy+=v;
		}
		inline void reverse()
		{
			swap(child[0],child[1]);
			flip=!flip;
		}
		inline void push_down()
		{
			if(lazy)
			{
				if(child[0]) child[0]->update(lazy);
				if(child[1]) child[1]->update(lazy);
				lazy=0;
			}
			if(flip)
			{
				if(child[0]) child[0]->reverse();
				if(child[1]) child[1]->reverse();
				flip=false;
			}
		}
	}*root[N],pool[N*50],*alloc;
	vector<Node*> bin;
	Node*& operator [](int i)
	{
		return root[i];
	}
	Node* new_Node(T key=0)
	{
		Node* ret;
		if(bin.empty()) ret=alloc++;
		else
		{
			ret=bin.back();
			bin.pop_back();
		}
		ret->siz=1;
		ret->key=ret->value=key;
		ret->lazy=0;
		ret->flip=false;
		ret->child[0]=ret->child[1]=NULL;
		return ret;
	}
	void init()
	{
		alloc=pool;
		bin.clear();
		root[0]=NULL;
	}
	Node* merge(Node* left,Node* right)
	{
		if(left==NULL&&right==NULL) return NULL;
		Node* ret=new_Node();
		if(left==NULL) memcpy(ret,right,sizeof(Node));
		else if(right==NULL) memcpy(ret,left,sizeof(Node));
		else
		{
			left->push_down(),right->push_down();
			if(left->cmp(right))
			{
				memcpy(ret,left,sizeof(Node));
				ret->child[1]=merge(left->child[1],right);
			}
			else
			{
				memcpy(ret,right,sizeof(Node));
				ret->child[0]=merge(left,right->child[0]);
			}
		}
		ret->maintain();
		ret->cnt=0;
		if(ret->child[0]) ret->child[0]->cnt++;
		if(ret->child[1]) ret->child[1]->cnt++;
		return ret;
	}
	void split(Node* curr,int k,Node* &left,Node* &right)
	{
		if(curr==NULL)
		{
			left=right=NULL;
			return;
		}
		curr->push_down();
		Node* temp=new_Node();
		memcpy(temp,curr,sizeof(Node));
		if(curr->size(0)>=k)
		{
			right=temp;
			split(curr->child[0],k,left,temp->child[0]);
		}
		else
		{
			left=temp;
			split(curr->child[1],k-curr->size(0)-1,
				temp->child[1],right);
		}
		temp->maintain();
		temp->cnt=0;
		if(temp->child[0]) temp->child[0]->cnt++;
		if(temp->child[1]) temp->child[1]->cnt++;
	}
	void recycle(Node* curr)//回收子树
	{	
		if(curr==NULL) return;
		if(--curr->cnt<=0)
		{
			recycle(curr->child[0]);
			recycle(curr->child[1]);
			bin.push_back(curr);
		}
	}
	Node* get(int x,int l,int r)
	{
		Node *left,*mid,*right,*temp;
		split(root[x],l-1,left,temp);
		split(temp,r-l+1,mid,right);
		recycle(left),recycle(right),recycle(temp);
		return mid;
	}
	Node* copy(Node* curr,int k)//把当前节点复制K次连起来
	{
		Node *ret=NULL,*base=new_Node();
		memcpy(base,curr,sizeof(Node));
		if(base->child[0]) base->child[0]->cnt++;
		if(base->child[1]) base->child[1]->cnt++;
		while(k)
		{
			if(k&1)
			{
				Node* temp=ret;
				ret=merge(ret,base);
				recycle(temp);
			}
			Node* temp=base;
			base=merge(base,base);
			recycle(temp);
			k>>=1;
		}
		recycle(base);
		return ret;
	}
	int rank(T key,Node* curr)//小于key的元素个数
	{
		if(curr==NULL) return 0;
		curr->push_down();
		if(key<=curr->key)
			return rank(key,curr->child[0]);
		else
			return curr->size(0)+1+rank(key,curr->child[1]);
	}
	void insert(int x,int k,T key)//在第K个位置插入
	{
		Node *left,*right,*mid=new_Node(key);
		split(root[x-1],k,left,right);
		Node* temp=merge(left,mid);
		root[x]=merge(temp,right);
		recycle(left),recycle(mid),recycle(right),recycle(temp);
	}
	void erase(int x,int k)//删除第K个位置的元素
	{
		Node *left,*mid,*right,*temp;
		split(root[x-1],k-1,left,temp);
		split(temp,1,mid,right);
		root[x]=merge(left,right);
		recycle(left),recycle(mid),recycle(right),recycle(temp);
	}
};
