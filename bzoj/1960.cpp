#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 20002;
	const int MAXM = 1002;

	int n, m, a[MAXN];
	inline void Input(void) {
		scanf("%d %d", &m, &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i), m = std::max(m, a[i]);
	}

	int L[MAXM], R[MAXM], D[MAXN];
	void solve(void) {
		Input();
		int last = 0, ret = 0;
		for (int i = 1; i <= n >> 1; i++) {
			L[a[i]]++, R[a[i]]--;
			for (int j = last + 1; j <= i * 2; j++) R[a[j]]++; last = i * 2;
			bool OK = true;
			for (int j = m; j >= 1; j--) {
				D[j] = D[j + 1] + R[j + 1] - L[j];
				if (D[j] < 0) OK = false;
			}
			if (OK) ret = std::max(ret, i);
		}
		printf("%d\n", ret);
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
