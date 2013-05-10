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
#define rep(i,n) for(int i = 1; i <= n; i++)

using namespace std;

namespace Solve {
	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	long long f[200]; long long mod = 1000000007;

	inline void solve(void) {
		int kase = ScanInt();
		rep(_, kase) {
			int n = ScanInt();
			memset(f, 0, sizeof f);
			f[2] = 1;
			for (int i = 3; i <= n; i++) {
				long long tmp = f[i - 1] + f[i - 2];
				tmp %= mod;
				tmp *= i - 1;
				tmp %= mod;
				f[i] = tmp;
			}
			cout <<f[n]<<endl;
		}
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
