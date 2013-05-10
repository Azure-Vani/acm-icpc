//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

#define rep(i,l,r) for(int i = l; i <= r; i++)

int n, m;

namespace Solve {
	const int MAXN = 404;
	const int inf = 1000001;

	int a[MAXN];
	struct Vol {
		int c, q;
	}c[MAXN];

	void solve(void) {
		rep(i,1,n) scanf("%d",a + i);
		std::sort(a + 1, a + n + 1);std::reverse(a + 1, a + n + 1);
		rep(i,1,m) scanf("%d%d",&c[i].c, &c[i].q);
		int cnt = 0, sum = 0;
		rep(i,1,n) {
			int pos = 0, min = inf;
			rep(j,1,m) if (c[j].c && c[j].q >= a[i] && c[j].q < min) min = c[j].q, pos = j;
			if (pos) {
				c[pos].c--;
				cnt++;
				sum += a[i];
			}
		}
		printf("%d %d\n", cnt, sum);
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	while (scanf("%d%d", &n, &m), n || m)
	Solve::solve();
	return 0;
}
