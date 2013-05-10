//#define Debug
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cmath>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 3005;

	struct Point {
		int x, y; double angle;
		inline Point operator -(const Point& oth) const {
			Point ret;
			ret.x = x - oth.x;
			ret.y = y - oth.y;
			return ret;
		}
		inline int operator *(const Point& oth) const {
			return x * oth.y - oth.x * y;
		}
	}a[MAXN];
	int n;Int64 Sx, Sy;
	
	void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y), Sx += a[i].x, Sy += a[i].y;
	}
	
	Point Base;
	
	inline bool cmp(const Point& a, const Point& b) {
		return a.angle > b.angle;
	}

	Point T[MAXN << 1];int cnt, last[MAXN];
	inline Int64 Work(int u) {
		Base = a[u]; cnt = 0;
		for (int i = 1; i <= n; i++) if (i != u) T[cnt] = a[i] - Base, T[cnt].angle = atan2(T[cnt].y, T[cnt].x), cnt++;
		std::sort(T, T + cnt, cmp);
		for (int i = 0; i < cnt; i++) {
			T[i + cnt] = T[i];
			if (i != 0 && T[i].angle == T[i - 1].angle) last[i] = last[i - 1];
			else last[i] = i;
		}
		Int64 X = (Int64)(Sx - (Int64)n * Base.x), Y = (Int64)(Sy - (Int64)n * Base.y),
		      Tx = T[0].x, Ty = T[0].y, p = 0;
		Int64 Sum = 0;
		for (int i = 0; i < cnt; i++) {
			if (p < i) {p = i; Tx += T[i].x, Ty += T[i].y;}
			while (p + 1 < (last[i] + cnt) && T[i] * T[p + 1] <= 0)
				p++, Tx += T[p].x, Ty += T[p].y;
			Sum -= T[i].x * Ty - T[i].y * Tx;
			Sum += T[i].x * (Y - Ty) - T[i].y * (X - Tx);
			Tx -= T[i].x, Ty -= T[i].y;
		}
		return Sum;
	}

	Int64 Ans;
	void solve(void) {
		Input();
		for (int i = 1; i <= n; i++)
			Ans += Work(i);
		printf(LL, Ans / 12);
		if (Ans & 3) puts(".5"); else puts(".0");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
