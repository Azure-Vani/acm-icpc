#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {

	const int MAXN = 106;

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

	int n, m, stack[MAXN], top;

	void Dfs(int u, int f) {
		stack[++top] = u;
		for (Edge *p = a[u]; p; p = p->next) if (p->y != f) Dfs(p->y, u);
	}

	inline void solve(void) {
		n = ScanInt(), m = ScanInt();
		rep(i,m) {
			int x = ScanInt(), y = ScanInt();
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
		}
		Dfs(1, 0);
		rep(i,top - 1) printf("%d ", stack[i]); printf("%d\n", stack[top]);
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
