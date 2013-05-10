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
	const int MAXN = 1005;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct _{
		int x, y;
	}a[MAXN];
	int n;
	bool hash[MAXN][MAXN], m[MAXN][MAXN], vis[MAXN];

	inline void Dfs(int u) {
		vis[u] = true;
		for (int i = 1; i <= n; i++) if (m[u][i] && !vis[i]) {
			Dfs(i);
		}
	}

	inline void solve(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) {
			a[i].x = ScanInt(), a[i].y = ScanInt();
			hash[a[i].x][a[i].y] = true;
		}
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++) if (hash[a[i].x][a[j].y] || hash[a[j].x][a[i].y]) {
				m[i][j] = m[j][i] = true;
			}
		}
		int ret = 0;
		for (int i = 1; i <= n; i++) if (!vis[i]) Dfs(i), ++ret;
		printf("%d\n", ret - 1);
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
