#include <cstdio>
#include <cctype>
#include <algorithm>
#define inf 1000000000
using namespace std;
namespace Solve {
	const int MAXN = 610;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c));
		r = c - '0';
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y, z; Edge *next;
		Edge(int y, int z, Edge *next):y(y), z(z), next(next){}
	}*a[MAXN];

	int n, m1, m2;
	inline void Input(void) {
		n = ScanInt(), m1 = ScanInt(), m2 = ScanInt();
		for (int i = 1; i <= m1; i++) {
			int x = ScanInt(), y = ScanInt();
			a[x] = new Edge(y, 1, a[x]);
			a[y] = new Edge(x, -1, a[y]);
		}
		for (int i = 1; i <= m2; i++) {
			int x = ScanInt(), y = ScanInt();
			a[y] = new Edge(x, 0, a[y]);
		}
	}

	int tim[MAXN], low[MAXN], time, sum, belong[MAXN], stack[MAXN], top; bool instack[MAXN];

	inline void Dfs(int u) {
		tim[u] = low[u] = ++time;
		stack[++top] = u; instack[u] = true;
		for (Edge *p = a[u]; p; p = p->next) {
			if (!tim[p->y]) {
				Dfs(p->y);
				low[u] = min(low[u], low[p->y]);
			} else if (instack[p->y]) low[u] = min(low[u], tim[p->y]);
		}
		if (low[u] == tim[u]) {
			sum++; int j;
			do {
				j = stack[top--];
				instack[j] = false;
				belong[j] = sum;
			} while(j != u);
		}
	}

	int dis[MAXN][MAXN]; bool vis[MAXN];
	inline void Floyd(void) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) if (i != j) dis[i][j] = inf;
		for (int i = 1; i <= n; i++)
			for (Edge *p = a[i]; p; p = p->next) 
				if (belong[i] == belong[p->y]) dis[i][p->y] = min(dis[i][p->y], p->z);
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++) if (dis[i][k] < inf)
				for (int j = 1; j <= n; j++) if (dis[k][j] < inf)
					dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
		for (int i = 1; i <= n; i++) if (dis[i][i] < 0) {puts("NIE"); return;}
		int Ans = 0;
		for (int i = 1; i <= n; i++) if (!vis[belong[i]]) {
			vis[belong[i]] = true;
			int M = -inf;
			for (int j = 1; j <= n; j++) if (belong[j] == belong[i])
				for (int k = 1; k <= n; k++) if (belong[k] == belong[i])
					M = max(M, dis[j][k]);
			Ans += M + 1;
		}
		printf("%d\n", Ans);
	}

	inline void solve(void) {
		Input();
		for (int i = 1; i <= n; i++) if (!tim[i]) Dfs(i);
		Floyd();
	}
}
int main(void) {
//	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}
