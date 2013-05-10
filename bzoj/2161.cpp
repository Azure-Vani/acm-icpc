#include <cstdio>
#include <cassert>
#include <algorithm>
#include <vector>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 100010;
	const int Mod = 19921228;

	struct query {
		int value, type, p;
		query(int v, int t, int p):value(v), type(t), p(p){}
		inline friend bool operator <(const query& a, const query& b) {
			if (a.value == b.value) return a.type < b.type;
			else return a.value < b.value;
		}
	};
	std::vector<query> Q;

	int n;

	struct Node {
		Node *ch[2], *p; int value, size;
		inline bool dir(void) {return this == p->ch[1];}
		inline void Set(Node *x, bool d) {
			ch[d] = x, x->p = this;
		}
		void Update(void);
	}Tnull, *null = &Tnull;
	inline void Node::Update(void) {
		if (this == null) return;
		size = ch[0]->size + ch[1]->size + 1;
	}

	class TREE {public:
		Node *root;
		TREE(){root = null;}

		inline void rotate(Node *x) {
			Node *p = x->p; bool d = x->dir();
			p->p->Set(x, p->dir());
			p->Set(x->ch[!d], d);
			x->Set(p, !d);
			p->Update();
		}
		inline void Splay(Node *x, Node* G) {
			if (G == null) root = x;
			while (x->p != G) {
				if (x->p->p == G) rotate(x);
				else if (x->p->dir() == x->dir()) {
					rotate(x->p); rotate(x);
				}else {rotate(x); rotate(x);}
			}
			x->Update();
		}
		inline Node* Renew(int v) {
			Node* t = new Node;
			t->value = v, t->size = 1;
			t->p = t->ch[0] = t->ch[1] = null;
			return t;
		}
		inline void Insert(int value) {
			if (root == null) {root= Renew(value); return;}
			Node *now = root; bool d;
			while (now->ch[d = (value > now->value)] != null) now->size++, now = now->ch[d];
			now->Set(Renew(value), d);
			Splay(now->ch[d], null);
		}
		inline Node* Select(int k, Node *r) {
			Node *now = r, *L;
			if (now->size < k || k <= 0) return null;
			while (k) {
				L = now->ch[0];
				if (L->size + 1 == k) return now;
				if (L->size + 1 < k) 
					k -= L->size + 1, now = now->ch[1];
				else now = L;
			}
		}
		inline Node* Find(int value) {
			Node *now = root;
			while (true) {
				if (now->value == value) {Splay(now, null);return now;}
				else now = now->ch[value > now->value];
			}
		}
		inline void Delete(int value) {
			Node *now = Find(value);
			Splay(now, null);
			if (now->ch[0] == null || now->ch[1] == null) {
				bool d = (now->ch[1] != null);
				root = now->ch[d];
				null->Set(root, 0);
				return;
			}
			Node *L = Select(now->ch[0]->size, now->ch[0]), *R = Select(1, now->ch[1]);
			Splay(L, root); Splay(R, root);
			L->p = null; root = L; L->Set(R, 1); L->Update();
		}
	}T;

	inline void Input(int a[]) {
		int add, first, mod, prod;
		scanf("%d%d%d%d", &add, &first, &mod, &prod);
		a[1] = (first % mod);
		for (int i = 2; i <= n; i++) 
			a[i] = (Int64)((Int64) a[i - 1] * prod + (Int64)add + (Int64)i) % mod;
	}

	int L[MAXN], M[MAXN], R[MAXN], c[MAXN];
	inline void Push(int a[], int type) {
		for (int i = 1; i <= n; i++)
			Q.push_back(query(a[i], type, i));
	}

	inline int Work(void) {
		std::sort(Q.begin(), Q.end());
		Int64 Ans = 0, tmp = 0; int l = 0;
		for (int i = 0; i < Q.size(); i++) {
			tmp = 0;
			if (Q[i].type == 0) T.Insert(c[Q[i].p]), l++;
			if (Q[i].type == 1) tmp = (Int64) T.Select(l - Q[i].p + 1, T.root)->value;
			if (Q[i].type == 2) T.Delete(c[Q[i].p]), l--;
			assert(l == T.root->size);
			assert(null->size == 0);
			Ans = (Ans + tmp) % Mod;
		}
		return Ans;
	}

	inline void solve(void) {
		scanf("%d", &n);
		Input(M); Input(c); Input(L); Input(R); 
		for (int i = 1; i <= n; i++) if (L[i] > R[i]) std::swap(L[i], R[i]);
		Push(M,1); Push(L,0); Push(R,2);
		printf("%d\n", Work());
	}
}
int main(void) {
	//freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}
