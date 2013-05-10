//#define Debug
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <iostream>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 305;
	const int MAXV = (MAXN << 1) + 10;
	int inf = 500000000;
	Int64 inf64 = 1000000000000000ll;

	int n, m, k, dist[MAXN][MAXN][MAXN];
	void Input(void) {
		scanf("%d %d %d", &n, &m, &k);
		for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) dist[0][i][j] = (i == j ? 0 : inf);

		for (int i = 1; i <= m; i++) {
			int x, y, z;
			scanf("%d %d %d", &x, &y, &z);
			z = std::min(dist[0][x][y], z);
			dist[0][x][y] = dist[0][y][x] = z;
		}
	}

	void Floyd(void) {
		for (int k = 0; k < n; k++)
			for (int i = 0; i <= n; i++)
				for (int j = 0; j <= n; j++)
					dist[k + 1][i][j] = std::min(dist[k][i][j], dist[k][i][k] + dist[k][k][j]);
	}
	
	struct Edge {
		int y, f, c; Edge *next, *opt;
		Edge(int y, int f, int c, Edge *next):y(y), f(f), c(c), next(next){}
	}*a[MAXN << 1];
	void AddEdge(int x, int y, int f, int c) {
		a[x] = new Edge(y, f, c, a[x]);
		a[y] = new Edge(x, 0, -c, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}

	int vs, vt, cnt = 0, In[MAXN], Out[MAXN];
	void MakeGraph(void) {
		for (int i = 0; i <= n; i++)
			In[i] = ++cnt, Out[i] = ++cnt;
		vs = ++cnt, vt = ++cnt;

		for (int i = 0; i <= n; i++)
			AddEdge(In[i], Out[i], 1, -inf);
		AddEdge(vs, Out[0], k, 0);
		for (int i = 0; i <= n; i++) {
			for (int j = i + 1; j <= n; j++) {
				int cost = dist[j][i][j];
				if (cost >= inf) continue;
				AddEdge(Out[i], In[j], inf, cost);
			}
			AddEdge(Out[i], vt, inf, 0);
		}
	}

	
	Int64 Ans = 0, dis[MAXV];
	Edge* path[MAXV];

	bool spfa(void) {
		std::queue<int> Q;
		bool hash[MAXV] = {0};
		std::fill(dis, dis + cnt + 1, inf64);
		dis[vs] = 0;
		Q.push(vs); hash[vs] = true;
		path[vs] = NULL;

		while (Q.size()) {
			int now = Q.front(); Q.pop();
			for (Edge *p = a[now]; p; p = p->next) if (p->f > 0 && dis[p->y] > dis[now] + p->c) {
				path[p->y] = p->opt;
				dis[p->y] = dis[now] + p->c;
				if (!hash[p->y])
					hash[p->y] = true, Q.push(p->y);
			}
			hash[now] = false;
		}
		if (dis[vt] >= inf64) return false;

		int min = inf;
		for (Edge* p = path[vt]; p; p = path[p->y]) min = std::min(min, p->opt->f);
		for (Edge* p = path[vt]; p; p = path[p->y])
			p->f += min, p->opt->f -= min, Ans += (Int64) (p->opt->c * min);
		return true;
	}

	Int64 MinCost(void) {
		while (spfa()){}
		return Ans += (Int64) (1LL * inf) * (Int64) n;
	}

	void solve(void) {
		Input();
		Floyd();
		MakeGraph();
		printf("%lld\n", MinCost());
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
