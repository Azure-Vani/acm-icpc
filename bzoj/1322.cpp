#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 305;
	const int inf = 1050000000;

	inline int ScanInt(void) {
		int r = 0, c;
		while (!isdigit(c = getchar()));
		r = c - '0';
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y, f; Edge *next, *opt;
		Edge(int y, int f, Edge* next):y(y), f(f), next(next){}
	}*a[MAXN << 1];
	inline void AddEdge(int x, int y, int f) {
		a[x] = new Edge(y, f, a[x]);
		a[y] = new Edge(x, 0, a[y]);
		a[x]->opt = a[y], a[y]->opt = a[x];
	}

	int n, m, vs, vt;
	#define In(x) (((x) << 1) - 1)
	#define Out(x) (((x) << 1))

	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		vs = Out(n) + 1, vt = vs + 1;
		for (int i = 1; i <= n; i++) {
			int c = ScanInt();
			AddEdge(Out(i), vt, c);
		}
		for (int i = 1; i <= n; i++) {
			int c = ScanInt();
			AddEdge(vs, In(i), c);
		}
		while (m--) {
			int x = ScanInt(), y = ScanInt();
			AddEdge(In(x), Out(y), inf);
		}
	}

	int level[MAXN], d[MAXN];
	inline bool Bfs(void) {
		memset(level, -1, sizeof level);
		level[vs] = 0; d[1] = vs;
		int head = 1, tail = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && level[p->y] == -1)
				level[d[++tail] = p->y] = level[now] + 1;
		}
		return level[vt] != -1;
	}
	int Extend(int u, int sum) {
		if (u == vt) return sum;
		int r = 0, t;
		for (Edge *p = a[u]; p && r < sum; p = p->next) if (p->f > 0 && level[p->y] == level[u] + 1) {
			t = Extend(p->y, std::min(p->f, sum - r));
			p->f -= t, p->opt->f += t, r += t;
		}
		if (!r) level[u] = -1;
		return r;
	}
	int Dinic(void) {
		int r = 0, t;
		while (Bfs())
			while (t = Extend(vs, inf))
				r += t;
		return r;
	}

	void solve(void) {
		Input();
		printf("%d\n", Dinic());
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
