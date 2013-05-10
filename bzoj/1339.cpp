//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
namespace Solve {
	const int MAXN = 505;
	const int inf = 1000000000;
	struct Edge {
		int y, f; Edge *next, *opt;
		Edge(int y, int f, Edge* next):y(y), f(f), next(next){}
	}*a[MAXN];

	inline void AddEdge(int x, int y, int c) {
		a[x] = new Edge(y, c, a[x]);
		a[y] = new Edge(x, 0, a[y]);
		a[x]->opt = a[y], a[y]->opt = a[x];
	}
	int n, m, vs, vt;
	#define In(x) ((x) << 1)
	#define Out(x) ((x) * 2 - 1)
	void Input(void) {
		scanf("%d %d", &n, &m);
		int x, y, c;
		scanf("%d %d", &x, &y);
		vs = In(x), vt = Out(y);
		for (int i = 1; i <= n; i++) {
			scanf("%d", &c);
			AddEdge(In(i), Out(i), c);
		}
		for (int i = 1; i <= m; i++) {
			scanf("%d %d", &x, &y);
			AddEdge(Out(x), In(y), inf);
			AddEdge(Out(y), In(x), inf);
		}
	}

	int level[MAXN];
	bool Bfs(void) {
		memset(level, -1, sizeof level); level[vs] = 0;
		std::queue<int> Q;
		Q.push(vs);
		while (Q.size()) {
			int now = Q.front(); Q.pop();
			for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && level[p->y] == -1) {
				level[p->y] = level[now] + 1;
				Q.push(p->y);
			}
		}
		return level[vt] != -1;
	}

	int Extend(int u, int sum) {
		if (u == vt) return sum;
		int r = 0, t;
		for (Edge *p = a[u]; p && r < sum; p = p->next) if (level[p->y] == level[u] + 1 && p->f > 0) {
			t = Extend(p->y, std::min(sum - r, p->f));
			p->f -= t, p->opt->f += t, r += t;
		}
		if (!r) level[u] = -1;
		return r;
	}
	int Dinic(void) {
		int t, r = 0;
		while (Bfs()) while (t = Extend(vs, inf)) r += t;
		return r;
	}
	void solve(void) {
		Input();
		printf("%d\n", Dinic());
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
