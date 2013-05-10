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
#include <queue>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	typedef long long Int64;

	const Int64 MAXN = 100010;

	inline Int64 ScanInt(void) {
		Int64 r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10l + c - '0';
		return d=='-'?-r:r;
	}

	inline Int64 Exgcd(Int64 a, Int64 b, Int64 &x, Int64 &y) {
		if (!b) {
			x = 1, y = 0;
			return a;
		}
		Int64 r = Exgcd(b , a % b, x, y);
		Int64 t = x; x = y , y = t - a / b * y;
		return r;
	}

	Int64 c[MAXN], n, a, b, p[MAXN];

	inline void Input(void) {
		n = ScanInt(), a = ScanInt(), b = ScanInt();
		for (Int64 i = 1; i <= n; i++) p[i] = ScanInt();
		n++;
		for (Int64 i = 1; i <= n; i++) c[i] = p[i] - p[i - 1];
	}

	inline void Min(Int64 &x, Int64 &y) {
		Int64 x1 = x, y1 = y, x2 = x, y2 = y;
		Int64 tmp1 = x / b; x1 = x - tmp1 * b, y1 = y + tmp1 * a;
		Int64 tmp2 = y / a; x2 = x + tmp2 * b, y2 = y - tmp2 * a;
		if (abs(x1) + abs(y1) < abs(x2) + abs(y2))
			x = x1, y = y1;
		else
			x = x2, y = y2;
		if (x1 > 0) x1 -= b, y1 += a; else x1 += b, y1 -= a;
		if (y2 > 0) x2 += b, y2 -= a; else x2 -= b, y2 += a;
		if (abs(x1) + abs(y1) < abs(x2) + abs(y2))
			x2 = x1, y2 = y1;
		if (abs(x2) + abs(y2) < abs(x) + abs(y)) x = x1, y = y1;
	}

	priority_queue<pair<Int64, Int64> > Q;

	Int64 X[MAXN], Y[MAXN];

	inline void Insert(Int64 i) {
		Q.push(mp(abs(X[i]) + abs(Y[i]) - abs(X[i] - b) - abs(Y[i] + a), i));
	}

	inline void Work(void) {
		Int64 t_x = 0, t_y = 0;
		Int64 d = Exgcd(a, b, t_x, t_y); a /= d, b /= d;
		for (Int64 i = 1; i <= n; i++) {
			if (c[i] % d != 0) {puts("-1"); return;}
			c[i] /= d;
		}
		Int64 Sx = 0, Sy = 0;
		for (Int64 i = 1; i <= n; i++) {
			X[i] = t_x * -c[i], Y[i] = t_y * -c[i];
			Min(X[i], Y[i]);
			Sx += X[i], Sy += Y[i];
		}
		if (Sx <= 0) {
			swap(a, b); swap(Sx, Sy);
			for (Int64 i = 1; i <= n; i++) swap(X[i], Y[i]);
		}
		for (Int64 i = 1; i <= n; i++) {
			Insert(i);
		}
		while (Sx != 0) {
			Int64 now = Q.top().second; Q.pop();
			Sx -= b, Sy += a;
			X[now] -= b, Y[now] += a;
			Insert(now);
		}
		Int64 ret = 0;
		for (Int64 i = 1; i <= n; i++) ret += abs(X[i]) + abs(Y[i]);
		printf(LL "\n", ret >> 1);
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