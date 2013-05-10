//efine FILEIO

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
	const int MAXN = 60;
	
	string a[MAXN]; int n;

	inline bool OK(int x, int y) {
		return (a[x][0] == a[y][0] || a[x][1] == a[y][1]);
	}

	bool f[MAXN][MAXN][MAXN][MAXN];

	inline void solve(void) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >>a[i];
		if (n == 1) {puts("YES"); return;}
		if (n == 2) {if (OK(1, 2)) puts("YES"); else puts("NO"); return; }
		f[n - 2][n - 2][n - 1][n] = true;
		for (int i = n - 2; i > 1; i--) {
			for (int l3 = 1; l3 <= n; l3++) 
				for (int l2 = 1; l2 <= n; l2++) 
					for (int l1 = 1; l1 <= n; l1++) if (f[i][l3][l2][l1]) {
						if (OK(l1, l2)) f[i - 1][i - 1][l3][l1] = true;
						if (OK(l1, i - 1)) f[i - 1][l1][l3][l2] = true;
					}
		}
		for (int l3 = 1; l3 <= n; l3++) 
			for (int l2 = 1; l2 <= n; l2++) 
				for (int l1 = 1; l1 <= n; l1++) if (f[1][l3][l2][l1]) {
					if (OK(l1, l3) && OK(l1, l2)) {puts("YES"); return; }
				}
		puts("NO");
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
