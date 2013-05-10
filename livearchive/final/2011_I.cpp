#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
namespace Solve {
	const int MAXN = 200020;

	struct Point {
		int x, y;
	}a[MAXN];
	struct Rect {
		int x1, y1, x2, y2;
	}b[MAXN];
	int n;

	inline bool Cal(int pos, int x1, int y1, int x2, int y2) {
		if (x1 > x2 || y1 > y2) return false;
		if (pos > n) return true;
		if (b[pos].x1 > x2 || b[pos].x2 < x1 || b[pos].y1 > y2 || b[pos].y2 < y1) {
			return Cal(pos + 1, x1, y1, x2, y2);
		}
		bool r1 = false, r2 = false, r3 = false, r4 = false;
		if (b[pos].x1 > x1) {
			r1 = Cal(pos + 1, x1, y1, b[pos].x1 - 1, y2); 
			if (r1) return r1; 
			x1 = b[pos].x1;
		}
		if (b[pos].x2 < x2) {
			r2 = Cal(pos + 1, b[pos].x2 + 1, y1, x2, y2);
			if (r2) return r2;
			x2 = b[pos].x2;
		}
		if (b[pos].y1 > y1) {
			r3 = Cal(pos + 1, x1, y1, x2, b[pos].y1 - 1);
			if (r3) return r3;
			y1 = b[pos].y1;
		}
		if (b[pos].y2 < y2) {
			r4 = Cal(pos + 1, x1, b[pos].y2 + 1, x2, y2);
			if (r4) return r4;
			y2 = b[pos].y2;
		}
		return false;
	}

	inline bool Check(int t) {
		return Cal(1, -t, -t, t, t);
	}

	void solve(void) {
		int Tcase = 0;
		while (scanf("%d", &n), n != -1) { printf("Case %d: ", ++Tcase);
			for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
			int l = 1, r = 1000000000;
			while (l <= r) {
				int t = (l + r) >> 1;
				for (int i = 1; i <= n; i++) b[i].x1 = a[i].x - t, b[i].x2 = a[i].x + t, b[i].y1 = a[i].y - t, b[i].y2 = a[i].y + t;
				if (Check(t))
					l = t + 1;
				else
					r = t - 1;
			}
			if (l > 1000000000) puts("never"); else printf("%d\n", l);
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}

