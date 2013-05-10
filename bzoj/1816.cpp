#include <cstdio>
#include <algorithm>
long n, m, a[152];
typedef long long ll;
inline bool Check(int u) {
	ll S = 0;
	for (int i = 0; i <= n; i++) if (a[i] < u) S += u - a[i];
	return S <= u;
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	scanf("%d%d", &n, a);
	int l = 0, r = 2147483647;
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (Check(mid))
			l = mid + 1;
		else
			r = mid - 1;
	}
	printf("%d\n", r);
	return 0;
}
