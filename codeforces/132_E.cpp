#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <iostream>
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
	typedef long long Int64;
	const int MAXN = 66;

	bool c[MAXN][MAXN]; int pre[MAXN];

	inline Int64 Gao(int *P, int n, int k) {
		if (P[1] == -1) {
			return (n / k - 1) * ((1 << k) - 1);
		}
		int u = k;
		for (int i = 1; i <= k && P[i] != -1; i++, u--) {
			for (int j = i + k; j <= n; j += k) {
				if (P[i] != P[j] && P[j] != -1) return 0;
			}
		}
		return 1 << u;
	}

	inline Int64 Dp(int n) {
		Int64 ret = 0; int *v = pre + 1; while (v - pre <= n && *v == 0) ++v;
		n -= v - pre - 1;
		for (int i = 1; i * i <= n; i++) if (n % i == 0) {
			ret += Gao(v - 1, n, i);
		}
		return ret;
	}

	inline Int64 Cal(Int64 N) {
		if (N <= 1) return 0;
		Int64 ret = 0;
		int v = 1; while ((1ll << v) <= N) ++v; --v;
		memset(pre, -1, sizeof pre);
		for (int i = v; i >= 0; i--) {
			for (int k = 0; (k - (i == 0)) < (bool)(N & (1ll << i)); ++k) {
				pre[v - i + 1] = k;
				ret += Dp(v + 1);
			}
			pre[v - i + 1] = (bool)(N & (1ll << i));
		}
		return ret;
	}

	inline void solve(void) {
		Int64 L, R; cin >>L>>R;
		cout <<Cal(R) - Cal(L - 1)<<endl;
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
