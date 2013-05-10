//#define Debug
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 600;
	const int inf = 1000000000;

	struct Edge {
		int y, z; Edge *next, *opt;
		Edge(int y, int z, Edge* next):y(y), z(z), next(next){}
	}*a[MAXN];
	void AddEdge(int x, int y, int c) {
		a[x] = new Edge(y, c, a[x]);
		a[y] = new Edge(x, 0, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}

	struct pair{int x, y;}c[MAXN];

	int L, W, n;
	void Input(void) {
		scanf("%d%d%d", &L, &W, &n);
		for (int i = 1; i <= n; i++) 
			scanf("%d%d", &c[i].x, &c[i].y);
	}
	
	#define In(x) (((x) << 1) - 1)
	#define Out(x) ((x) << 1)
	#define dis(i, j) ((c[i].x - c[j].x) * (c[i].x - c[j].x) + (c[i].y - c[j].y) * (c[i].y - c[j].y))

	int vs, vt;
	void MakeGraph(void) {
		vs = Out(n) + 1, vt = vs + 1;
		for (int i = 1; i <= n; i++) {
			if (c[i].y <= 100)
				AddEdge(vs, In(i), inf), AddEdge(Out(i), vs, inf);
			if (W - c[i].y <= 100)
				AddEdge(Out(i), vt, inf), AddEdge(vt, In(i), inf);
			AddEdge(In(i), Out(i), 1);
		}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) if (i != j && dis(i, j) <= 40000)
				AddEdge(Out(i), In(j), inf);
	}

	int level[MAXN];
	bool Bfs(void) {
		std::queue<int> Q;
		memset(level, -1, sizeof level);
		level[vs] = 0; Q.push(vs);
		while (Q.size()) {
			int now = Q.front(); Q.pop();
			for (Edge *p = a[now]; p; p = p->next) if (p->z > 0 && level[p->y] == -1) {
				level[p->y] = level[now] + 1;
				Q.push(p->y);
			}
		}
		return level[vt] != -1;
	}

	int extend(int u, int sum) {
		if (u == vt) return sum;
		int r = 0, t;
		for (Edge *p = a[u]; p && r < sum; p = p->next) if (p->z > 0 && level[p->y] == level[u] + 1) {
			t = extend(p->y, std::min(sum - r, p->z));
			p->z -= t, p->opt->z += t, r += t;
		}
		if (!r) level[u] = -1;
		return r;
	}

	int Dinic(void) {
		int r = 0, t;
		while (Bfs()) while (t = extend(vs, inf)) r += t;
		return r;
	}
	void solve(void) {
		Input();
		MakeGraph();
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
