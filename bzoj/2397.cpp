#include <cstdio>
#include <algorithm>
#include <cstring>
#define abs(x) ((x)<0?(-(x)):(x))
namespace Solve {
	typedef long long Int64;
	const int MAXN = 102;
	const Int64 inf = 10000000000000000ll;
	
	Int64 a[MAXN], d, n, c[MAXN];
	inline void Input(void) {
		scanf("%lld%lld", &n, &d);
		for (int i = 1; i <= n; i++) {
			scanf("%lld", a + i);
		}
		c[1] = a[1];
		for (int i = 2; i <= n; i++) c[i] = c[i - 1] - d;
	}

	inline Int64 Work(void) {
		while (c[n] != a[n]) {
			Int64 s = 0, maxs = -inf, mind = inf, delta = 0, pos = 1;
			for (int i = n; i >= 2; i--) {
				if (c[i] >= a[i]) s--;
				else {
					s++;
					mind = std::min(a[i] - c[i], mind);
				}
				if (s > maxs && c[i - 1] + d > c[i]) {
					delta = mind;
					pos = i;
					maxs = s;
				}
			}
			if (c[pos - 1] + d < c[pos] + delta) delta = c[pos - 1] + d - c[pos];
			for (int i = pos; i <= n; i++) c[i] += delta;
		}
		Int64 Ans = 0;
		for (int i = 2; i < n; i++) Ans += abs(c[i] - a[i]);
		return Ans;
	}

	inline void solve(void) {
		Input();
		if (abs(a[n] - a[1]) > (Int64) d * (n - 1)) {
			puts("impossible");
			return;
		}
		Int64 Ans = Work();
		printf("%lld\n", Ans);
	}
}
int main(void) {
	
	int t; scanf("%d", &t); while (t--)
	Solve::solve();
	return 0;
}
