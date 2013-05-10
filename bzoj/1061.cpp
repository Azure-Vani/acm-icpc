#include <cstdio>
#define rep(i,l,n) for(int i = l; i <= n; i++)
const int MAXR = 10010, MAXC = 1010, inf = (~0U)>>2;
int n, m, a[MAXR][MAXC], next[MAXC], s, t, c;
inline void orz(int l, int e) {
	a[l][e] = -1;t = MAXC - 1;
	rep(i,0,m) if (a[l][i]) next[t] = i, t = i; next[t] = -1;
	rep(i,0,n) if (i != l && (t = a[i][e])) {
		a[i][e] = 0;
		for (int j = next[MAXC - 1];j != -1; j = next[j]) a[i][j] += a[l][j] * t;
	}
}
int solve(void) {for(;;) {
	int min = inf, l = 0, e = 0;
	rep(i,1,m) if (a[0][i] > 0) {e = i; break;}
	if (!e) return a[0][0];
	rep(i,1,n) if (a[i][e] < 0 && a[i][0] < min) min = a[i][0], l = i;
	orz(l,e);}
}
int main() {
	scanf("%d%d", &m, &n);
	rep(i,1,m) scanf("%d", &a[0][i]);
	rep(i,1,n) {
		scanf("%d%d%d", &s, &t, &c);
		rep(j,s,t) a[i][j] = -1; a[i][0] = c;
	}
	printf("%d\n", solve());
}