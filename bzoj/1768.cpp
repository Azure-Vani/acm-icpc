//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXM = 1505;
	const int MAXN = 15005;

	char a[MAXM]; int n, m;
	int f[MAXM], g[MAXM] = {-1};

	#define max(a, b) ((a) > (b) ? (a) : (b))
	void solve(void) {
		scanf("%d%d\n", &n, &m);
		int Ans = 0;
		for (int i = 1; i <= n; i++) {
			gets(a + 1); scanf("\n");
			for (int i = 1; i <= m; i++) {
				f[i] = ((a[i] == '1') ? f[i] + 1 : 0);
				g[i] = f[i];
			}
			std::sort(g + 1, g + 1 + m);
			for (int i = m; i >= 1; i--) if (g[i] != g[i - 1])
				Ans = max(Ans, g[i] * (m - i + 1));
		}
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
