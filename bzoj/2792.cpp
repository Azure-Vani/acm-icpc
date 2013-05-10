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
	const int MAXN = 1000010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	Int64 a[MAXN], c[MAXN], m, M = 0;
	int n;

	inline void Input(void) {
		n = ScanInt(); scanf("%lld", &m);
		for (int i = 1; i <= n; i++) a[i] = c[i] = ScanInt(), M = max(M, c[i]);
	}

	Int64 L[MAXN], R[MAXN];
	Int64 sum[MAXN];

	inline void Sweep(Int64 k, Int64 *a, Int64 *ret) {
		int v = 1;
		for (int i = 1; i <= n; i++) {
			while (v < i && a[v] < (i - v) * k) v++;
			ret[i] = v;
		}
	}

	inline Int64 Cal(Int64 k) {
		Int64 ret = 0;
		for (int i = 1; i <= n; i++) a[i] = c[i];
		for (int i = 2; i <= n; i++) if (a[i] - a[i - 1] > k) a[i] = a[i - 1] + k;
		for (int i = n - 1; i >= 1; i--) if (a[i] - a[i + 1] > k) a[i] = a[i + 1] + k;
		for (int i = 1; i <= n; i++) ret += c[i] - a[i], sum[i] = sum[i - 1] + a[i];
		Sweep(k, a, L);
		reverse(a + 1, a + n + 1);
		Sweep(k, a, R);
		reverse(R + 1, R + n + 1);
		reverse(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) R[i] = n - R[i] + 1;
		for (int i = 1; i <= n; i++) {
			Int64 l = i - L[i], r = R[i] - i;
			Int64 lsum = sum[i - 1] - sum[L[i] - 1] - (1 + l) * l * k / 2;
			Int64 rsum = sum[R[i]] - sum[i] - (1 + r) * r * k / 2;
			if (a[i] + lsum + rsum + ret <= m) return i;
		}
		return -1;
	}

	inline void Work(void) {
		Int64 l = 0, r = M;
		Int64 pos = 0;
		while (l <= r) {
			Int64 mid = (l + r) >> 1;
			Int64 tmp = Cal(mid);
			if (tmp != -1) {
				pos = tmp;
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		}
		printf("%lld %lld\n", pos, l);
	}

	inline void solve(void) {
		Input();
		Work();
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