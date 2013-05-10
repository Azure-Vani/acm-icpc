//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <set>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 1010;
	const int MAXM = 100033;
	const int base = 32;
	const int MAXQ = MAXM / base + 1;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct obj {
		int a, b, c, id;
	}a[MAXN], c[MAXM];
	struct query {
		int m, k, s, id;
	}q[MAXM * 10];
	inline bool cmp1(const obj& a, const obj& b) {
		return a.a < b.a;
	}
	inline bool cmp2(const query& a, const query& b) {
		return a.m < b.m;
	}
	inline bool cmp3(const obj& a, const obj& b) {
		return a.b > b.b;
	}

	int n, m, fim[MAXN]; long long sum[MAXN];

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) a[i].id = i, a[i].c = ScanInt(), a[i].a = ScanInt(), a[i].b = ScanInt(), c[i] = a[i];
		m = ScanInt();
		for (int i = 1; i <= m; i++) q[i].m = ScanInt(), q[i].k = ScanInt(), q[i].s = ScanInt(), q[i].id = i;
		sort(c + 1, c + n + 1, cmp3);
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + c[i].c;
		sort(a + 1, a + n + 1, cmp1);
		sort(q + 1, q + m + 1, cmp2);
		for (int i = 1; i <= n; i++) fim[c[i].id] = i;
	}

	bool Ans[MAXM * 10], used[MAXN];
	unsigned int f[MAXN][MAXQ + 2];int len[MAXN];
	set<pair<int, int> > S;

	inline void Work(void) {
		int v = 1; used[0] = true;
		for (int i = 0; i <= n; i++) f[i][0] = 1;
		for (int i = 1; i <= m; i++) {
			while (v <= n && a[v].a <= q[i].m) {
				register int d = a[v].c / base, mod = a[v].c & (base - 1);
				register int now = fim[a[v].id];
				used[now] = true;
				for (; now <= n; ++now) {
					for (register int k = min(MAXQ, len[now] + d + 1); k >= d; k--) if (f[now][k] != ~0U) {
						f[now][k] |= f[now][k - d] << mod;
						if (k - d && mod) f[now][k] |= f[now][k - d - 1] >> (base - mod);
						if (f[now][k] && k > len[now]) len[now] = k;
					}
				}
				S.insert(mp(a[v].b, -fim[a[v].id]));
				v++;
			}
			set<pair<int, int> >::iterator it = S.upper_bound(mp(q[i].m + q[i].s, ~0U>>1));
			int tmp = -it->second;
			if (f[tmp][q[i].k / base] & (1 << (q[i].k & (base - 1)))) Ans[q[i].id] = true;
		}
		for (int i = 1; i <= m; i++) if (Ans[i]) puts("TAK"); else puts("NIE");
	}

	inline void solve(void) {
		Input();
		Work();
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
