#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 1000050;
	int a[MAXN], n;
	void solve(void) {
		scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d", a + i);
		std::sort(a + 1, a + n + 1);
		long long now = 0, bef = 0;
		for (int i = 1; i <= n; i++) now = std::max(bef, a[i] - bef), bef = now;
		printf("%lld\n", now);
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
