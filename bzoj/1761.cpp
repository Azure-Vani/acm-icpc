#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
namespace Solve {
	const int MAXN = 301;
	const int inf = 2000000;

	int n, m, a[MAXN];
	void Input(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		a[++n] = 0;
	}
	
	int l[2][MAXN][MAXN], r[2][MAXN][MAXN]; bool vis[MAXN][MAXN][MAXN];
	void Dfs(int k, int l, int r) {
		if (k <= 0 || l < 1 || r > n) return;
		if (n - (r - l + 1) < k) return;
		if (vis[k][l][r]) return; vis[k][l][r] = true;
		bool now = k & 1, bef = !now;
		int &L = Solve::l[now][l][r], &R = Solve::r[now][l][r];
		Dfs(k - 1, l - 1, r);
		Dfs(k - 1, l, r + 1);
		L = std::min(Solve::l[bef][l - 1][r] + k * (a[l] - a[l - 1]), Solve::r[bef][l][r + 1] + k * (a[r + 1] - a[l]));
		R = std::min(Solve::l[bef][l - 1][r] + k * (a[r] - a[l - 1]), Solve::r[bef][l][r + 1] + k * (a[r + 1] - a[r]));
	}
	void solve(void) {
		Input();
		std::sort(a + 1, a + n + 1);a[0] = -inf, a[n + 1] = inf;
		int where = 0, ret = 0;
		for (int i = 1; i <= n; i++) if (!a[i]) where = i;
		for (int i = 0; i < n; i++) {
			Dfs(i, where, where);
			ret = std::max(ret, i * m - l[i & 1][where][where]);
		}
		printf("%d\n", ret);
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
