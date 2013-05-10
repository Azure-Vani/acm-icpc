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

	const int MAXN = 6;

	int a[MAXN][MAXN]; char ch[MAXN];

	bool Gao(int t) {
		for (int i = 1; i <= 4; i++) {
			int tmp = 1;
			for (int j = 1; j <= 4; j++) {
				if (a[i][j] == 3) {tmp--; continue;}
				if (a[i][j] != t) {tmp = -1; break;}
			}
			if (tmp >= 0) return true;
		}
		for (int j = 1; j <= 4; j++) {
			int tmp = 1;
			for (int i = 1; i <= 4; i++) {
				if (a[i][j] == 3) {tmp--; continue;}
				if (a[i][j] != t) {tmp = -1; break;}
			}
			if (tmp >= 0) return true;
		}
		int tmp = 1;
		for (int i = 1; i <= 4; i++) {
			if (a[i][i] == 3) {tmp--; continue;}
			if (a[i][i] != t) {tmp = -1; break;}
		}
		if (tmp >= 0) return true;
		tmp = 1;
		for (int i = 1; i <= 4; i++) {
			if (a[i][4 - i + 1] == 3) {tmp--; continue;}
			if (a[i][4 - i + 1] != t) {tmp = -1; break;}
		}
		if (tmp >= 0) return true;
		return false;
	}

	inline void solve(void) {
		int kase; scanf("%d", &kase); rep(_, kase) {
			printf("Case #%d: ", _);
			int s = 0;
			REP(i, 1, 4) {
				scanf("%s", ch + 1);
				REP(j, 1, 4) {
					if (ch[j] == 'X') a[i][j] = 1, s++;
					if (ch[j] == 'O') a[i][j] = 2, s++;
					if (ch[j] == 'T') a[i][j] = 3, s++;
				}
			}
			int ok1 = Gao(1);
			int ok2 = Gao(2);
			if (ok1) puts("X won"); else
			if (ok2) puts("O won"); else 
			if (s == 16) puts("Draw"); else puts("Game has not completed");
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
