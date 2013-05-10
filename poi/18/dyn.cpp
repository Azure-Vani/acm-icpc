#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

using namespace std;

const int MAXN = 300010;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

struct Edge {
	int y; Edge *next, *opt; bool flag;
	Edge(int  y, Edge *next):y(y), next(next){flag = true;}
}*a[MAXN];

int n, m, bomb[MAXN], deep[MAXN];

int f[MAXN], g[MAXN], cnt, k;

inline void Dfs(int u) {
	int Max = bomb[u] ? deep[u] : -MAXN, tmp = MAXN * 2;
	for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
		p->opt->flag = false; deep[p->y] = deep[u] + 1;
		Dfs(p->y);
		Max = max(f[p->y], Max); tmp = min(tmp, g[p->y]);
	}
	if (tmp + Max - 2 * deep[u] <= k) {
		f[u] = -MAXN, g[u] = tmp;
	} else if (Max - deep[u] == k || u == 1) {
		cnt++; f[u] = -MAXN, g[u] = deep[u];
	} else {
		f[u] = Max, g[u] = tmp;
	}
}

int main(void) {
	//freopen("in", "r", stdin);
	n = ScanInt(), m = ScanInt();
	for (int i = 1; i <= n; i++) bomb[i] = ScanInt();
	for (int i = 1; i <  n; i++) {
		int x = ScanInt(), y = ScanInt();
		a[x] = new Edge(y, a[x]); a[y] = new Edge(x, a[y]);
		a[x]->opt = a[y], a[y]->opt = a[x];
	}
	int l = 0, r = n;
	while (l <= r) {
		int mid = (l + r) >> 1; k = mid, cnt = 0; memset(f, 0, sizeof f); memset(g, 0, sizeof g);
		Dfs(1);
		if (cnt <= m) r = mid - 1; else l = mid + 1;
	}
	printf("%d\n", l);
	return 0;
}

