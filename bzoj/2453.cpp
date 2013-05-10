//#define Debug
#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
const int MAXN = 10020;
namespace Data_BST {
	struct Node {
		Node *ch[2], *p;
		int size, v;
		inline bool dir(void){return p->ch[1] == this;}
		inline void SetC(Node *x, bool d) {
			x->p = this; ch[d] = x;
		}
	}Tnull, *null = &Tnull;

	class SplayTree {
		public:
		Node *root;

		SplayTree(){root = null;}
		void Updata(Node* t) {
			if (t == null) return;
			t->size = t->ch[0]->size + t->ch[1]->size + 1;
		}

		inline void rorate(Node *x) {
			Node *p = x->p; bool d = x->dir();
			p->p->SetC(x, p->dir());
			p->SetC(x->ch[!d], d);
			x->SetC(p, !d);
			Updata(p);
			if (p == root) root = x;
		}
		inline void Splay(Node *x, Node *G) {
			while (x->p != G)
				if (x->p->p == G)
					rorate(x);
				else if (x->p->dir() == x->dir()){
					rorate(x->p);rorate(x);
				} else {
					rorate(x); rorate(x);
				}
			Updata(x);
		}

		inline Node* Find(int x) {
			Node *t = root;
			while (t->v != x)
				if (x < t->v) t = t->ch[0]; else t = t->ch[1];
			return t;
		}

		inline Node* Next(int x) {
			Splay(Find(x), null);
			if (root->ch[1] == null) return null;
			Node *now = root->ch[1];
			while (now->ch[0] != null) now = now->ch[0];
			return now;
		}
		inline Node* Last(int x) {
			Splay(Find(x), null);
			if (root->ch[0] == null) return null;
			Node *now = root->ch[0];
			while (now->ch[1] != null) now = now->ch[1];
			return now;
		}
		
		int Succ(int x) {
			return Next(x)->v;
		}
		int Prev(int x) {
			return Last(x)->v;
		}

		Node* New(int x) {
			Node* now = new Node;
			now->v = x; now->ch[0] = now->ch[1] = null; now->size = 1;
			return now;
		}

		void Insert(int x, Node* &now, Node* last) {
			if (now == null) {
				now = New(x); now->p = last;
				Splay(now, null);
				return;
			}
			now->size++;
			if (x < now->v)
				Insert(x, now->ch[0], now);
			else
				Insert(x, now->ch[1], now);
		}

		void Push(int x) {
			Insert(x, root, null);
		}

		int Work(int x, Node *now) {
			if (now == null) return 0;
			if (now->v >= x)
				return Work(x, now->ch[0]);
			else
				return now->ch[0]->size + Work(x, now->ch[1]) + 1;
		}

		int Cal(int x) {
			return Work(x, root);
		}

		void Delete(int x) {
			Node *t;
			Splay(t = Find(x), null);
			if (t->ch[1] != null) {
				Splay(Next(t->v), root);
				t->ch[1]->SetC(root->ch[0], 0);
				root = t->ch[1];
			}else root = t->ch[0];
			root->p = null;
			Updata(root);
		}
	};
}

int a[MAXN];
namespace Segment_Tree {
	struct Node {
		int l, r; Node *lc, *rc;
		Data_BST::SplayTree T;
		void Change(int, int, int);
		int Cal(int, int, int);
	}Tnull, *null = &Tnull;

	Node* Build(int l, int r) {
		if (l > r)return null;
		if (l == r) {
			Node *t = new Node; t->l = t->r = l; t->lc = t->rc = null;
			t->T.Push(a[l]);
			return t;
		}
		int mid = (l + r) >> 1;
		Node *t = new Node;
		t->l = l, t->r = r;
		t->lc = Build(l, mid);
		t->rc = Build(mid + 1, r);
		for (int i = l; i <= r; i++)
			t->T.Push(a[i]);
		return t;
	}
	
	void Node::Change(int W, int last, int now) {
		if (this == null) return;
		int mid = (l + r) >> 1;
		if (W <= mid)
			lc->Change(W, last, now);
		else
			rc->Change(W, last, now);
		T.Delete(last);
		T.Push(now);
	}

	int Node::Cal(int left, int right, int low) {
		if (left > right) return 0;
		if (this == null) return 0;
		if (left <= l && r <= right)
			return T.Cal(low);
		int mid = (l + r) >> 1;
		return lc->Cal(left, std::min(right, mid), low) + rc->Cal(std::max(left, mid + 1), right, low);
	}
}
namespace Solve {
	inline int ScanInt(void) {
		int r, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	inline int ScanChar(void) {
		int c;
		while (c = getchar(), !isupper(c)) {}
		return c;
	}

	const int MAXM = 1000011;
	Data_BST::SplayTree M[MAXM];
	Segment_Tree::Node *root ;
	int c[MAXN];
	int n, Q;

	void Input(void) {
		n = ScanInt(), Q = ScanInt();
		for (int i = 1; i <= n; i++) {
			c[i] = ScanInt();
			M[c[i]].Push(i);
			a[i] = M[c[i]].Prev(i);
		}
	}

	inline void Trans(int l, int u) {
		if (a[l] == u) return;
		int t = a[l]; a[l] = u;
		root->Change(l, t, u);
	}

	void Ex(int u, int color) {
		int last = a[u];
		int N = M[c[u]].Succ(u);
		int P = M[c[u]].Prev(u);
		M[c[u]].Delete(u);
		if (N) 
			Trans(N, P);

		M[color].Push(u);
		N = M[color].Succ(u);
		P = M[color].Prev(u);
		if (N) 
			Trans(N, u);
		
		Trans(u, P);
		c[u] = color;
	}

	void Work(void) {
		root = Segment_Tree::Build(1, n);
		for (int _ = 1; _ <= Q; _++) {
			int c = ScanChar(), l = ScanInt(), r = ScanInt();
			if (c == 'Q') {
				int ret = 0;/*= root->Cal(l, r, l)*/;
				for (int i = l; i <= r; i++) if (a[i] < l) ret++;
				printf("%d\n", ret);
			}else {
				Ex(l, r);
			}
		}
	}

	void solve(void) {
		Input();
		Work();
	}
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
