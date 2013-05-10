//#define FILEIO

#define INPUT "angel.in"
#define OUTPUT "angel.out"

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
	const int inf = ~0U>>1;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	inline void Min(int &a, int b) {
		if (a > b) a = b;
	}
	inline void Max(int &a, int b) {
		if (a < b) a = b;
	}

	struct Query {
		int t, x, y, pos, ask_pos;
	}a[MAXN], b[MAXN], c[MAXN];;

	int n, m, nAsk, Ans[MAXN], Len;

	inline void Input(void) {
		m = ScanInt(), n = ScanInt();
		int k = 0;
		for (int i = 1; i <= m; i++) {
			k++;
			a[k].t = 1, a[k].x = ScanInt(), a[k].y = ScanInt();
			a[k].pos = i;
			Max(Len, a[k].x); Max(Len, a[k].y);
		}
		for (int i = k + 1; i <= k + n; i++) {
			a[i].t = ScanInt(), a[i].x = ScanInt(), a[i].y = ScanInt();
			a[i].pos = i;
			if (a[i].t == 2) a[i].ask_pos = ++nAsk;
			Max(Len, a[i].x); Max(Len, a[i].y);
		}
		Len++;
		n += k;
		for (int i = 1; i <= n; i++) c[i] = a[i];
	}

	int C[MAXN];

	inline void Ins(int u, int x) {
		for (;u <= Len; u += u & -u) Max(C[u], x);
	}
	inline int Cal(int u) {
		int ret = -inf;
		for (;u; u -= u & -u) Max(ret, C[u]);
		return ret;
	}

	void Work(int l, int r) {
		if (l >= r) return;
		int mid = (l + r) >> 1;
		Work(l, mid);
		Work(mid + 1, r);
		register Query tmp;
		int lv = l, rv = mid + 1;
		for (int i = l; i <= r; i++) {
			if (lv <= mid && (rv > r || a[rv].x >= a[lv].x)) tmp = a[lv++]; else tmp = a[rv++];
			if (tmp.pos <= mid) {
				if (tmp.t == 1) Ins(tmp.y, tmp.x + tmp.y);
			} else {
				if (tmp.t == 2) Min(Ans[tmp.ask_pos], tmp.x + tmp.y - Cal(tmp.y));
			}
			b[i] = tmp;
		}
		for (int i = l; i <= r; i++) a[i] = b[i];
		for (int i = l; i <= r; i++) if (a[i].pos <= mid && a[i].t == 1) {
			for (int j = a[i].y; j <= Len && C[j] != C[0]; j += j&-j) C[j] = C[0];
		}
	}

	inline void solve(void) {
		Input();
		memset(C, -60, sizeof C); memset(Ans, 60, sizeof Ans);
		Work(1, n);
		for (int i = 1; i <= n; i++) c[i].x = Len - c[i].x, a[i] = c[i];
		memset(C, -60, sizeof C);
		Work(1, n);
		for (int i = 1; i <= n; i++) c[i].y = Len - c[i].y, a[i] = c[i];
		memset(C, -60, sizeof C);
		Work(1, n);
		for (int i = 1; i <= n; i++) c[i].x = Len - c[i].x, a[i] = c[i];
		memset(C, -60, sizeof C);
		Work(1, n);
		for (int i = 1; i <= nAsk; i++) printf("%d\n", Ans[i]);
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
