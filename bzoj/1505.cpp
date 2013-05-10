//#define Debug
#include <cstdio>
#include <cmath>
#include <algorithm>
namespace Solve {
	const double inf = 0x6eeeeeee;
	double k1, k2; int m, n;

	inline double Cal(int L, double k) {
		return L * L * k;
	}
	inline double Cal(int L, int n) {
		int L1 = L / n, L2 = L % n;
		return  L2 * Cal(L1 + 1, k2) + (n - L2) * Cal(L1, k2) + Cal(L, k1);
	}
	inline double Cal(int L, int n, int m) {
		int L1 = L / n, L2 = L % n;
		return L2 * Cal(L1 + 1, m) + (n - L2) * Cal(L1, m);
	}

	void solve(void) {
		scanf("%lf%lf%d%d", &k1, &k2, &n, &m);
		int n1 = n - m % n, n2 = m % n;
		int m1 = m / n, m2 = m / n + 1;
		double Ans = inf;
		if (!n2) {
			printf("%.1lf\n", Cal(100, n1, m1));
			return;
		}
		for (int i = n1 * m1; i + n2 * m2 <= 100; i++) {
			double now = Cal(i, n1, m1) + Cal(100 - i, n2, m2);
			Ans = std::min(now, Ans);
		}
		printf("%.1lf\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
