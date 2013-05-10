#include <cstdio>
#include <algorithm>
using namespace std;
long long n, s1, v1, s2, v2, d = 35000;
int main(void) {
	int kase = 0; scanf("%d", &kase);
	for (int i = 1; i <= kase; i++) {
		scanf("%lld%lld%lld%lld%lld", &n, &s1, &v1, &s2, &v2);
		long long Ans = 0;
		if (s1 < s2) swap(s1, s2), swap(v1, v2);
		if (s1 >= d) {
			for (long long i = 0; s1 * i <= n; i++) Ans = max(Ans, i * v1 + (n - i * s1) / s2 * v2);
		} else {
			if (v1 * s2 < v2 * s1) swap(s1, s2), swap(v1, v2);
			for (long long i = 0; i < s1 && i * s2 <= n; i++) Ans = max(Ans, i * v2 + (n - i * s2) / s1 * v1);
		}
		printf("Case #%d: %lld\n", i, Ans);
	}
	return 0;
}