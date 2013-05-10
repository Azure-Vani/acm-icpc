//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 1005;
	const int inf = 1000000000;

	int a[MAXN][MAXN]; int n, m; char ch[MAXN];
	void Input(void) {
		scanf("%d %d\n", &n, &m);
		for (int i = 1; i <= n; i++) {
			gets(ch + 1);
			for (int j = 1; j <= m; j++)
				a[i][j] = ch[j] - '0';
		}
	}

	int b[MAXN][MAXN];
	void Trans(int a[MAXN][MAXN], int n, int m) {
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++)
				b[m - j + 1][i] = a[i][j];
		memcpy(a, b, sizeof b);
	}

	int f[MAXN][MAXN], Ans[MAXN][MAXN];
	void Dp(void) {
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; i++) f[i][0] = inf;
		for (int j = 1; j <= m; j++) f[0][j] = inf;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				if (!a[i][j])
					f[i][j] = std::min(f[i - 1][j], f[i][j - 1]) + 1;
				Ans[i][j] = std::min(Ans[i][j], f[i][j]);
			}
	}

	void Work(void) {
		memset(Ans, 60, sizeof Ans);
		for (int i = 1; i <= 4; i++) {
			Dp();
			Trans(a, n, m);
			Trans(Ans, n, m);
			std::swap(n, m);
		}
		for (int i = 1; i <= n; printf("%d\n", Ans[i][m]), i++)
			for (int j = 1; j < m; j++)
				printf("%d ", Ans[i][j]);
	}

	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
