#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 620020;
	const int Mod = 1000000009;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n, d, a[MAXN];

	inline void Input(void) {
		n = ScanInt(), d = ScanInt();
		for (int i = 1; i <= n; i++) a[i] = ScanInt();
		std::sort(a + 1, a + n + 1);
	}

	inline void solve(void) {
		Input();
		int p = 1, Ans = 1, t;
		for (int i = 1; i <= n; i++) {
			while (p <= n && a[p] - a[i] <= d) p++;
			t = p - i;
			Ans = (long long) Ans * t % Mod;
		}
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	//	freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
