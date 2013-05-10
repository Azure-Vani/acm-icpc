//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 105;
	bool a[MAXN][MAXN], vis[MAXN];
	int r[MAXN];

	int n, m;

	bool Dfs(int u) {
		for (int i = 1; i <= n; i++) if (a[u][i] && !vis[i]) {
			vis[i] = true;
			if (!r[i] || Dfs(r[i])) {
				r[i] = u;
				return true;
			}
		}
		return false;
	}

	void solve(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			a[x][y] = true;
		}
		for (int k = 1; k <= n; k++)
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++)
					a[i][j] |= a[i][k] && a[k][j];
		int Ans = 0;
		for (int i = 1; i <= n; i++, memset(vis, 0, sizeof vis)) Ans += Dfs(i);
		printf("%d\n", n - Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
