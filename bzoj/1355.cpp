#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 1000005;
	int a[MAXN], n, p[MAXN], f[MAXN];
	void solve(void) {
		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++) a[i] = getchar() - 'a' + 1;
		int ret = MAXN;
		for (int i = 2; i <= n; i++) {
			int tmp = p[i - 1];
			while (tmp && a[tmp + 1] != a[i]) tmp = p[tmp];
			if (a[tmp + 1] == a[i]) tmp++;
			p[i] = tmp;
		}
		for (int i = n; i >= n - p[n]; i--) if ((n - i) < i - p[i]) ret = std::min(ret, i - p[i]);
		printf("%d\n", ret);
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
