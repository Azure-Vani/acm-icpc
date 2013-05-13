#include <cstdio>
#include <algorithm>

using namespace std;

pair<int, long long> a[100010];int n;long long gss[65];
int main(void) {
//	freopen("in", "r", stdin);
	int n; scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld%d", &a[i].second, &a[i].first);
	sort(a + 1, a + n + 1);
	int Ans = 0;
	for (int i = n; i >= 1; i--) {
		bool ok = false; int t = a[i].first;
		for (int j = 62; j >= 0; j--) if (a[i].second & (1ll << j)) {
			if (!gss[j]) {gss[j] = a[i].second; ok = true; break;} else a[i].second ^= gss[j];
		}
		if (ok) Ans += t;
	}
	printf("%d\n", Ans);
	return 0;
}

