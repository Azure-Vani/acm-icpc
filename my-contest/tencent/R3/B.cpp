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

	const int MAXN = 100;

	int len[100] = {4,3,3,5,4,4,3,5,5,4,3,6,6,8,8,7,7,9,8,8,6,9,9,11,10,10,9,11,11,10,6,9,9,11,10,10,9,11,11,10,5,8,8,10,9,9,8,10,10,9,5,8,8,10,9,9,8,10,10,9,5,8,8,10,9,9,8,10,10,9,7,10,10,12,11,11,10,12,12,11,6,9,9,11,10,10,9,11,11,10,6,9,9,11,10,10,9,11,11,10};

	vector<int> T[20];

	inline void solve(void) {
		for (int i = 0; i < 100; i++) if (len[i] <= 9) T[len[i]].pb(i);
		int Q; scanf("%d", &Q); rep(_,Q) {
			printf("Case #%d: ", _);
			int n, m; scanf("%d%d", &n, &m);
			if (m <= T[n].size()) {
				printf("%d\n", T[n][m - 1]);
			} else if (n > 6 && m - T[n].size() <= T[n - 6].size()) {
				printf("%d", T[n - 6][m - T[n].size() - 1]);
				rep(i, 100) putchar('0');
				puts("");
			} else puts("-1");
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
