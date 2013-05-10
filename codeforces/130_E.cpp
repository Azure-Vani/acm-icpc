//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 100010;

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXN];

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	int root, n, m;
	int f[20][MAXN], list[MAXN], pos, begin[MAXN], end[MAXN], deep[MAXN];
	vector<int> V[MAXN];

	inline int Up(int x, int k) {
		for (int i = 19; i >= 0; i--) if (k & (1 << i)) x = f[i][x];
		return x;
	}

	inline void Dfs(int u) {
		list[++pos] = deep[u]; begin[u] = pos;
		for (int i = 1; (1 << i) <= deep[u]; i++) f[i][u] = f[i - 1][f[i - 1][u]];
		for (Edge *p = a[u]; p; p = p->next) {
			f[0][p->y] = u;
			deep[p->y] = deep[u] + 1;
			Dfs(p->y);
		}
		end[u] = pos;
	}

	inline int Cal(int x, int c) {
		int l = begin[x], r = end[x];
		return upper_bound(V[c].begin(), V[c].end(), r) - lower_bound(V[c].begin(), V[c].end(), l);
	}

	inline void solve(void) {
		n = ScanInt();n++;
		for (int i = 2; i <= n; i++) {
			int x = ScanInt(); x++;
			a[x] = new Edge(i, a[x]);
		}
		Dfs(1);
		for (int i = 1; i <= n; i++) V[list[i]].pb(i);
		m = ScanInt();
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), q = ScanInt(); x++;
			if (deep[x] <= q) {printf("0 "); continue;}
			int f = Up(x, q);
			int s = Cal(f, deep[x]), sx = Cal(x, deep[x]);
			printf("%d ", s - sx);
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
