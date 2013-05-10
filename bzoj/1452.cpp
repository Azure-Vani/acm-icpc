#include <cstdio>
const int MAXN = 303; const int MAXM = 103;
#define low(x) ((x)&(-(x)))
class BIT {public:
	int a[MAXN][MAXN], n, m;
	inline void Set(int _n, int _m){n = _n;m = _m;}
	inline void Add(int x, int y, int d) {for (int i = x; i <= n; i += low(i)) for (int j = y; j <= m; j += low(j)) a[i][j] += d;}
	inline int Ask(int x, int y) {int ret = 0; for (int i = x; i >= 1; i -= low(i)) for (int j = y; j >= 1; j -= low(j)) ret += a[i][j]; return ret;}
	inline int Cal(int x1, int y1, int x2, int y2) {return Ask(x2, y2) - Ask(x2, y1 - 1) - Ask(x1 - 1, y2) + Ask(x1 - 1, y1 - 1);}
};
BIT a[MAXM]; int c[MAXN][MAXN];
void solve(void) {
	int n, m, Q, flag, x, y, C, x1, y1, x2, y2; scanf("%d%d", &n, &m);
	for (int i = 1; i <= 100; i++) a[i].Set(n, m);
	for (int i = 1; i <= n; i++) for (int j = 1; j <= m; j++) scanf("%d", &c[i][j]), a[c[i][j]].Add(i, j, 1);
	scanf("%d", &Q);
	while (Q--) {scanf("%d", &flag);
		if (flag == 1) scanf("%d%d%d", &x, &y, &C), a[c[x][y]].Add(x, y, -1), a[c[x][y] = C].Add(x, y, 1); else
		scanf("%d%d%d%d%d", &x1, &x2, &y1, &y2, &C), printf("%d\n", a[C].Cal(x1, y1, x2, y2));
	}
}
int main(int argc, char** argv) {
	solve();
	return 0;
}
