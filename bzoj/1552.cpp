//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 100020;

	struct Node {
		Node *ch[2], *p; int size, v; bool rev;
		inline bool dir(void) {return this == p->ch[1];}
		inline void SetC(Node *x, bool d) {
			ch[d] = x, x->p = this;
		}
		inline void Pass(void) {
			if (rev) {
				std::swap(ch[1], ch[0]);
				ch[1]->rev ^= 1, ch[0]->rev ^= 1;
			}
			rev = false;
		}
		inline void Update(void) {size = ch[0]->size + ch[1]->size + 1;}
		void P(void);
	}Tnull, *null = &Tnull, *fim[MAXN];

	void Node::P(void) {
		Pass();
		if (ch[0] != null) ch[0]->P();
		printf("%d ", v);
		if (ch[1] != null) ch[1]->P();
	}

	class _ {public:
		Node *root;
		inline void rotate(Node *x) {
			Node *p = x->p; bool d = x->dir();
			p->Pass(); x->Pass();
			p->p->SetC(x, p->dir());
			p->SetC(x->ch[!d], d);
			x->SetC(p, !d);
			p->Update();
		}
		inline void Splay(Node *x, Node *G) {
			if (G == null) root = x;
			while (x->p != G) {
				if (x->p->p == G) {rotate(x); break;}
				else {
					x->p->p->Pass(); x->p->Pass();
					if (x->p->dir() == x->dir()) {rotate(x->p); rotate(x);}
					else {rotate(x); rotate(x);}
				}
			}
			x->Update(); x->Pass();
		}
		inline Node *Build(int l, int r, int a[]) {
			if (l > r) return null;
			int mid = (l + r) >> 1;
			Node *t = new Node; fim[a[mid]] = t;
			t->SetC(Build(l, mid - 1, a), 0);
			t->SetC(Build(mid + 1, r, a), 1);
			t->rev = false;
			t->size = r - l + 1; t->v = a[mid];
			return t;
		}
		inline int Rank(Node *x) {
			Splay(x, null);
			root->Pass();
			return root->ch[0]->size;
		}
		inline Node* Select(int k) {
			Node *t = root;
			while (t->Pass(), t->ch[0]->size + 1 != k)
				if (k <= t->ch[0]->size)
					t = t->ch[0];
				else
					k -= t->ch[0]->size + 1, t = t->ch[1];
			return t;
		}
		inline void Reverse(int l, int r) {
			Splay(Select(l), null);
			Splay(Select(r + 2), root);
			root->Pass(); root->ch[1]->Pass();
			root->ch[1]->ch[0]->rev ^= 1;
		}
	}T;

	int n, b[MAXN];
	inline void Work(void) {
		(T.root = T.Build(0, n + 1, b))->p = null;
		for (int i = 1, p; i < n; i++) {
			//T.root->P(); puts("");
			printf("%d ", p = T.Rank(fim[i]));
			T.Reverse(i, p);
		}
		printf("%d\n", n);
	}
	
	struct pair {
		int first, second;
		inline friend bool operator <(const pair& a, const pair& b) {
			if (a.first == b.first) return a.second < b.second;
			else return a.first < b.first;
		}
	}a[MAXN];

	inline void solve(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i].first), a[i].second = i;
		std::sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) b[a[i].second] = i;
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
