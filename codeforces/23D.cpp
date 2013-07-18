#include <cstdio>
#include <cassert>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

const double eps = 1e-6;

int Ro[][3] = {{0,1,2},{1,0,2},{2,1,0},{1,2,0},{0,2,1},{2,0,1}};

template<class T> inline int sign(T x) { if (x < -eps) return -1; else if (x > eps) return 1; else return 0;}
struct Point {
    double x, y;
    Point():x(0),y(0){}
    Point(double x, double y):x(x), y(y){}
    inline Point operator +(const Point& oth) const {
        return Point(x + oth.x, y + oth.y);
    }
    inline Point operator -(const Point& oth) const {
        return Point(x - oth.x, y - oth.y);
    }
	inline Point operator *(const double k) const {
		return Point(x * k, y * k);
	}
	inline Point operator /(const double k) const {
		return Point(x / k, y / k);
	}
	inline double len(void) {
		return sqrt(x*x + y*y);
	}
	inline Point Resize(void) const {
		Point ret = *this;
		return ret / ret.len();
	}
    inline double operator ^(const Point& oth) const {
        return (double) x * oth.y - (double) oth.x * y;
    }
	inline double rotate(const Point& a, const Point& b) const {
		return sign((a - *this) ^ (b - *this));
	}
};

struct Line {
	double A, B, C;
	Line():A(0), B(0), C(0){}
	Line(double A, double B, double C):A(A), B(B), C(C){}
};

inline Point Intersect(const Line& x, const Line& y) {
	double Y = ((x.A * y.C) - (y.A * x.C)) / ((y.A * x.B) - (x.A * y.B));
	double X = - (x.B * Y + x.C) / x.A;
	return Point(X, Y);
}

inline Line getMid(Point a, Point b) {
	double A = b.x - a.x, B = b.y - a.y, C = - ((a.x + b.x) * (b.x - a.x) - (a.y + b.y) * (a.y - b.y)) / 2.0;
	return Line(A, B, C);
}

vector<Point> Ans;

inline bool Cal(void) {
	if (Ans[0].rotate(Ans[3], Ans[2]) * Ans[0].rotate(Ans[1], Ans[2]) >= -eps) return false;
	if (Ans[1].rotate(Ans[2], Ans[3]) * Ans[1].rotate(Ans[0], Ans[3]) >= -eps) return false;
	return true;
}

inline bool Check(Point a, Point b, Point c) {
	Line L1 = getMid(a, b);
	Line L2 = getMid(a, c);
	Point p0 = Intersect(L1, L2);
	Point t0 = a - p0, t1 = ((a + b) / 2 - p0).Resize(), t2 = ((a + c) / 2 - p0).Resize();
	double A = t1 ^ t2, B = t0 ^ t1, C = t2 ^ t0, alpha = t1 ^ t0, beta = t0 ^ t2;
	double k = alpha / beta;
	double ret = (B + C * k) / (-A * k);
	Point v = t1 * ret + p0; Ans.clear();
	Ans.push_back(b * 2 - v); Ans.push_back(v); Ans.push_back((a * 2) - v); Ans.push_back((c * 2) - Ans[2]);
	return Cal();
}

int main(void) {
	freopen("in", "r", stdin);
	int kase; scanf("%d", &kase); for (int _ = 1; _ <= kase; _++) {
		Point a[3]; for (int i = 0; i < 3; i++) scanf("%lf%lf", &a[i].x, &a[i].y);
		if (a[0].rotate(a[1], a[2]) == 0) {
			puts("NO\n");
		} else {
			bool ok = false;
			for (int i = 0; i < 6; i++) {
				if (Check(a[Ro[i][0]], a[Ro[i][1]], a[Ro[i][2]])) {
					ok = true;
					break;
				}
			}
			if (ok) {
				puts("YES");
				for (int i = 0; i < 4; i++) printf("%.9lf %.9lf ", Ans[i].x, Ans[i].y);
				puts("");
			} else puts("NO\n");
		}
	}
	return 0;
}

