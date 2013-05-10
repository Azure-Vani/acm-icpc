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
#define foreach(i,T) for(__typeof(T.begin();) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	inline void solve(void) {
		int n, m; scanf("%d%d", &n, &m);
		int cnt = 0;
		for (int a = 0; a <= 1000; a++) 
			for (int b = 0; b <= 1000; b++) if (a != b) {
				if (a*a + b == n && a + b * b == m) cnt++;
			}
		for (int a = -1000; a <= 1000; a++) if (a * a + a == n && n == m) cnt++;
		printf("%d\n", cnt);
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
