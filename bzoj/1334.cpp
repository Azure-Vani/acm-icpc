#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 305;
	const int MAXM = 100050;
	int a[MAXN], n, S;
	bool f[MAXM];
	void solve(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i), S += a[i]; S >>= 1;
		std::sort(a + 1, a + n + 1);
		int m = 0, Ans = 0; f[0]= true;
		for (int i = n; i >= 1; i--) {
			m += a[i];
			for (int j = m; j >= 0; j--) {
				if (j >= a[i]) f[j] |= f[j - a[i]];
				if (f[j] && j > S && j - S <= a[i])
					Ans = std::max(Ans, j);
			}
		}
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
