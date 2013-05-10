//#define Debug
#include <algorithm>
#include <cstdio>
#define abs(x) ((x) < 0 ? (-(x)) : (x))
namespace Solve {
	const double eps = 0.000000001;
	void solve(void) {
		double p, q, p1, q1, s1, s2, N = 0, P = 1; int n;
		scanf("%d%lf%lf", &n, &p, &q);
		p1 = 1 - p, q1 = 1 - q;
		s1 = 1 / (1 - p1 * q1), s2 = 1 / (1 - p * q);
		for (int i = 1; i <= n; i++) {
			double tn = N, tp = P;
			N = (tn * p1 * q + tp * p) * s1;
			P = (tp * q1 * p + tn * q) * s1;
			std::swap(p1, p); std::swap(q1, q); std::swap(s1, s2);
			if (abs(N - tn) <= eps) break;
		}
		printf("%.6lf\n", N);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	int _; scanf("%d", &_);
	while (_--) Solve::solve();
	return 0;
}
