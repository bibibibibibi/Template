template<size_t N, typename T>
struct Splay_tree
{
	struct Node
	{
		int siz;
		T key, value, lazy;
		bool flip;
		Node *child[2], *parent;
		inline void maintain()
		{
			siz = child[0]->siz + child[1]->siz + 1;
			value = child[0]->value + child[1]->value + key;
		}
		inline void update(T v)
		{
			if (siz == 0) return;
			key += v;
			value += siz * v;
			lazy += v;
		}
		inline void reverse()
		{
			swap(child[0], child[1]);
			flip = !flip;
		}
		inline void push_down()
		{
			if (flip)
			{
				child[0]->reverse();
				child[1]->reverse();
				flip = false;
			}
			if (lazy)
			{
				child[0]->update(lazy);
				child[1]->update(lazy);
				lazy = 0;
			}
		}
		inline bool isroot() const
		{
			if (this->parent->siz == 0) return true;
			return this->parent->child[0] != this &&
				this->parent->child[1] != this;
		}
	} *nil, pool[N], *alloc;
	Node* new_Node(T key)
	{
		Node* ret = alloc++;
		ret->siz = 1;
		ret->key = ret->value = key;
		ret->lazy = 0;
		ret->flip = false;
		ret->child[0] = ret->child[1] = ret->parent = nil;
		return ret;
	}
	void init()
	{
		alloc = pool;
		nil = new_Node(0);
		nil->siz = 0;
	}
	void build(int left, int right, T* key, Node* &curr)
	{
		if (left == right) return;
		int mid = (left + right) / 2;
		curr = new_Node(key[mid]);
		build(left, mid, key, curr->child[0]);
		curr->child[0]->parent = curr;
		build(mid + 1, right, key, curr->child[1]);
		curr->child[1]->parent = curr;
		curr->maintain();
	}
	void rotate(Node* x)
	{//0 : 1 ? zag : zig
		Node* y = x->parent;
		int dir = (y->child[0] == x ? 1 : 0);
		y->child[dir ^ 1] = x->child[dir];
		x->child[dir]->parent = y;
		x->parent = y->parent;
		if (!y->isroot())
		{
			if (y == y->parent->child[0])
				y->parent->child[0] = x;
			else y->parent->child[1] = x;
		}
		x->child[dir] = y;
		y->parent = x;
		y->maintain();
	}
	void update(Node* curr)
	{
		if (!curr->isroot()) update(curr->parent);
		curr->push_down();
	}
	void splay(Node* x)
	{
		update(x);
		while (!x->isroot())
		{
			Node *y = x->parent, *z = y->parent;
			if (!y->isroot())
			{
				if ((z->child[0] == y) == (y->child[0] == x))
					rotate(y);
				else rotate(x);
			}
			rotate(x);
		}
		x->maintain();
	}
	Node* get(int k, Node* curr)
	{//第K个位置的节点
		curr->push_down();
		int l = curr->child[0]->siz + 1;
		if (k == l) return curr;
		else if (k < l) return get(k, curr->child[0]);
		else return get(k - l, curr->child[1]);
	}
	Node* prec(Node* curr)
	{
		splay(curr);
		Node* ret = curr->child[0];
		while (ret != nil && ret->child[1] != nil)
		{
			ret = ret->child[1];
			ret->push_down();
		}
		return ret;
	}
	Node* succ(Node* curr)
	{
		splay(curr);
		Node* ret = curr->child[1];
		while (ret != nil && ret->child[0] != nil)
		{
			ret = ret->child[0];
			ret->push_down();
		}
		return ret;
	}
	void insert(int k, T key, Node* curr)
	{
		curr = get(k, curr);
		splay(curr);
		Node* temp = new_Node(key);
		temp->child[0] = curr;
		curr->parent = temp;
		temp->child[1] = curr->child[1];
		curr->child[1]->parent = temp;
		curr->child[1] = nil;
		curr->maintain();
		temp->maintain();
	}
	void erase(int k, Node* curr)
	{
		curr = get(k, curr);
		Node *temp = prec(curr);
		splay(temp), splay(curr);
		temp->child[1] = curr->child[1];
		temp->child[1]->parent = temp;
		temp->parent = nil;
	}
	void split(Node* curr, int k, Node* &left, Node* &right)
	{//从第K个节点处分裂
		Node* temp = get(k, curr);
		splay(temp);
		right = temp->child[1];
		left = temp;
		left->child[1] = right->parent = nil;
		left->maintain();
	}
	Node* merge(Node* left, Node* right)
	{
		Node* ret = get(left->siz, left);
		splay(ret);
		ret->child[1] = right;
		right->parent = ret;
		ret->maintain();
		return ret;
	}
};
