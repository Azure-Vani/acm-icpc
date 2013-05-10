#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>

using namespace std;

namespace Solve {
	const int MAXN = 500010;
	const int inf = 500000000;

	char BUF[50000000], *pos = BUF;
	inline int ScanInt(void) {
		int r = 0, d = 0;
		while (!isdigit(*pos) && *pos != '-') pos++;
		if (*pos != '-') r = *pos - 48; else d = 1; pos++;
		while ( isdigit(*pos)) r = r * 10 + *pos++ - 48;
		return d ? -r : r;
	}
	inline void ScanStr(char *st) {
		int l = 0;
		while (!(isupper(*pos) || *pos == '-')) pos++;
		st[l++] = *pos++;
		while (isupper(*pos) || *pos == '-') st[l++] = *pos++; st[l] = 0;
	}

	struct Node {
		Node *ch[2], *p;
		int v, lmax, rmax, m, same, rev, sum, size;
		inline bool dir(void) {return this == p->ch[1];}
		inline void SetC(Node *x, bool d) {ch[d] = x, x->p = this;}
		inline void Update(void) {
			Node *L = ch[0], *R = ch[1];
			size = L->size + R->size + 1;
			m = max(L->m, R->m);
			m = max(m, L->rmax + v + R->lmax);
			lmax = max(L->lmax, L->sum + v + R->lmax);
			rmax = max(R->rmax, R->sum + v + L->rmax);
			sum = L->sum + R->sum + v;
		}
		inline void Rev(void) {
			if (v == -inf) return;
			rev ^= 1;
			swap(ch[0], ch[1]);
			swap(lmax, rmax);
		}
		inline void Same(int u) {
			if (v == -inf) return;
			same = u;
			sum = u * size;
			if (sum > 0) lmax = rmax = m = sum; else lmax = 0, rmax = 0, m = u;
			v = u;
		}
		inline void Down(void) {
			if (rev) {
				ch[0]->Rev(), ch[1]->Rev();
				rev = 0;
			}
			if (same != -inf) {
				ch[0]->Same(same), ch[1]->Same(same);
				same = -inf;
			}
		}
	} Tnull, *null = &Tnull;

	class Splay {public:
		Node *root;
		inline void rotate(Node *x) {
			Node *p = x->p; bool d = x->dir();
			p->Down(); x->Down();
			p->p->SetC(x, p->dir());
			p->SetC(x->ch[!d], d);
			x->SetC(p, !d);
			p->Update();
		}
		inline void splay(Node *x, Node *G) {
			if (G == null) root = x;
			while (x->p != G) {
				if (x->p->p == G) {rotate(x); break;}
				else {if (x->dir() == x->p->dir()) rotate(x->p), rotate(x); else rotate(x), rotate(x);}
			}
			x->Update();
		}
		inline Node *Select(int k) {
			Node *t = root;
			while (t->Down(), t->ch[0]->size + 1 != k) {
				if (k > t->ch[0]->size + 1) k -= t->ch[0]->size + 1, t = t->ch[1];
				else t = t->ch[0];
			}
			splay(t, null);
			return t;
		}
		inline Node *getInterval(int l, int r) {
			Node *L = Select(l), *R = Select(r + 2);
			splay(L, null); splay(R, L);
			L->Down(); R->Down();
			return R;
		}
		inline void Insert(int pos, Node *x) {
			Node *now = getInterval(pos + 1, pos);
			now->SetC(x, 0);
			now->Update(); root->Update();
		}
		inline void Delete(int l, int r) {
			Node *now = getInterval(l, r);
			now->ch[0] = null;
			now->Update(); root->Update();
		}
		inline void Make(int l, int r, int c) {
			Node *now = getInterval(l, r);
			now->ch[0]->Same(c);
			now->Update(); root->Update();
		}
		inline void Reverse(int l, int r) {
			Node *now = getInterval(l, r);
			now->ch[0]->Rev();
			now->Update(); root->Update();
		}
		inline int Sum(int l, int r) {
			Node *now = getInterval(l, r);
			root->Down(); now->Down();
			return now->ch[0]->sum;
		}
		inline int maxSum(int l, int r) {
			Node *now = getInterval(l, r);
			root->Down(); now->Down();
			return now->ch[0]->m;
		}
		inline Node* Renew(int c) {
			Node *ret = new Node;
			ret->ch[0] = ret->ch[1] = ret->p = null; ret->size = 1;
			ret->Same(c); ret->same = -inf;
			return ret;
		}
		inline Node* Build(int l, int r, int *a) {
			if (l > r) return null;
			int mid = (l + r) >> 1;
			Node *ret = Renew(a[mid]);
			ret->ch[0] = Build(l, mid - 1, a);
			ret->ch[1] = Build(mid + 1, r, a);
			ret->ch[0]->p = ret->ch[1]->p = ret;
			ret->Update();
			return ret;
		}
		inline void P(Node *t) {
			if (t == null) return;
			t->Down(); t->Update();
			P(t->ch[0]);
			printf("%d ", t->v);
			P(t->ch[1]);
		}
	}T;


	int a[MAXN]; char ch[10];

	inline void solve(void) {
		fread(BUF, 1, 50000000, stdin);
		null->same = null->m = null->v = -inf;
		int kase = ScanInt();
		while (kase--) {
			int n = ScanInt(), m = ScanInt();
			for (int i = 1; i <= n; i++) a[i] = ScanInt();
			T.root = T.Build(0, n + 1, a);
			for (int i = 1; i <= m; i++) {
				ScanStr(ch);
				if (strcmp(ch, "INSERT") == 0) {
					int pos = ScanInt(), t = ScanInt();
					for (int j = 1; j <= t; j++) a[j] = ScanInt();
					Node *tmp = T.Build(1, t, a);
					T.Insert(pos, tmp);
				}
				if (strcmp(ch, "DELETE") == 0) {
					int l = ScanInt(), r = ScanInt(); r = l + r - 1;
					T.Delete(l, r);
				}
				if (strcmp(ch, "MAKE-SAME") == 0) {
					int l = ScanInt(), r = ScanInt(), c = ScanInt(); r = l + r - 1;
					T.Make(l, r, c);
				}
				if (strcmp(ch, "REVERSE") == 0) {
					int l = ScanInt(), r = ScanInt(); r = l + r - 1;
					T.Reverse(l, r);
				}
				if (strcmp(ch, "GET-SUM") == 0) {
					int l = ScanInt(), r = ScanInt(); r = l + r - 1;
					int ret = T.Sum(l, r);
					printf("%d\n", ret);
				}
				if (strcmp(ch, "MAX-SUM") == 0) {
					int ret = T.maxSum(1, T.root->size - 2);
					printf("%d\n", ret);
				}
			}
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}

