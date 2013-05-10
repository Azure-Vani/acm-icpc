//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 605;
	
	int s[MAXN][MAXN], n, g[MAXN][MAXN];
	int f[MAXN][MAXN], k, path[MAXN][MAXN];

	int Input(void) {
		scanf("%d%d", &n, &k);
		for (int i = 1; i < n; i++)
			for (int j = i + 1; j <= n; j++)
				scanf("%d", &s[i][j]), s[i][j] += s[i][j - 1];
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= i; j++)
				g[i][j] = g[i][j - 1] + s[j][n] - s[j][i];
	}

	void solve(void) {
		Input();
		for (int l = 1; l <= k; l++) {
			for (int i = 1; i <= n; i++) {
				int tmp = 0, k = 0;
				for (int j = 0; j < i; j++)
					if (tmp < f[l - 1][j] + (g[i][i] - g[i][j])) {
						tmp = f[l - 1][j] + (g[i][i] - g[i][j]);
						k = j;
					}
				f[l][i] = tmp;
				path[l][i] = k;
			}
		}
		int Ans[54] = {0}, t = 0, max = 0;
		for (int i = 1; i <= n; i++) if (f[k][i] > max) {
			max = f[k][i];
			t = i;
		}
		for (int i = k; i >= 1; i--) {
			Ans[i] = t;
			t = path[i][t];
		}
		for (int i = 1; i < k; i++) printf("%d ", Ans[i] == 0 ? i : Ans[i]); printf("%d\n", Ans[k] < k ? k : Ans[k]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	//	freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
