//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <map>
#include <set>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	typedef long long Int64;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	Int64 mod = 1000000007;

	inline Int64 Pow(Int64 a, Int64 n) {
		a %= mod;
		Int64 ret = 1;
		while (n) {
			if (n & 1) ret = ret * a % mod;
			a = a * a % mod;
			n >>= 1;
		}
		return ret;
	}

	map<Int64, Int64> S;
	set<pair<Int64, Int64> > T;

	inline void solve(void) {
		Int64 n = ScanInt(), m = ScanInt(), k = ScanInt();
		for (int i = 1; i <= k; i++) {
			Int64 a = ScanInt(), b = ScanInt();
			if (T.find(mp(a, b)) != T.end()) continue;
			T.insert(mp(a, b));
			S[a] = S[a] + b;
		}
		Int64 sum = n * (n + 1) / 2;
		Int64 A1 = Pow(sum, m - S.size());
		Int64 A2 = 1;
		foreach(it, S) {
			A2 = A2 * ((sum - it->second) % mod) % mod;
		}
		printf("%lld\n", A1 * A2 % mod);
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