#define FILEIO

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXM = 600;
	const int MAXN = MAXM * MAXM;
	const long long inf = 100000000000000000ll;

	typedef long long Int64;

	struct Node {
		Int64 l, r, fac;
		bool diagonal;
		inline friend bool operator <(const Node &a, const Node &b) {
			return a.fac < b.fac;
		}
	}a[MAXN];

	int cnt;

	inline bool Input(void) {
		int n;
		if (!~scanf("%d", &n)) return false;
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			for (int j = i; j <= n; j++) {
				cnt++;
				scanf(LL LL LL, &a[cnt].fac, &a[cnt].l, &a[cnt].r);
				if (i == j) a[cnt].fac <<= 1, a[cnt].diagonal = true;
				else a[cnt].l <<= 1, a[cnt].r <<= 1, a[cnt].diagonal = false;
			}
		}
		return true;
	}

	Int64 closestR[MAXN];

	inline Int64 Greedy(void) {
		sort(a + 1, a + cnt + 1);
		Int64 sumR = 0, sumL = 0, sumUpper = 0, sumLower = 0;
		for (int i = 1; i <= cnt; i++) {
			sumR += a[i].fac * a[i].r;
			sumUpper += a[i].r;
		}
		Int64 C = inf;
		for (int i = cnt; i >= 1; i--) {
			if (a[i].diagonal) C = a[i].fac;
			closestR[i] = C;
		}
		Int64 ret = -inf, closestL = -inf;
		for (int i = 1; i <= cnt; i++) {
			sumR -= a[i].fac * a[i].r;
			sumUpper -= a[i].r;
			Int64 tmp = -sumUpper - sumLower;
			if (a[i].diagonal) closestL = a[i].fac;
			if (a[i].l <= tmp && tmp <= a[i].r) {
				if (a[i].diagonal || tmp % 2 == 0)
					ret = max(ret, sumR + sumL + tmp * a[i].fac);
				else {
					if (tmp != a[i].r) {
						ret = max(ret, sumR + sumL + (tmp + 1) * a[i].fac - closestR[i]);
					}
					if (tmp != a[i].l) {
						ret = max(ret, sumR + sumL + (tmp - 1) * a[i].fac + closestL);
					}
				}
			}
			sumL += a[i].fac * a[i].l;
			sumLower += a[i].l;
		}
		assert(ret != -inf);
		return ret >> 1;
	}

	inline void solve(void) {
		while (true) {
			if (!Input()) break;
			printf(LL "\n", Greedy());
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

