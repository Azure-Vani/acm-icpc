#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <cstring>

using namespace std;
namespace Solve {
	const int MAXN = 100010;
	const int eps = 1e-5;

	inline int ScanInt(void) {
		int r = 0, d, c;
		while (d = getchar(), !isdigit(d) && d != '-') ;
		if (d != '-') r = d - 48;
		while (c = getchar(), isdigit(c)) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Point {
		double x, y;
	}a[MAXN], b[MAXN];
	inline double Distans(const Point &a, const Point &b) {
		return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	inline pair<Point, double> getCircle(const Point& a, const Point& b, const Point& c) {
		register double a1 = 2 * (b.x - a.x), b1 = 2 * (b.y - a.y), c1 = (b.x*b.x - a.x*a.x) + (b.y*b.y - a.y*a.y),
					a2 = 2 * (c.x - a.x), b2 = 2 * (c.y - a.y), c2 = (c.x*c.x - a.x*a.x) + (c.y*c.y - a.y*a.y), det = a1*b2-a2*b1;
		register Point ret; ret.x = (c1*b2-c2*b1)/det, ret.y = (a1*c2-a2*c1)/det;
		return make_pair(ret, Distans(ret, a));
	}

	int n, m;

	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) a[i].x = ScanInt(), a[i].y = ScanInt();
	}

	inline pair<Point,double> Circle(Point *a, int n) {
		memcpy(b, a + 1, sizeof (a[0]) * n);
		for (int i = 1; i <= n; i++) swap(a[i], a[rand() % n + 1]);
		Point ret = a[1]; double r = 0;
		for (int i = 2; i <= n; i++) if (Distans(ret, a[i]) > r + eps) {
			ret = a[i], r = 0;
			for (int j = 1; j < i; j++) if (Distans(ret, a[j]) > r + eps) {
				ret.x = (a[i].x + a[j].x) * 0.5, ret.y = (a[i].y + a[j].y) * 0.5;
				r = Distans(a[i], a[j]) * 0.5;
				for (int k = 1; k < j; k++) if (Distans(ret, a[k]) > r + eps) {
					pair<Point, double> tmp = getCircle(a[i], a[j], a[k]);
					ret = tmp.first, r = tmp.second;
				}
			}
		}
		memcpy(a + 1, b, sizeof (b[0]) * n);
		return make_pair(ret, r);
	}

	Point stack[MAXN]; int top = 0;

	inline void Work(void) {
		double l = 0, r = 1500000;
		while (r - l > 1e-7) {
			double mid = (l + r) * 0.5; int cnt = 0, ok = true;
			for (int i = 1; i <= n;) {
				int k = 1;
				for (;;k++) {
					pair<Point, double> tmp = Circle(a + i - 1, min(1 << k, n - i + 1));
					if (tmp.second - mid > eps) break;
					if (i + (1 << k) - 1 > n) break;
				}
				int L = i + (1 << (k - 1)) - 1, R = min(i + (1 << k) - 1, n);
				while (L <= R) {
					int M = (L + R) >> 1; 
					pair<Point, double> tmp = Circle(a + i - 1, M - i + 1);
					if (tmp.second - mid > eps)
						R = M - 1;
					else
						L = M + 1;
				}
				i = R + 1;
				if (++cnt > m) {ok = false; break;}
			}
			if (ok) r = mid; else l = mid;
		}
		double mid = r;
		printf("%.15lf\n", mid);
		for (int i = 1; i <= n; ) {
			int k = 1;
			for (;;k++) {
				pair<Point, double> tmp = Circle(a + i - 1, min(1 << k, n - i + 1));
				if (tmp.second - mid > eps) break;
				if (i + (1 << k) - 1 > n) break;
			}
			int L = i + (1 << (k - 1)) - 1, R = min(i + (1 << k) - 1, n); Point ret;
			while (L <= R) {
				int M = (L + R) >> 1;
				pair<Point, double> tmp = Circle(a + i - 1, M - i + 1);
				if (tmp.second - mid > eps)
					R = M - 1;
				else
					L = M + 1, ret = tmp.first;
			}
			i = R + 1;
			stack[++top] = ret;
		}
		printf("%d\n", top);
		for (int i = 1; i <= top; i++) printf("%.15lf %.15lf\n", stack[i].x, stack[i].y);
	}

	inline void solve(void) {
		Input();
		Work();
	}
}

int main(void) {
//	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}

