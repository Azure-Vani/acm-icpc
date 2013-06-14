#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 4010;

int n, k, a[MAXN], b[MAXN], m;
vector<int> R[MAXN], tmp;

inline int Check(int t) {
	if (!t) return 0; tmp.clear();
	for (int i = 1; i <= m; i++) {
		for (int j = 0, p = 0; j < (int)R[i].size(); j++) {
			p += R[i][j];
			if (j % t == (t - 1)) {tmp.push_back(p), p = 0; break;}
		}
	}
	int ret = 0;
	if ((int)tmp.size() >= k) {
		sort(tmp.rbegin(), tmp.rend());
		for (int i = 0; i < k; i++) ret += tmp[i];
	}
	return ret;
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d%d", a + i, b + i), R[a[i]].push_back(b[i]), m = max(m, a[i]);
	for (int i = 1; i <= m; i++) sort(R[i].rbegin(), R[i].rend());
	int l = 1, r = n;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (Check(mid) > 0) l = mid + 1; else r = mid - 1;
	}
	printf("%d %d\n", r, Check(r));
	return 0;
}

