#include <cstdio>
#include <algorithm>
#include <cmath>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	
	int p, v; Int64 n;

	inline Int64 Work(int k) {
		Int64 eps = (Int64) pow(n, 1.0 / k);
		int i = 0;
		for (; std::pow(double(eps + 1), double(i)) * pow(double(eps), double(k - i)) < n; i++) {}
		return (eps * k + i) * p + k * v;
	}

	void solve(void) {
		scanf(LL "%d%d", &n, &p, &v);
		Int64 Ans = 100000000000000ll;
		for (int i = 1; (1ll << i) <= n; i++) {
			Int64 t = Work(i);
			Ans = std::min(Ans, t);
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
