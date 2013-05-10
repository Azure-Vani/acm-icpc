#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define REP(i,l,r) for(int i = l; i <= r; i++)

int n, a[101][101];

int main(void) {
	freopen("in", "r", stdin);
	while (scanf("%d", &n) && n) {
		memset(a, 42, sizeof a);
		REP(i, 1, n) {
			int t, x, y; scanf("%d", &t);
			REP(j, 1, t) scanf("%d%d", &x, &y), a[i][x] = y;
			a[i][i] = 0;
		}
		REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) a[i][j] = min(a[i][j], a[i][k] + a[k][j]);
		int w = 0, best = a[0][0]; bool ok = false;
		REP(i, 1, n) {
			int cnt = 0, m = 0;
			REP(j, 1, n) if (a[i][j] != a[0][0]) ++cnt, m = max(m, a[i][j]);
			if (cnt != n) continue;ok = true;
			if (m < best) best = m, w = i;
		}
		if (ok) printf("%d %d\n", w, best); else puts("disjoint");
	}
	return 0;
}

