//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 40;
	const int inf = 0x6eeeeeee;
	
	bool c[MAXN][MAXN], *a[MAXN];
	int n, m;
	
	void Input(void) {
		scanf("%d%d", &n, &m);
		for (int __ = 1; __ <= m; __++) {
			int x, y;
			scanf("%d%d", &x, &y);
			c[x][y] = c[y][x] = true;
		}
	}
	
	void Work(void) {
		for (int i = 1; i <= n; i++) a[i] = c[i], c[i][n + 1] = true, c[i][i] = true;
		
		for (int k = 1; k < n; k++) {
			bool ex = false;
			for (int i = k; i <= n; i++)
				if (a[i][k]) {
					std::swap(a[i], a[k]);
					ex = true;
					break;
				}
			if (!ex) continue;
			for (int i = k + 1; i <= n; i++)
				if (a[i][k])
					for (int j = k; j <= n + 1; j++)
						a[i][j] ^= a[k][j];
		}
	}
	
	int A = inf;
	bool res[MAXN];
	
	void Dfs(int k, int Cal) {
		if (Cal >= A) return;
		if (k == 0) {
			A = std::min(A, Cal);
			return;
		}
		bool temp = a[k][n + 1];
		for (int i = k + 1; i <= n; i++)
			if (a[k][i])
				temp ^= res[i];
		
		if (a[k][k]) {
			res[k] = temp;
			Dfs(k - 1, Cal + temp);
		}else {
			res[k] = 1;
			Dfs(k - 1, Cal + 1);
			res[k] = 0;
			Dfs(k - 1, Cal);
		}
		res[k] = 0;
	}
	
	void solve(void) {
		Input();
		Work();
		Dfs(n, 0);
		printf("%d\n", A);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
