#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)
using namespace std;

const int MAXN = 1010;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

int n, m, a[MAXN][MAXN], c[MAXN][MAXN], inp[MAXN], oup[MAXN], vs, vt, cur, vis[MAXN], b[MAXN][MAXN], fim[MAXN][MAXN];

inline int Dfs(int u, int f) {
	if (u == vt) return f;
	vis[u] = cur; rep(i,vt) if (c[u][i] > 0 && vis[i] != cur) {
		int d = Dfs(i, min(f, c[u][i]));
		if (d) return c[u][i] -= d, c[i][u] += d, d;
	}
	return 0;
}

inline bool check(int mid) {
	memset(c, 0, sizeof c); memset(inp, 0, sizeof inp); memset(oup, 0, sizeof oup);
	rep(i,n) rep(j,n) if (a[i][j] - a[0][0]) {
		if (a[i][j] <= mid) {
			if (a[j][i] <= mid) {
				if (i < j) c[i][j] = 1, inp[j]++, oup[i]++;
			} else inp[j]++, oup[i]++;
		} else if (a[j][i] > mid) return false;
	}
	rep(i,n) if ((inp[i] - oup[i]) % 2 != 0) return false; else {
		if (inp[i] > oup[i] ) c[i][vt] = (inp[i] - oup[i]) >> 1; else c[vs][i] = (oup[i] - inp[i]) >> 1;
	}
	int ret = 0;
	while (cur++, Dfs(vs,2));
	rep(i, n) ret += c[vs][i];
	return !ret;
}

int stack[MAXN << 1], top = 0;
void Dfs(int u) {
	rep(i,n) if (b[u][i]) {b[u][i] = 0; Dfs(i);}
	stack[++top] = u;
}

int main(void) {
	//freopen("in", "r", stdin);
	n = ScanInt(), m = ScanInt(); memset(a, 60, sizeof a); rep(i,n) a[i][i] = 0; vs = n + 1, vt = vs + 1;
	rep(i, m) {
		int x = ScanInt(), y = ScanInt(); a[x][y] = ScanInt(), a[y][x] = ScanInt(); fim[x][y] = fim[y][x] = i;
	}
	int l = 0, r = 1000;
	while (l <= r) {
		int mid = (l + r) >> 1;
		if (check(mid)) r = mid - 1; else l = mid + 1;
	}
	if (l <= 1000) {
		printf("%d\n", l); 
		check(l); 
		rep(i, n) rep(j, n) if (i != j && a[i][j] <= l) {
			if (a[j][i] <= l) {
				if (c[i][j]) b[i][j] = 1; else b[j][i] = 1;
			} else b[i][j] = 1;
		}
		Dfs(1);
		for (int i = m + 1; i >= 2; i--) printf("%d ", fim[stack[i]][stack[i-1]]);
	}else puts("NIE");
	return 0;
}

