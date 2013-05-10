//#define FILEIO

#define INPUT "seventeen.in"
#define OUTPUT "seventeen.out"

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

typedef long long Int64;

namespace Solve {
	const int MAXN = 220;
	const int MAXM = MAXN * MAXN;
	const Int64 INF = 100000000000000000ll;


	Int64 f[2][MAXM << 1];

	inline Int64 Cal(Int64 a[], Int64 n) {
		memset(f, 55, sizeof f);
		Int64 S = MAXM, sum = 0;
		f[0][S] = 0;
		for (Int64 i = 1; i <= n; i++) {
			for (Int64 j = S - sum - a[i]; j <= S + sum + a[i]; j++) 
				f[i & 1][j] = INF;
			for (Int64 j = S - sum; j <= S + sum; j++) {
				f[i & 1][j + a[i]] = min(f[i & 1][j + a[i]], f[(i - 1) & 1][j] + (j - S) * a[i]);
				f[i & 1][j - a[i]] = min(f[i & 1][j - a[i]], f[(i - 1) & 1][j] - (j - S) * a[i]);
			}
			sum += a[i];
		}
		Int64 ret = INF;
		for (Int64 i = S - sum; i <= S + sum; i++) 
			ret = min(ret, f[n & 1][i]);
		return ret;
	}

	Int64 X[MAXN], Y[MAXN], n;
	inline void solve(void) {
		scanf("%lld", &n);
		for (int i = 1; i <= n; i++)
			scanf("%lld%lld", X + i, Y + i);
		Int64 Ans = Cal(X, n) + Cal(Y, n);
		printf("%.2f\n", (double)Ans);
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