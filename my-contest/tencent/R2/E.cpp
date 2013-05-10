#define FILEIO

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
#define rep(i,n) for(int i = 1; i <= n; i++)

using namespace std;

namespace Solve {
	const int MAXN = 200;
	const int MAXM = 2000;

	int n, m;
	int f[MAXN][MAXM], a[MAXN][MAXN];

	inline void solve(void) {
		while (scanf("%d%d", &n, &m) == 2) {
			memset(a, 0, sizeof a); memset(f, -1, sizeof f);
			int S = (1 << m) - 1;
			rep(i,n) rep(i,m) {
				scanf("%d", &a[i][j]); 
			}
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
