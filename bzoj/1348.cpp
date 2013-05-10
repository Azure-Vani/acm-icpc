//#define Debug
#include <cstdio>
#include <algorithm>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 200050;
	const Int64 inf = 100000000000000000ll;

	Int64 n, c[MAXN]; Int64 k, t;
	void Input(void) {
		scanf(LL "%d%d", &n, &t, &k);
		for (int i = 1; i <= k; i++) scanf(LL, &c[i]);
	}

	inline double Cal(Int64 sum) {
		double ret = 0;
		for (int i = 1; i <= k; i++) {
			if (sum < c[i]) break;
			double tmp = (sum - c[i]) / t; tmp++;
			ret += (tmp * (tmp + 1ll)) * 2;
			if (ret > n) return n + 1;
		}
		return ret;
	}

	void solve(void) {
		Input();
		Int64 l = 0, r = inf;
		while (l <= r) {
			Int64 mid = (l + r) >> 1;
			double tmp = Cal(mid);
			if (tmp < n)
				l = mid + 1ll;
			else 
				r = mid - 1ll;
		}
		Int64 Ans = 0, sum = l, delta = 0;
		for (int i = 1; i <= k; i++) {
			if (sum < c[i]) break;
			Int64 tmp = (sum - c[i]) / t;
			Int64 T1 = ((tmp * (tmp + 1ll) * (tmp * 2ll + 1ll)) / 6 + (tmp * (tmp + 1)) / 2) * t;
			Int64 T2 = (tmp + 1ll) * (tmp + 2ll) / 2 * c[i];
			Ans += (T1 + T2) << 2;
			delta += (tmp + 1ll) * (tmp + 2ll) << 1;
		}
		printf(LL "\n", Ans - (delta - n) * sum);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
