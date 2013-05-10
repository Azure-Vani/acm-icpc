//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cmath>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	typedef long long Int64;

	typedef pair<long long, long long> PII;

	long long gcd(long long a, long long b) {
		return !b ? a : gcd(b, a % b);
	}

	PII F(long long p1, long long q1, long long p2, long long q2) {
		long long l = (long long)floor((double)p1 / (double)q1) + 1, r = (long long)ceil((double)p2 / (double)q2) - 1;
		PII ret;
		if (l <= r) {
			ret.second = 1;
			ret.first = l;
			return ret;
		}
		if (p1 == 0) {
			return PII(1, (long long)floor((double)q2 / (double)p2) + 1);
		}
		if (p1 <= q1 && p2 <= q2) {
			ret = F(q2, p2, q1, p1);
			std::swap(ret.first, ret.second);
			return ret;
		}
		long long t = p1 / q1;
		ret = F(p1 - q1 * t, q1, p2 - q2 * t, q2);
		ret.first += ret.second * t;
		return ret;
	}

	inline void solve(void) {
		long long p1, q1, p2, q2, t;
		while (scanf("%lld%lld%lld%lld", &p1, &q1, &p2, &q2) == 4) {
			t = gcd(p1, q1), p1 /= t, q1 /= t;
			t = gcd(p2, q2), p2 /= t, q2 /= t;
			PII Ans = F(p1, q1, p2, q2);
			printf("%lld/%lld\n", Ans.first, Ans.second);
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		//freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}