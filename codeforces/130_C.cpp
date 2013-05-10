#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <iostream>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	typedef long long Int64;
	const int MAXN = 110;

	int a[MAXN][MAXN]; Int64 sum[MAXN][MAXN];

	inline void solve(void) {
		int n, m; cin >> n>> m;
		while (m--) {
			int x, y; cin >> x >> y;
			a[x][y] = a[y][x] = 1;
			sum[x][y] = sum[y][x] = 1;
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
