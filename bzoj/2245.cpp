//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 505;
	const int inf = 1050000000;

	struct Edge {
		int y; int f, c; Edge *next, *opt;
		Edge(int y, int f, int c, Edge* next):y(y), f(f), c(c), next(next){}
	}*a[MAXN], *path[MAXN];

	inline void AddEdge(int x, int y, int f, int c) {
		a[x] = new Edge(y, f, c, a[x]);
		a[y] = new Edge(x, 0, -c, a[y]);
		a[x]->opt = a[y], a[y]->opt = a[x];
	}

	int n, m, vs, vt;

	void Input(void) {
		scanf("%d%d", &n, &m); vs = n + m + 1, vt = vs + 1;
		for (int i = 1; i <= m; i++) {
			int tmp; scanf("%d", &tmp);
			AddEdge(i + n, vt, tmp, 0);
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				int tmp; scanf("%d", &tmp);
				if (tmp) {
					AddEdge(i, j + n, inf, 0);
				}
			}
		int w[MAXN] = {0}, c[MAXN] = {0};
		for (int i = 1; i <= n; i++) {
			int s; scanf("%d", &s);
			for (int j = 1; j <= s; j++) scanf("%d", w + j); w[s + 1] = inf;
			for (int j = 1; j <= s + 1; j++) scanf("%d", c + j);
			for (int j = 1; j <= s + 1; j++) 
				AddEdge(vs, i, w[j] - w[j - 1], c[j]);
		}
	}

	long long Ans = 0; int dis[MAXN], d[MAXN];

	inline bool Spfa(void) {
		bool hash[MAXN] = {0};
		memset(dis, 63, sizeof dis);
		int head = 1, tail = 1, sum = 1;
		hash[d[1] = vs] = true; dis[vs] = 0;
		while (sum) {
			int now = d[head++];sum--; if (head >= MAXN) head = 1;
			for (Edge *p = a[now]; p; p = p->next) 
				if (p->f > 0 && dis[p->y] > dis[now] + p->c) {
					dis[p->y] = dis[now] + p->c;
					path[p->y] = p->opt;
					if (!hash[p->y]) {
						hash[d[++tail] = p->y] = true, sum++;
						if (tail >= MAXN) tail = 1;
					}
				}
			hash[now] = false;
		}
		if (dis[vt] == dis[0]) return false;
		int minflow = inf;
		for (int i = vt; i != vs; i = path[i]->y) minflow = std::min(minflow, path[i]->opt->f);
		long long tmp = 0;
		for (int i = vt; i != vs; i = path[i]->y)
			path[i]->f += minflow, path[i]->opt->f -= minflow, tmp -= path[i]->c;
		Ans += (long long) tmp * minflow;
		return true;
	}

	inline void solve(void) {
		Input();
		while (Spfa()) {}
		printf("%lld\n", Ans);
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
