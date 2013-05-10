//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
namespace DATA {
	const int MAXN = 100050;
	struct info {
		int L, R, t, cover;
		info():L(0), R(0), t(0), cover(-1){}
	};
	inline info Merge(const info& a, const info& b) {
		if (a.t == 0) return b;
		if (b.t == 0) return a;
		info c;
		c.L = a.L, c.R = b.R;
		c.t = a.t + b.t - (a.R == b.L);
		return c;
	}

	class Node {public:
		int l, r; info Info; Node *ch[2];
		
		inline int& RR(void) {return Info.R;}
		inline int& LL(void) {return Info.L;}
		inline int& TT(void) {return Info.t;}
		
		inline void Set(int c) {
			Info.cover = Info.L = Info.R = c;
			Info.t = 1;
		}
		inline void Pass(void) {
			if (Info.cover != -1 && ch[0] != NULL) {
				ch[0]->Set(Info.cover);
				ch[1]->Set(Info.cover);
				Info.cover = -1;
			}
		}
		inline void Updata(void) {
			if (!ch[0]) return;
			Info.L = ch[0]->Info.L;
			Info.R = ch[1]->Info.R;
			Info.t = ch[0]->Info.t + ch[1]->Info.t - (ch[0]->RR() == ch[1]->LL());
		}

		void Build(int a[], int L, int R) {
			l = L, r = R;
			if (L == R) {
				Info.L = Info.R = a[L];
				Info.t = 1; ch[0] = ch[1] = NULL;
				return;
			}
			int mid = (L + R) >> 1;
			ch[0] = new Node; ch[0]->Build(a, L, mid);
			ch[1] = new Node; ch[1]->Build(a, mid + 1, R);
			Updata();
		}

		info Ask(int L, int R) {
			if (L > R) return info();
			if (L <= l && r <= R) return Info;
			Pass();
			int mid = (l + r) >> 1;
			info Li = ch[0]->Ask(L, std::min(R, mid));
			info Ri = ch[1]->Ask(std::max(L, mid + 1), R);
			return Merge(Li, Ri);
		}

		void Trans(int L, int R, int color) {
			if (L > R) return;
			if (L <= l && r <= R) {
				Set(color);
				return;
			}
			Pass();
			int mid = (l + r) >> 1;
			ch[0]->Trans(L, std::min(R, mid), color);
			ch[1]->Trans(std::max(mid + 1, L), R, color);
			Updata();
		}
	}*root[MAXN];

	class SegmentTree {public:
		void Make(int a[], int n, int which) {
			root[which] = new Node;
			root[which]->Build(a, 1, n);
		}
		info Ask(int l, int r, int which) {
			return root[which]->Ask(l, r);
		}
		void Trans(int l, int r, int color, int which) {
			root[which]->Trans(l, r, color);
		}
	};
}

namespace Solve {
	const int MAXN = DATA::MAXN;

	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	inline int ScanChr(void) {
		int c;
		while (c = getchar(), !isupper(c)) {}
		return c;
	}

	struct Edge {
		int y; Edge *next, *opt; bool flag;
		Edge(int y, Edge *next):next(next), y(y) {flag = true;}
	}*a[MAXN];
	inline void AddEdge(int x, int y) {
		a[x] = new Edge(y, a[x]);
		a[y] = new Edge(x, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}

	int n, m, c[MAXN];
	void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) c[i] = ScanInt();
		for (int i = 1; i < n; i++) {
			int x = ScanInt(), y = ScanInt();
			AddEdge(x, y);
		}
	}

	DATA::SegmentTree T;
	int Son[MAXN], p[MAXN], belong[MAXN], d[MAXN], head = 1, tail = 0, deep[MAXN], Sum[MAXN];
	int seg[MAXN], index[MAXN];
	void Cut(void) {
		d[++tail] = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->flag) {
				p->opt->flag = false;
				deep[p->y] = deep[now] + 1;
				d[++tail] = p->y;
				Solve::p[p->y] = now;
			}
		}
		for (int i = tail; i >= 1; i--) Sum[d[i]]++, Sum[p[d[i]]] += Sum[d[i]];
		for (int i = 1; i <= tail; i++) {
			int t = d[i], best = 0;
			if (!belong[t]) belong[t] = t;
			for (Edge *p = a[t]; p; p = p->next) if (p->flag && Sum[p->y] > best)
				best = Sum[p->y], Son[t] = p->y;
			belong[Son[t]] = belong[t];
		}
		
		for (int i = tail; i >= 1; i--) {
			int now = d[i]; if (Son[now] > 1) continue;
			int L = 0;
			for (;now != belong[now]; now = p[now]) {
				seg[++L] = c[now];
				index[now] = L;
			}
			seg[++L] = c[now], index[now] = L;
			T.Make(seg, L, now);
		}
	}

	inline int LCA(int a, int b) {
		while (true) {
			if (deep[a] > deep[b]) std::swap(a, b);
			if (belong[a] == belong[b]) return a;
			if (deep[belong[a]] > deep[belong[b]]) std::swap(a, b);
			b = p[belong[b]];
		}
	}

	inline DATA::info Answer(int now, int A) {
		DATA::info ret, tmp;
		while (true) {
			int father = belong[now];
			if (deep[father] <= deep[A]) {
				tmp = T.Ask(index[now], index[A], father);
				ret = DATA::Merge(ret, tmp);
				break;
			}
			tmp = T.Ask(index[now], index[father], father);
			ret = Merge(ret, tmp);
			now = p[father];
		}
		return ret;
	}

	inline void Gao(int x, int A, int color) {
		while (true) {
			int father = belong[x];
			if (deep[father] <= deep[A]) {
				T.Trans(index[x], index[A], color, father);
				break;
			}
			T.Trans(index[x], index[father], color, father);
			x = p[father];
		}
	}

	void Work(void) {
		for (int i = 1; i <= m; i++) {
			int type = ScanChr();
			if (type == 'Q') {
				DATA::info A, B;
				int x = ScanInt(), y = ScanInt();
				int lca = LCA(x, y);
				A = Answer(x, lca);
				B = Answer(y, lca);
				int Ans = A.t + B.t - (A.R == B.R);
				printf("%d\n", Ans);
			}else {
				int x = ScanInt(), y = ScanInt(), c = ScanInt();
				int lca = LCA(x, y);
				Gao(x, lca, c);
				Gao(y, lca, c);
			}
		}
	}
	void solve(void) {
		Input();
		Cut();
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
