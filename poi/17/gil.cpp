#include <cstdio>
#include <algorithm>
#include <cctype>
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)
using namespace std;

const int MAXN = 200010;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

struct Edge {
	int y; Edge *next;
	Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN];

int n, m, inp[MAXN], color[MAXN];

inline void Dfs(int u, int c) {
	color[u] = c;
	for (Edge *p = a[u]; p; p = p->next) if (!color[p->y]) {
		Dfs(p->y, c ^ 3);
	}
}

int main(void) {
	//freopen("in", "r", stdin);
	n = ScanInt(), m = ScanInt();
	rep(i,m) {
		int x = ScanInt(), y = ScanInt();
		a[x] = new Edge(y, a[x]);
		a[y] = new Edge(x, a[y]);
		inp[x] ++, inp[y] ++;
	}
	rep(i,n) if (!inp[i]) {puts("NIE"); return 0;}
	rep(i,n) if (!color[i]) Dfs(i,1); puts("TAK");
	rep(i,n) puts(color[i]==1?"K":"S");
	return 0;
}

