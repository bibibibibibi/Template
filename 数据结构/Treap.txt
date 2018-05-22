template<size_t N, typename T>
struct Treap
{
	struct Node
	{
		int pr, siz;
		T key;
		Node *child[2];
		inline int cmp(T v) const
		{
			if (v == key) return -1;
			else return v < key ? 0 : 1;
		}
		inline void maintain()
		{
			siz = child[0]->siz + child[1]->siz + 1;
		}
	} *root, *nil, pool[N], *alloc;
	Node* new_Node(T key)
	{
		Node* ret = alloc++;
		ret->key = key;
		ret->pr = rand();
		ret->siz = 1;
		ret->child[0] = ret->child[1] = nil;
		return ret;
	}
	void init()
	{
		alloc = pool;
		nil = new_Node(0);
		nil->siz = 0;
		root = nil;
	}
	void rotate(Node* &x, int dir)
	{//0 : 1 ? zag : zig
		Node* y = x->child[dir ^ 1];
		x->child[dir ^ 1] = y->child[dir];
		y->child[dir] = x;
		x->maintain(), y->maintain();
		x = y;
	}
	void insert(Node* temp, Node* &curr)
	{
		if (curr == nil) curr = temp;
		else
		{
			int dir = (temp->key < curr->key ? 0 : 1);
			insert(temp, curr->child[dir]);
			if (curr->child[dir]->pr > curr->pr)
				rotate(curr, dir ^ 1);
		}
		curr->maintain();
	}
	Node* erase(T key, Node* &curr)
	{
		int d = curr->cmp(key);
		Node* ret;
		if (d == -1)
		{
			if (curr->child[0] == nil) curr = curr->child[1];
			else if (curr->child[1] == nil) curr = curr->child[0];
			else
			{
				int dir = (curr->child[0]->pr > curr->child[1]->pr ? 1 : 0);
				rotate(curr, dir);
				erase(key, curr->child[dir]);
				curr->maintain();
			}
		}
		else
		{
			ret = erase(key, curr->child[d]);
			curr->maintain();
		}
		return ret;
	}
	T get(int k, Node* curr)
	{//第K小的值
		if (curr == nil || k <= 0 || k > curr->siz) return 0;
		int l = curr->child[0]->siz + 1;
		if (k == l) return curr->key;
		else if (k < l) return get(k, curr->child[0]);
		else return get(k - l, curr->child[1]);
	}
	int rank(T key, Node* curr)
	{//小于key的元素个数
		if (curr == nil) return 0;
		if (key <= curr->key)
			return rank(key, curr->child[0]);
		else return curr->child[0]->siz + 1 + rank(key, curr->child[1]);
	}
	T prec(T key, Node* curr)
	{
		if (curr == nil) return -INF;
		if (key <= curr->key)
			return prec(key, curr->child[0]);
		else return max(curr->key, prec(key, curr->child[1]));
	}
	T succ(T key, Node* curr)
	{
		if (curr == nil) return INF;
		if (key >= curr->key)
			return succ(key, curr->child[1]);
		else return min(curr->key, succ(key, curr->child[0]));
	}
	void merge(Node* x, Node* &y)
	{//启发式合并
		if (x->child[0] != nil) merge(x->child[0], y);
		if (x->child[1] != nil) merge(x->child[1], y);
		x->child[0] = x->child[1] = nil;
		insert(x, y);
	}
	void modify(T x, T y)
	{
		Node* temp = erase(x, root);
		temp->key = y;
		temp->child[0] = temp->child[1] = nil;
		insert(temp, root);
	}
};