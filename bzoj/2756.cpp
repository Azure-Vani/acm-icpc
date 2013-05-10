//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	typedef long long Int64;

	const Int64 MAXN = 1910;
	const Int64 MAXM = 80;
	const Int64 inf = 100000000000000000ll;

	inline Int64 ScanInt(void) {
		Int64 r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	Int64 R, C, e[MAXM][MAXM], MaxH, n;

	inline void Input(void) {
		R = ScanInt(), C = ScanInt(), MaxH = 0;
		n = R * C;
		for (Int64 i = 1; i <= R; i++) 
			for (Int64 j = 1; j <= C; j++) 
				e[i][j] = ScanInt(), MaxH = max(MaxH, e[i][j]);
	}

	inline Int64 ID(Int64 x, Int64 y) {
		return (x - 1) * C + y;
	}

	struct Edge {
		Int64 y;Int64 z; Edge *next, *opt;
		Edge(Int64 y, Int64 z, Edge *next):y(y), z(z), next(next){}
	}*a[MAXN];
	inline void AddEdge(Int64 x, Int64 y, Int64 c) {
		a[x] = new Edge(y, c, a[x]);
		a[y] = new Edge(x, 0, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}

	Int64 s, t;
	Int64 Vol = 0, S1, S2;

	inline void Makeup(void) {
		memset(a, 0, sizeof a);
		Vol = 0; s = n + 1, t = s + 1; S1 = 0, S2 = 0;
		for (Int64 i = 1; i <= R; i++) 
			for (Int64 j = 1; j <= C; j++) {
				Vol += e[i][j];
				if ((i&1) == (j&1)) {
					S1 += e[i][j];
					if (j != C) AddEdge(ID(i, j), ID(i, j + 1), inf);
					if (i != R) AddEdge(ID(i, j), ID(i + 1, j), inf);
					if (i != 1) AddEdge(ID(i, j), ID(i - 1, j), inf);
					if (j != 1) AddEdge(ID(i, j), ID(i, j - 1), inf);
					AddEdge(s, ID(i, j), 0);
				} else
					AddEdge(ID(i, j), t, 0), S2 += e[i][j];
			}
	}

	Int64 level[MAXN], d[MAXN];
	inline bool Bfs(void) {
		memset(level, -1, sizeof level);
		level[s] = 0;
		Int64 head = 1, tail = 1; d[1] = s;
		while (head <= tail) {
			Int64 now = d[head++];
			for (Edge *p = a[now]; p; p = p->next)
				if (level[p->y] == -1 && p->z > 0)
					level[d[++tail] = p->y] = level[now] + 1;
		}
		return level[t] != -1;
	}

	inline Int64 Extend(Int64 u, Int64 sum) {
		if (u == t) return sum;
		Int64 r = 0, t;
		for (Edge *p = a[u]; p && r < sum; p = p->next) if (p->z> 0 && level[p->y] == level[u] + 1) {
			t = min(p->z, sum - r);
			t = Extend(p->y, t);
			r += t, p->z -= t, p->opt->z += t;
		}
		if (!r) level[u] = -1;
		return r;
	}

	inline Int64 Dinic(void) {
		Int64 r = 0, t;
		while (Bfs()) while ((t = Extend(s, inf))) r += t;
		return r;
	}

	inline void Clear(Int64 H) {
		for (Int64 i = 1; i <= R; i++) 
			for (Int64 j = 1; j <= C; j++) {
				for (Edge *p = a[ID(i, j)]; p; p = p->next) {
					if (p->y == t)
						p->z = H - e[i][j], p->opt->z = 0;
					if (p->y == s)
						p->z = 0, p->opt->z = H - e[i][j];
					if ((i&1) == (j&1) && p->y <= n)
						p->z = inf, p->opt->z = 0;
				}
			}
	}

	inline void solve(void) {
		Int64 T; for (T = ScanInt(); T; T--) {
			Input();
			Makeup();
			if (n&1) {
				Int64 H = S1 - S2;
				if (H < MaxH) puts("-1"); else {
					Clear(H);
					Int64 tmp = Dinic();
					if (Vol + tmp * 2 == H * n) {
						printf("%lld\n", tmp);
					} else puts("-1");
				}
			} else {
				Int64 Limit = 100000000000ll;
				Int64 l = MaxH, r = Limit;
				while (l <= r) {
					Int64 mid = (l + r) >> 1;
					Clear(mid);
					Int64 tmp = Dinic();
					if (Vol + tmp * 2ll == mid * n) {
						r = mid - 1;
					} else {
						l = mid + 1;
					}
				}
				if (l > Limit) puts("-1"); else printf("%lld\n", (l * n - Vol) >> 1);
			}
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}