//#define FILEIO

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>

#define rep(i,l,r) for(int i = (l); i <= (r); i++)
#define In(a, b, c) (((a) >= (b)) && ((a) <= (c)))

namespace Solve {
	typedef long long Int64;
	const int MAXN = 6000005;
	const int MAXM = 20;

	int n, m, len;
	int a[MAXM], DList[MAXN], next[MAXM];
	Int64 pow[MAXM];

	inline int Digit(int n, int *p) {
		int len = 0, *backup = p;
		do {
			len++;
			*(p++) = n % 10;
			n /= 10;
		}while (n);
		std::reverse(backup, p);
		return len;
	}

	inline Int64 Count_Less(void) {
		int ret = 0;
//		memset(DList, 0, sizeof DList);
		memset(next, 0, sizeof next);
		int *P = DList + 1, N = 0;
		for (int i = 1; i < std::min(pow[n], pow[len - 1]); i++) {
			int tmp = Digit(i, P);
			P += tmp;
			N += tmp;
		}
		int last = 0;
		for (int i = 2; i <= len; i++) {
			while (last && a[last + 1] != a[i])
				last = next[last];
			if (a[last + 1] == a[i]) last++;
			next[i] = last;
		}
		last = 0;
		for (int i = 1; i <= N; i++) {
			while (last && DList[i] != a[last + 1])
				last = next[last];
			if (DList[i] == a[last + 1]) last++;
			if (last == len) {
				ret++;
				last = next[last];
			}
		}
		return (Int64)ret;
	}

	inline Int64 Count_Biger(void) {
		Int64 ret = 0;
		for (int i = 0; i <= n - len; i++) {
			ret += pow[i] * pow[n - i - len];
		}
		for (int i = len; i <= n; i++) {
			for (int j = 1; j <= len - 1; j++) if (m / pow[j - 1] % 10)
				ret += pow[i - len];
		}
		return ret;
	}

	void solve(void) {
		pow[0] = 1;
		for (int i = 1; i <= 17; i++) 
			pow[i] = pow[i - 1] * 10;
		while (scanf("%d%d", &n, &m), n != 0 && m != 0) {
			len = Digit(m, a + 1);
			Int64 Ans = Count_Less();
			Ans += Count_Biger();
			printf(LL "\n", Ans);
		}
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
