//#define Debug
#include <cctype>
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 1000003;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n, L, list[MAXN], f[MAXN];
	void solve(void) {
		n = ScanInt(), L = ScanInt();
		int Ans = 0;
		for (int i = 1; i <= n; i++) {
			int l = 0, tmp = ScanInt();
			for (int j = 1; j * j <= tmp; j++)
				if (tmp % j == 0)
					list[++l] = j, list[++l] = tmp / j;
			int max = 0;
			for (int j = 1; j <= l; j++) if (list[j] >= L)
				max = std::max(max, f[list[j]] + 1);
			for (int j = 1; j <= l; j++)
				f[list[j]] = std::max(f[list[j]], max);
			Ans = std::max(Ans, max);
		}
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
