//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
#include <queue>
namespace Solve {
	const int MAXN = 605;
	const int inf = 0x6eeeeeee;

	int ScanInt(void) {
		int c, r;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y, c, f; Edge*next, *opt;
		Edge(int y, int f, int c, Edge* next):y(y), f(f), c(c), next(next){}
	}*a[MAXN];

	#define Ou(u) ((u) << 1)
	#define In(u) ((u) * 2 - 1)

	inline void AddEdge(int x, int y, int f, int z) {
		a[x] = new Edge(y, f, z, a[x]);
		a[y] = new Edge(x, 0, -z, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}
	int n, m, vs, vt;
	void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			AddEdge(Ou(x), In(y), 1, z);
		}
		for (int i = 1; i <= n; i++)
			AddEdge(In(i), Ou(i), 1, 0);
		vs = Ou(1), vt = In(n);
		n <<= 1;
	}

	int Cost = 0, dis[MAXN], Flow = 0;
	bool hash[MAXN], vis[MAXN];

	int Extend(int u, int sum) {
		if (u == vt) return sum;
		vis[u] = true;
		int r = 0, t;
		for (Edge* p = a[u]; p && r < sum; p = p->next)
			if (!vis[p->y] && p->f > 0 && dis[p->y] == dis[u] + p->c) {
				t = Extend(p->y, std::min(p->f, sum - r));
				r += t; p->f -= t, p->opt->f += t; Cost += t * p->c;
			}
		return r;
	}

	bool Spfa(void) {
		memset(dis, 101, sizeof (int) * (n + 1));
		memset(hash, 0, sizeof (bool) * (n + 1));
		dis[vs] = 0;
		std::queue<int> Q;
		Q.push(vs);
		hash[vs] = true;
		while (Q.size()) {
			int now = Q.front(); Q.pop();
			for (Edge* p = a[now]; p; p = p->next)
				if (p->f > 0 && dis[p->y] > dis[now] + p->c) {
					dis[p->y] = dis[now] + p->c;
					if (!hash[p->y]) {
						Q.push(p->y);
						hash[p->y] = true;
					}
				}
			hash[now] = false;
		}

		if (dis[vt] == dis[0]) return false;
		int t = 0;
		while (true) {
			memset(vis, 0, sizeof (bool) * (n + 1));
			t = Extend(vs, inf);
			if (!t) break;
			Flow += t;
		}
		return true;
	}
	void solve(void) {
		Input();
		while (Spfa());
		printf("%d %d\n", Flow, Cost);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
