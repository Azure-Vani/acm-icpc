//#define Debug
#include <cstdio>
#include <cstring>
namespace Solve {
	const long MAXN = 10050;
	const long inf = 0x6eeeeeee;
	long fim[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
	long n, m, vs, vt, map[102][102] = {0};
	inline long G(long x, long y) {return (x - 1) * m + y;}
	inline void Input(void) {
		scanf("%ld %ld", &n, &m);
		memset(map, -1, sizeof map);
		for (long i = 1; i <= n; i++)
			for (long j = 1; j <= m; j++) {
				long t; scanf("%ld", &t); map[i][j] = t;
			}
		
		vs = m * n + 1, vt = vs + 1;
	}

	struct Edge {
		long y, z; Edge* next, *opt;
		Edge(long y, long z, Edge* next):y(y), z(z), next(next){}
	}*a[MAXN];
	inline void Add(long x, long y, long c) {
		a[x] = new Edge(y, c, a[x]); a[y] = new Edge(x, 0, a[y]);
		a[x]->opt = a[y]; a[y]->opt = a[x];
	}
	long level[MAXN] = {0};
	bool Bfs(void) {
		memset(level, -1, sizeof level);
		long d[MAXN] = {0}, head = 1, tail = 1;
		level[vs] = 0, d[1] = vs;
		while (head <= tail) {
			long now = d[head++];
			for (Edge* p = a[now]; p ; p = p->next)
				if (p->z > 0 && level[p->y] == -1)
					level[d[++tail] = p->y] = level[now] + 1;
		}
		return level[vt] != -1;
	}
	long Extend(long u, long sum) {
		if (u == vt) return sum;
		long t, r = 0;
		for (Edge* p = a[u]; p && r < sum;p = p->next)
			if (p->z > 0 && level[p->y] == level[u] + 1) {
				t = Extend(p->y, p->z < sum - r ? p->z : sum - r);
				r += t, p->z -= t, p->opt->z += t;
			}
		if (!r) level[u] = -1;
		return r;
	}
	long Dinic(void) {
		long t, r = 0;
		while (Bfs()) 
			while (t = Extend(vs, inf)) r += t;
		return r;
	}
	void Work(void) {
		Input();
		for (long i = 1; i <= n; i++)
			for (long j = 1; j <= m; j++) {
				if (map[i][j] == 1)
					Add(vs, G(i, j), inf);
				else if (map[i][j] == 2)
					Add(G(i ,j), vt, inf);
				for (long k = 0; k < 4; k++) {
					long x = i + fim[k][0], y = j + fim[k][1];
					if (x > 0 && x <= n && y > 0 && y <= m) {
						if (map[x][y] == map[i][j] && map[i][j])
							Add(G(i, j), G(x, y), 0);
						else
							Add(G(i ,j), G(x, y), 1);
					}
				}
			}
		printf("%ld\n", Dinic());
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}
