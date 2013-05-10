//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 200050;
	int n, m;
	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXN];

	int inp[MAXN] = {0};
	void solve(void) {
		scanf("%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int x, y;
			scanf("%d%d", &x, &y);
			inp[x]++, inp[y]++;
		}
		for (int i = 1; i <= n; i++) if (!inp[i]) {
			puts("NIE");
			return;
		}
		puts("TAK");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
