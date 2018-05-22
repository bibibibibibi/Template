template<size_t N, typename T>
struct Scapegoat_tree
{
	static constexpr double alpha = 0.75;//平衡因子
	struct Node
	{
		int siz;
		T key;
		Node* child[2];
		inline int cmp(T v) const
		{
			if (v == key) return -1;
			else return v < key ? 0 : 1;
		}
		inline void maintain()
		{
			siz = 1;
			for (int i = 0; i < 2; i++) if (child[i])
				siz += child[i]->siz;
		}
		inline bool balance() const
		{//节点平衡条件
			for (int i = 0; i < 2; i++) if (child[i])
				if (child[i]->siz > alpha * siz) return false;
			return true;
		}
	} *root, pool[N], *alloc;
	vector<Node*> bin;
	Node* new_Node(T key)
	{
		Node* ret = alloc++;
		ret->key = key;
		ret->siz = 1;
		ret->child[0] = ret->child[1] = NULL;
		return ret;
	}
	void init()
	{
		alloc = pool;
		root = NULL;
	}
	void recycle(Node* curr)
	{//回收子树
		if (curr == NULL) return;
		recycle(curr->child[0]);
		bin.push_back(curr);
		recycle(curr->child[1]);
	}
	void rebuild(int left, int right, Node* &curr)
	{//重构
		if (left == right)
		{
			curr = NULL;
			return;
		}
		int mid = (left + right) / 2;
		curr = bin[mid];
		rebuild(left, mid, curr->child[0]);
		rebuild(mid + 1, right, curr->child[1]);
		curr->maintain();
	}
	void insert(T key, Node* &curr)
	{
		if (curr == NULL)
		{
			curr = new_Node(key);
			return;
		}
		int dir = key < curr->key ? 0 : 1;
		insert(key, curr->child[dir]);
		curr->maintain();
		if (!curr->balance())
		{
			bin.clear();
			recycle(curr);
			rebuild(0, bin.size(), curr);
		}
	}
	void erase(T key, Node* &curr)
	{
		int d = curr->cmp(key);
		if (d == -1)
		{
			if (curr->child[0])
			{
				Node* temp = curr->child[0];
				while (temp->child[1]) temp = temp->child[1];
				curr->key = temp->key;
				erase(temp->key, curr->child[0]);
			}
			else if (curr->child[1])
			{
				Node* temp = curr->child[1];
				while (temp->child[0]) temp = temp->child[0];
				curr->key = temp->key;
				erase(temp->key, curr->child[1]);
			}
			else curr = NULL;
		}
		else erase(key, curr->child[d]);
		if (curr == NULL) return;
		curr->maintain();
		if (!curr->balance())
		{
			bin.clear();
			recycle(curr);
			rebuild(0, bin.size(), curr);
		}
	}
};