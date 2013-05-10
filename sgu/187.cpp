#include <algorithm>
#include <cstdio>
#include <cctype>
using namespace std;

namespace Solve {
	const int MAXN = 130001;

	inline int ScanInt(void) {
		int r = 0, c;
		while (!isdigit(c = getchar())) ;
		r = c - '0';
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return r;
	}
	char ch[10];
	inline void Out(int v) {
		int l = 0; if (v == 0) putchar('0');
		while (v) ch[l++] = v % 10 + 48, v /= 10;
		while (--l >= 0) putchar(ch[l]);
	}

	int n, m;

	struct Node {
		Node *ch[2], *p; int sum, v; bool rev;
		inline bool dir(){return this == p->ch[1];}
		inline void SetC(Node *t, bool d) {ch[d] = t; t->p = this;}
		inline void Update(void) {sum = ch[0]->sum + ch[1]->sum + 1;}
		inline void Rev() {swap(ch[0], ch[1]); rev ^= 1;}
		inline void Down() {if (rev) ch[0]->Rev(), ch[1]->Rev(), rev = 0;}
	}Tnull, *null = &Tnull, data[MAXN], *pid = data;

	class SPLAY {public:
		Node *root;
		inline void rotate(Node *x) {
			x->p->Down(), x->Down();
			Node *p = x->p; bool d = x->dir();
			p->p->SetC(x, p->dir());
			p->SetC(x->ch[!d], d);
			x->SetC(p, !d);
			p->Update();
		}
		inline void splay(Node *x, Node *G) {
			if (G == null) root = x;
			while (x->p != G) {
				if (x->p->p == G) {rotate(x); break;}
				if (x->dir() == x->p->dir()) {rotate(x->p); rotate(x); } else {rotate(x); rotate(x);}
			}
			x->Update();
		}
		inline Node* Geth(int k) {
			Node *t = root;
			while (true) {
				t->Down();
				if (t->ch[0]->sum + 1 == k) return t;
				if (t->ch[0]->sum + 1 < k) k -= t->ch[0]->sum + 1, t = t->ch[1]; else t = t->ch[0];
			}
		}
		inline Node* GetInval(int l, int r) {
			Node *L = Geth(l), *R = Geth(r + 2);
			splay(L, null); splay(R, L);
			return R->ch[0];
		}
		inline Node* Build(int l, int r) {
			if (l > r) return null;
			int mid = (l + r) >> 1;
			Node *tmp = pid++; tmp->ch[0] = tmp->ch[1] = tmp->p = null; tmp->sum = 1, tmp->rev = 0, tmp->v = mid;
			if (l == r) return tmp;
			tmp->ch[0] = Build(l, mid - 1), tmp->ch[1] = Build(mid + 1, r);
			tmp->ch[0]->p = tmp->ch[1]->p = tmp;
			tmp->Update();
			return tmp;
		}
		inline void Print(Node *t) {
			if (t == null) return;
			t->Down();
			Print(t->ch[0]);
			if (t->v > 0 && t->v <= n) if (t->v == n) Out(t->v), putchar('\n'); else Out(t->v), putchar(' ');
			Print(t->ch[1]);
		}
		inline void Print(void) {
			Print(root);
		}
	}T;

	inline void solve(void) {
		n = ScanInt(), m = ScanInt();
		T.root = T.Build(0, n + 1);
		for (int i = 1; i <= m; i++) {
			int l = ScanInt(), r = ScanInt();
			T.GetInval(l, r)->Rev();
		}
		T.Print();
	}
}

int main(void) {
	//freopen("in", "r", stdin);
//	freopen("out", "w", stdout);
	Solve::solve();
	return 0;
}

