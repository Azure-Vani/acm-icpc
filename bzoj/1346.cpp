//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 500050;

	bool b[MAXN];int a[MAXN], n, k;
	void solve(void) {
		scanf("%d %d", &n, &k);
		for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i);
		int Ans = 0, Sum = 0; a[n + 1] = k;
		for (int i = 1; i <= n; i++) if (!b[i]) {
			if (Sum + a[i] < a[i + 1])
				Sum += a[i], Ans++;
		}
		printf("%d\n", Ans);
		if (!Ans) printf("%d\n", k - 1); else printf("%d\n", k - Sum);
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
