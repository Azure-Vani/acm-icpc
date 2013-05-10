//#define FILEIO

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
#include <map>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int Mod = 20120427;
	typedef long long Int64;

	map<Int64, pair<Int64, Int64> > f[19];
	pair<Int64, Int64> g[19];

	inline void Init(void) {
		f[0][1] = mp(1, 0);
		g[0] = mp(1, 0);
		for (int i = 1; i <= 18; i++) {
			foreach(it, f[i - 1]) {
				pair<Int64, pair<Int64, Int64> > t = *it;
				for (int j = 0; j <= 9; j++) {
					pair<Int64, Int64> &tmp = f[i][j * t.first];
					tmp.first += t.second.first;
					tmp.second += (t.second.second * 10ll % Mod + j * t.second.first % Mod);
					tmp.second %= Mod;
					tmp.first %= Mod;
				}
			}
			foreach(it, f[i]) {
				g[i].first = (g[i].first + it->second.first) % Mod;
				g[i].second = (g[i].second + it->second.second) % Mod;
			}
		}
	}

	inline Int64 Digit(Int64 n) {
		Int64 ret = 1;
		while (n) ret *= n % 10, n /= 10;
		return ret;
	}

	inline Int64 Cal(Int64 l, Int64 r, Int64 k) {
		Int64 ret = 0;
		while (l <= r) {
			Int64 p = 0, pow = 1;
			while (true) {
				Int64 t_pow = pow * 10;
				if (l % t_pow == 0 && l + t_pow - 1 <= r) {
					pow = t_pow;
					p++;
				} else break;
			}
			Int64 pre = Digit(l / pow);
			if (pre == 0 && k == 0) {
				Int64 tmp = l % Mod;
				tmp = tmp * g[p].first % Mod;
				ret = (ret + tmp + g[p].second) % Mod;
			}
			if (pre != 0 && k % pre == 0) {
				Int64 t = k / pre;
				Int64 tmp = l % Mod;
				tmp = tmp * f[p][t].first % Mod;
				ret = (ret + tmp + f[p][t].second) % Mod;
			}
			l += pow;
		}
		return ret;
	}

	inline Int64 force(Int64 l, Int64 r, Int64 k) {
		Int64 ret = 0;
		for (Int64 i = l; i <= r; i++) 
			if (Digit(i) == k) ret = (ret + i) % Mod;
		return ret;
	}

	inline void solve(void) {
		Init();
		int T; for (scanf("%d", &T); T; T--) {
			Int64 l, r, k, Ans; scanf(LL LL LL, &l, &r, &k);
			printf(LL "\n", Ans = Cal(l, r, k));
#ifdef FILEIO
			Int64 Check = force(l, r, k);
			fprintf(stderr, "Your Ans: %lld   Correct: %lld\n", Ans, Check);
			assert(Check == Ans);
#endif
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
