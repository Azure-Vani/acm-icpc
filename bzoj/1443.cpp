//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 10010;
	const int MAXC = 105;

	int c[MAXC][MAXC], cnt = 0;
	int n, m; bool type[MAXN];

	void Input(void) {
		scanf("%d%d\n", &n, &m);
		for (int i = 1; i <= n; i++, scanf("\n"))
			for (int j = 1; j <= m; j++)
				if (getchar() != '#')
					c[i][j] = ++cnt, type[cnt] = (i&1)^(j&1);
	}

	struct Edge {
		int y; Edge *next, *opt;int c;
		Edge(int y, Edge *next, int c):y(y), next(next), c(c){}
	}*a[MAXN];

	inline void Add(int x, int y, bool f = false) {
		if (!f && !type[x]) std::swap(x, y);
		a[x] = new Edge(y, a[x], 1);
		a[y] = new Edge(x, a[y], 0);
		a[x]->opt = a[y]; a[y]->opt = a[x];
	}

	int vs, vt;
	inline void MakeGraph(void) {
		vs = cnt + 1, vt = vs + 1;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) if (c[i][j]) {
				int y = c[i][j];
				if (i - 1 > 0 && c[i - 1][j]) {
					int x = c[i - 1][j];
					Add(x, y);
				}
				if (j - 1 > 0 && c[i][j - 1]) {
					int x = c[i][j - 1];
					Add(x, y);
				}
			}
		for (int i = 1; i <= cnt; i++) if (type[i])
			Add(vs, i, true);
		else
			Add(i, vt, true);
	}

	int  vis[MAXN], cur = 1;

	inline int Extend(int u, int sum) {
		if (u == vt) return sum;
		vis[u] = cur; int t;
		for (Edge *p = a[u]; p; p = p->next) if (p->c > 0 && vis[p->y] != cur) {
			t = Extend(p->y, std::min(sum, p->c));
			if (t) return p->c -= t, p->opt->c += t, t;
		}
		return 0;
	}

	bool hash[MAXN], now, win = false;

	void Dfs(int u) {
		vis[u] = cur;
		if (type[u] == now)
			hash[u] = true, win = true;
		for (Edge *p = a[u]; p; p = p->next) if (vis[p->y] != cur && p->c == now)
			Dfs(p->y);
	}

	void solve(void) {
		Input();
		MakeGraph();
		int tmp = 0, t;
		while (t = Extend(vs, 1000000000)) cur++, tmp += t;
		now = 1; cur++;
		Dfs(vs);
		now = 0; cur++;
		Dfs(vt);
		if (win) {
			puts("WIN");
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= m; j++) if (hash[c[i][j]])
					printf("%d %d\n", i, j);
		}else puts("LOSE");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
