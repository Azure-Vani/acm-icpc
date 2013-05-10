//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
namespace Data {
	struct Node {
		Node *ch[2], *p; int size, v;
		inline bool dir(void){return this == p->ch[1];}
		inline void SetC(Node* t, bool d) {
			t->p = this;
			ch[d] = t;
		}
		inline void Updata();
	}Tnull, *null = &Tnull;
	inline void Node::Updata(void) {if (this != null)size = ch[0]->size + ch[1]->size + 1;}

	class SplayTree {
		public:
		Node *root;
		SplayTree(){root = null;}
		inline void rotate(Node* x) {
			Node* p = x->p; bool d = x->dir();
			p->p->SetC(x, p->dir());
			p->SetC(x->ch[!d], d);
			x->SetC(p, !d);
			p->Updata();
		}
		inline void Splay(Node* x, Node* G) {
			while (x->p != G)
				if (x->p->p == G) rotate(x); else 
					if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x);}
					else {rotate(x); rotate(x);}
			if (G == null) root = x;
			x->Updata();
		}
		inline int Cal(int x) {
			int ret = 0; Node* t = root;
			while (t != null) {
				if (x > t->v) ret += t->ch[0]->size + 1, t = t->ch[1];
				else t = t->ch[0];
			}
			return ret;
		}
		inline Node* Renew(int x) {
			Node* t = new Node;
			t->v = x; t->size = 1; t->ch[0] = t->ch[1] = null;
			return t;
		}
		void Insert(int x, Node* &now, Node* last) {
			if (now == null) {
				now = Renew(x); now->p = last;
				Splay(now, null);
				return;
			}
			now->size++;
			if (x <= now->v)
				Insert(x, now->ch[0], now);
			else
				Insert(x, now->ch[1], now);
		}
		inline void Push(int x) {
			Insert(x, root, null);
		}
		inline Node* Find(int x) {
			Node *t = root;
			while (t->v != x)
				if (x < t->v) t = t->ch[0]; else t = t->ch[1];
			return t;
		}
		inline Node* GetMin(Node* t) {
			while (t->ch[0] != null) t = t->ch[0];
			return t;
		}
		inline void Delete(int x) {
			if (root == null || x == -1) return;
			Splay(Find(x), null);
			if (root->ch[1] == null) {
				root = root->ch[0];
				root->p = null;
				return;
			}else {
				Node* t = GetMin(root->ch[1]);
				Splay(t, root);
				t->SetC(root->ch[0], 0);
				root = root->ch[1];
				root->p = null;
				root->Updata();
			}
		}
	};
}

namespace Solve {
	const int MAXN = 10005;
	int c[MAXN];

	#define Lowbit(x) ((x) & (-(x)))
	class TreeArray {
		public:
		int n; Data::SplayTree a[MAXN];
		void Set(int k){n = k;}

		inline void Change(int where, int now) {
			for (int i = where; i <= n; i += Lowbit(i)) {
				a[i].Delete(c[where]);
				a[i].Push(now);
			}
		}

		inline int Count(int Where, int low) {
			int ret = 0;
			for (int i = Where; i > 0; i -= Lowbit(i))
				ret += a[i].Cal(low);
			return ret;
		}
		inline int Cal(int l, int r, int k) {
			return Count(r, k) - Count(l - 1, k);
		}
	};

	inline int ScanInt(void) {
		int c, r;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	inline int ScanChr(void) {
		int c;
		while (c = getchar(), !isupper(c)) {}
		return c;
	}

	int n, Q;
	TreeArray T;

	inline void Input(void) {
		n = ScanInt(), Q = ScanInt();
		T.Set(n);
		int t;
		for (int i = 1; i <= n; i++) {
			c[i] = -1;
			t = ScanInt();
			T.Change(i, t);
			c[i] = t;
		}
	}

	const int inf = 1000000002;
	inline int Work(int left, int right, int K) {
		int l = 0, r = inf;
		while (l <= r) {
			int mid = (l + r) >> 1;
			int Now = T.Cal(left, right, mid);
			if (Now > K - 1)
				r = mid - 1;
			else
				l = mid + 1;
		}
		return r;
	}

	inline void solve(void) {
		Input();
		for (int _ = 1; _ <= Q; _++) {
			int flag = ScanChr();
			if (flag == 'C') {
				int where = ScanInt(), num = ScanInt();
				T.Change(where, num);
				c[where] = num;
			}else {
				int l = ScanInt(), r = ScanInt(), k = ScanInt();
				int ret = Work(l, r, k);
				printf("%d\n", ret);
			}
		}
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
