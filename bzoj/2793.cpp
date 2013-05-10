//#define FILEIO

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
	const int MAXN = 1000010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	long long last[MAXN], N = 0;
	bool lucky[MAXN], used[MAXN];
	vector<long long> ans;

	inline void solve(void) {
		int m = ScanInt();
		for (long long i = 1, t; i <= m; i++) t = ScanInt(), lucky[t] = true, N = max(N, t);
		for (int i = 1; i <= N; i++) last[i] = 1;
		long long n = ScanInt(), num = 0;
		for (long long i = 1; i <= n; i++) {
			long long t = ScanInt(), n_num = num + t, tmp = t, cnt = 1;
			tmp *= last[t];
			while (tmp <= N && cnt <= t) {
				if (!used[tmp]) {
					used[tmp] = true;
					num++;
					if (lucky[tmp]) {
						ans.pb(num);
					}
					cnt++;
				}
				last[t]++;
				tmp += t;
			}
			num = n_num;
		}
		printf("%d\n", ans.size());
		sort(ans.begin(), ans.end());
		foreach(it, ans) printf("%lld\n", *it);
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