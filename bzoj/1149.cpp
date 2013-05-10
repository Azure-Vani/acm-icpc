//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 100005;
	struct pair {
		int l, r, maxdeep, mindeep;
	}a[MAXN];
	int n;

	void Input(void) {
		memset(a, 0,sizeof a);
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d %d", &a[i].l, &a[i].r);
			if (a[i].l == -1) a[i].l = 0;
			if (a[i].r == -1) a[i].r = 0;
		}
	}

	void Fail(void) {puts("-1"); exit(0);}
	int MAX = 0, MIN = 10000000;
	void Dfs(int u, int sum) {
		if (u == 0) {return;}
		Dfs(a[u].l, sum + 1);
		Dfs(a[u].r, sum + 1);
		a[u].maxdeep = std::max(a[a[u].l].maxdeep, a[a[u].r].maxdeep) + 1;
		a[u].mindeep = std::min(a[a[u].l].mindeep, a[a[u].r].mindeep) + 1;
		if (a[a[u].l].mindeep != a[a[u].l].maxdeep && a[a[u].r].mindeep != a[a[u].r].maxdeep) Fail();
	}
	int Dfs(int u) {
		if (u == 0) return 0;
		int L = Dfs(a[u].l);
		int R = Dfs(a[u].r);
		return L + R + (a[a[u].l].mindeep < a[a[u].r].maxdeep);
	}
	void solve(void) {
		Input();
		Dfs(1, 0);if (a[1].maxdeep - a[1].mindeep >= 2) Fail();
		printf("%d\n", Dfs(1));
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
