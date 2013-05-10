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
	typedef long long Int64;

	const int MAXN = 500050;
	const Int64 base1 = 13331;
	const Int64 base2 = 10701;
	const Int64 mod1 = 1000000007;
	const Int64 mod2 = 1010307711;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	Int64 pow1[MAXN], pow2[MAXN], sum1[MAXN], sum2[MAXN];
	int n;

	inline void Input(void) {
		n = ScanInt();
		pow1[0] = pow2[0] = 1;
		for (int i = 1; i <= n; i++) {
			int t; while (!islower(t = getchar()));
			pow1[i] = pow1[i - 1] * base1 % mod1;
			pow2[i] = pow2[i - 1] * base2 % mod2;
			sum1[i] = (sum1[i - 1] * base1 + t) % mod1;
			sum2[i] = (sum2[i - 1] * base2 + t) % mod2;
		}
	}

	inline pair<Int64, Int64> Get(int l, int r) {
		Int64 r1 = (sum1[r] - sum1[l - 1] * pow1[r - l + 1] % mod1) % mod1; if (r1 < 0) r1 += mod1;
		Int64 r2 = (sum2[r] - sum2[l - 1] * pow2[r - l + 1] % mod2) % mod2; if (r2 < 0) r2 += mod2;
		return mp(r1, r2);
	}

	inline bool Equal(int l1, int r1, int l2, int r2) {
		return Get(l1, r1) == Get(l2, r2);
	}

	bool tag[MAXN]; int list[MAXN], fac[MAXN], cnt = 0;
	inline void Genprime(void) {
		for (int i = 2; i <= n; i++) {
			if (!tag[i]) list[++cnt] = i, fac[i] = i;;
			for (int j = 1; j <= cnt && list[j] * i <= n; j++) {
				tag[list[j] * i] = true;
				fac[list[j] * i] = list[j];
				if (i % list[j] == 0) break;
			}
		}
	}

	inline void Work(void) {
		int m = ScanInt();
		while (m--) {
			register int l = ScanInt(), r = ScanInt();
			register int h = r - l + 1, tmp = h;
			while (tmp != 1) {
				register int f = fac[tmp], p = 1;
				while (fac[tmp] == f) {
					tmp /= f;
					register int next_p = p * f;
					if (Equal(l, r - h / next_p, l + h / next_p, r)) p = next_p;
				}
				h /= p;
			}
			printf("%d\n", h);
		}
	}

	inline void solve(void) {
		Input();
		Genprime();
		Work();
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
