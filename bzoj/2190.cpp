#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 40020;
	int f[MAXN], n;
	void solve(void) {
		scanf("%d", &n);n--;
		for (int i = n; i >= 1; i--) {
			f[i] = (n / i) * (n / i);
			for (int j = 2; i * j <= n; j++)
				f[i] -= f[i * j];
		}
		printf("%d\n", f[1] + 2);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
