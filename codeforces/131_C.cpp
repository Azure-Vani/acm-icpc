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
	const int MAXN = 300;

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

	int f[MAXN][4];
	int n, c[MAXN], inp[MAXN];
	int father[MAXN];
	int d[4][MAXN], head[4] = {1, 1, 1, 1}, tail[4];
	int tmp[MAXN];

	inline void solve(void) {
		n = ScanInt(); for (int i = 1; i <= n; i++) c[i] = ScanInt() - 1;
		for (int i = 1; i <= n; i++) {
			int t = ScanInt();
			for (int j = 1; j <= t; j++) {
				int x = ScanInt();
				a[x] = new Edge(i, a[x]);
				inp[i]++;
				tmp[i]++;
			}
		}
		int ret = 1000000000;
		for (int u = 0; u < 3; u++) {
			for (int i = 0; i <= 2; i++) tail[i] = 0, head[i] = 1;
			memcpy(inp, tmp, sizeof inp);
			for (int i = 1; i <= n; i++) if (!inp[i]) d[c[i]][++tail[c[i]]] = i;
			int now = u;
			int ans = 0;
			for (int i = now; ; i++, i = i % 3) {
				while (head[i] <= tail[i]) {
					int now = d[i][head[i]++];
					for (Edge *p = a[now]; p; p = p->next) {
						if (!--inp[p->y]) d[c[p->y]][++tail[c[p->y]]] = p->y;
					}
					ans++;
				}
				bool v = 0;
				for (int j = 0; j < 3; j++) if (head[j] <= tail[j]) v = true;
				if (!v) break;
				ans++;
			}
			ret = min(ret, ans);
		}
		printf("%d\n", ret);
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
