#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>

using namespace std;

namespace Solve {
	const int MAXN = 1000010;
	
	inline int ScanInt(void) {
		int r = 0, c;
		while (!isdigit(c = getchar()));
		r = c - '0';
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return r;
	}

	int k, t; pair<int, int> a[MAXN];
	int prev[MAXN], next[MAXN], nnext[MAXN], pprev[MAXN], hash[MAXN];

	void O(int h, int i, int k) {
		printf("%d %d %d %d %d %d\n", a[h].second, a[h].first, a[i].second, a[i].first, a[k].second, a[k].first);
	}

	inline void solve(void) {
		k = ScanInt(); int N = 0;
		for (int i = 1; i <= k; i++) {
			t = ScanInt();
			for (int j = 1; j <= t; j++) a[++N].second = i, a[N].first = ScanInt();
		}
		sort(a + 1, a + N + 1);
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= k; j++) if (j != a[i].second)
				prev[i] = max(prev[i], hash[j]);
			hash[a[i].second] = i;
			if (a[prev[prev[i]]].second == a[i].second) pprev[i] = pprev[prev[i]]; else pprev[i] = prev[prev[i]];
		}
		memset(hash, 60, sizeof hash);
		for (int i = N; i >= 1; i--) {
			next[i] = N + 1; nnext[i] = N + 1;
			for (int j = 1; j <= k; j++) if (j != a[i].second)
				next[i] = min(next[i], hash[j]);
			hash[a[i].second] = i;
			if (a[next[next[i]]].second == a[i].second) nnext[i] = nnext[next[i]]; else nnext[i] = next[next[i]];
		}
		bool ok = false;
		for (int i = 1; i <= N; i++) if (next[i] <= N && prev[i]) {
			int lll = pprev[i], l = prev[i], r = next[i], rrr = nnext[i];
			if (a[l].second != a[r].second && a[l].first + a[i].first > a[r].first) {
				O(l, i, r);
				ok = true; break;
			} else
			if (lll && a[lll].first + a[i].first > a[r].first) {
				O(lll, i, r);
				ok = true; break;
			} else
			if (rrr <= N && a[l].first + a[i].first > a[rrr].first) {
				O(l, i, rrr);
				ok = true; break;
			}
		}
		if (!ok) puts("NIE");
	}
}

int main(void) {
	//freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}
