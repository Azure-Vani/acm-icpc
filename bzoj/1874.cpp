#include <cstring>
//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 10005;
	
	int n, a[MAXN], m, b[MAXN], max = 0;
	void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i), max = std::max(max, a[i]);
		scanf("%d", &m);
		for (int i = 1; i <= m; i++) scanf("%d", b + i);
	}

	int sg[MAXN];
	void solve(void) {
		Input();
		bool vis[MAXN] = {0};
		for (int i = 1; i <= max; i++, memset(vis, 0, sizeof vis)) {
			for (int j = 1; j <= m; j++) if (b[j] <= i)
				vis[sg[i - b[j]]] = true;
			for (int j = 0;; j++) if (!vis[j]) {sg[i] = j;break;}
		}
		int ret = 0;
		for (int i = 1; i <= n; i++) ret ^= sg[a[i]];
		if (ret) {
			puts("YES");
			for (int i = 1; i <= n; i++) {
				ret ^= sg[a[i]];
				for (int j = 1; j <= m; j++) if (b[j] <= a[i])
					if ((ret ^ (sg[a[i] - b[j]])) == 0) {
						printf("%d %d\n", i, b[j]);
						return;
					}
				ret ^= sg[a[i]];
			}
		}else puts("NO");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
