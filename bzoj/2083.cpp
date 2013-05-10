//#define Debug
#include <cstdio>
#include <algorithm>
#include <vector>
namespace Solve {
	typedef std::vector<int> VII;
	const int MAXN = 1000010;

	int n, a[MAXN]; VII T[MAXN];
	void Input(void) {
		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i]), T[a[i]].push_back(i);
	}

	void Work(void) {
		int m, now = 1, tmp = 0;
		scanf("%d\n", &m);
		for (int i = 1, t; i <= m; i++) {
			scanf("%d", &t);
			VII::iterator it = std::lower_bound(T[t].begin(), T[t].end(), now);
			if (it == T[t].end()) tmp = 1;
			else now = *it + 1;
		}
		puts(tmp?"NIE":"TAK");
	}
	void solve(void) {
		Input();
		int p; scanf("%d\n", &p);
		while (p--) Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
