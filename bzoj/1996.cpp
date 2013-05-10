#include <cstdio>
namespace Solve {
	const int Mod = 19650827;
	const int MAXN = 1003;

	int L[MAXN][MAXN], R[MAXN][MAXN], n, a[MAXN];

	inline void Add(int &a, const int &b) {
		a += b; a %= Mod;
	}

	inline void solve(void) {
		scanf("%d", &n); if (n == 1) {puts("1"); return;}
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
		for (int i = n; i >= 1; i--)
			for (int j = i; j <= n; j++) if (i == j) L[i][j] = R[i][j] = 1; else {
				if (a[i] < a[i + 1]) Add(L[i][j], L[i + 1][j]);
				if (i + 1 != j && a[i] < a[j]) Add(L[i][j], R[i + 1][j]);
				if (a[j] > a[i]) Add(R[i][j], L[i][j - 1]);
				if (i + 1 != j && a[j] > a[j - 1]) Add(R[i][j], R[i][j - 1]);
			}
		Add(L[1][n], R[1][n]);
		printf("%d\n", L[1][n]);
	}
}
int main(void) {
	//freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}
