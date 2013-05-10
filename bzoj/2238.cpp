//#define Debug
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <algorithm>
#include <queue>
namespace Solve {
	const int MAXN = 50010;
	const int MAXM = 100010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (d = getchar(), !isdigit(d) && d != '-') {}
		if (d != '-') r = d - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return d == '-' ? -r : r;
	}

	struct Edge {
		int y; Edge *next, *opt; bool flag; int index;
		Edge(int y, Edge *next):y(y), next(next){flag = true;}
	}*a[MAXN];
	struct Pair {
		int x, y, z, index; bool mst;
	}E[MAXM];

	inline void AddEdge(int x, int y, int index) {
		a[x] = new Edge(y, a[x]);
		a[y] = new Edge(x, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
		a[x]->index = a[y]->index = index;
	}

	int n, m, Q;

	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1, x, y, z; i <= m; i++) {
			x = E[i].x = ScanInt(), y = E[i].y = ScanInt();
			z = E[i].z = ScanInt();
			E[i].index = i;
		}
	}

	inline bool cmp(const Pair& a, const Pair& b) {
		return a.z < b.z;
	}

	int f[MAXN];
	int Find(int x) {return x == f[x] ? x : (f[x] = Find(f[x]));}

	inline int MST(void) {
		int ret = 0;
		std::sort(E + 1, E + m + 1, cmp);
		for (int i = 1; i <= n; i++) f[i] = i;
		for (int i = 1; i <= m; i++) {
			int t1 = Find(E[i].x), t2 = Find(E[i].y);
			if (t1 == t2) continue;
			f[t1] = t2;
			ret += E[i].z;
			AddEdge(E[i].x, E[i].y, E[i].index);
			E[i].mst = true;
		}
		return ret;
	}

	int p[MAXN], d[MAXN], deep[MAXN];
	int pos[MAXN]; bool vis[MAXM];

	inline void Cut(void) {
		int head = 1, tail = 1; d[1] = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->flag) {
				p->opt->flag = false;
				deep[p->y] = deep[now] + 1;
				Solve::p[p->y] = now;
				pos[d[++tail] = p->y] = p->index;
			}
		}
	}

	int value[MAXM];
	inline void Cover(int a, int b, int c) {
		a = Find(a), b = Find(b);
		while (a != b) {
			if (deep[a] < deep[b]) std::swap(a, b);
			value[pos[a]] = c;
			f[a] = Find(p[a]);
			a = Find(a);
		}
	}

	inline bool comp(const Pair& a, const Pair& b) {
		return a.index < b.index;
	}

	inline void Prepare(void) {
		memset(value, -1, sizeof value);
		for (int i = 1; i <= n; i++) f[i] = i;
		for (int i = 1; i <= m; i++) if (!E[i].mst) {
			Cover(E[i].y, E[i].x, E[i].z);
		}
		std::sort(E + 1, E + m + 1, comp);
	}

	int _;
	inline void Work(void) {
		Q = ScanInt();
		for (int i = 1; i <= Q; i++) {
			int t = ScanInt();
			if (!E[t].mst) printf("%d\n", _);else if (value[t] == -1)
				puts("Not connected");
			else
				printf("%d\n", _ - E[t].z + value[t]);
		}
	}

	void solve(void) {
		Input();
		_ = MST();
		Cut();
		Prepare();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("mst.in", "r", stdin);
		freopen("mst.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
