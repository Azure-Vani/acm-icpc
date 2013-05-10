//#define Debug
#include <cassert>
#include <cstdarg>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cctype>
#define max(a,b) ((a)>(b)?(a):(b))
namespace Solve {
	const int MAXN = 250050;
	const int inf = 1050000000;
	
	struct Edge {
		int y, c; Edge *next, *opt; bool flag;
		Edge(int y, int c, Edge *next):y(y), c(c), next(next){flag = true;}
	}*a[MAXN];

	inline int ScanInt(void) {
		int c, r = 0, d;
		while (c = getchar(), !isdigit(c) && c != '-'){}
		if (c != '-') r = c - '0';
		while (d = getchar(),  isdigit(d)) r = r * 10 + d - '0';
		return c == '-' ? -r : r;
	}

	int n, m;
	inline void Input(void) {
		memset(a, NULL, sizeof a);
		n = ScanInt(), m = ScanInt();
		assert(m == n - 1);
		for (register int i = 1, x, y, z; i < n; i++) {
			x = ScanInt(), y = ScanInt(), z = ScanInt();
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
			a[x]->opt = a[y];
			a[y]->opt = a[x];
		}
	}

	int f[MAXN][2][3][6];
	bool Now = 0, next = 1, s[MAXN];

	void Dfs(int u) {
		for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			Dfs(p->y);
		}
		register int i, j, k;
		for (i = 0; i <= 2; i++) for (j = 0; j <= 5; j++) f[u][next][i][j] = -inf;
		f[u][Now][0][0] = f[u][next][0][0] = 0;
		for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
			register int t = p->y, c = p->c;
			Now ^= 1, next^= 1;
			for (i = 0; i <= 2; i++) for (j = 0; j <= 5; j++) f[u][next][i][j] = -inf;
			for (i = 0; i <= 2; i++)
				for (j = 0; j + i <= 2; j++) {
					register int *l = f[u][next][i + j], *h = f[u][Now][i], *g = f[t][s[t]][j];
					for (k = 0; k <= 5; k++) {
						l[k] = max(l[k], h[k] + g[0]);
						l[k] = max(max(max(l[k], h[k] + g[3]), h[k] + g[4]), h[k] + g[5]);
					}
					l[1] = max(l[1], h[0] + max(g[1], g[0]) + c);
					l[2] = max(l[2], h[1] + max(g[1], g[0]) + c);
					l[3] = max(l[3], h[0] + g[3] + c);
					l[5] = max(max(l[5], h[3] + max(g[1], g[0]) + c), h[1] + g[3] + c);
					if (i + j + 1 <= 2) {
						f[u][next][i + j + 1][3] = max(f[u][next][i + j + 1][3], h[0] + g[2] + c);
						f[u][next][i + j + 1][4] = max(f[u][next][i + j + 1][4], h[2] + max(g[1], g[0]) + c);
						f[u][next][i + j + 1][5] = max(f[u][next][i + j + 1][5], h[1] + g[2] + c);
					}
				}
		}
		s[u] = next;
	}

	inline void solve(void) {
		Input();
		Dfs(1);
		int Ans = max(max(f[1][s[1]][2][0], f[1][s[1]][2][3]), max(f[1][s[1]][2][4], f[1][s[1]][2][5]));
		if (Ans < 0) puts("POOR BB"); else printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	int _; scanf("%d", &_);
	while (_--)
		Solve::solve();
	return 0;
}
