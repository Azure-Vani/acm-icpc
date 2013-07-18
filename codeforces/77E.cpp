#include <cstdio>
#include <cmath>

using namespace std;

struct Point {
	double x, y;
	Point(double x = 0, double y = 0):x(x), y(y){}
    inline Point operator +(const Point& oth) const {
        return Point(x + oth.x, y + oth.y);
    }
    inline Point operator -(const Point& oth) const {
        return Point(x - oth.x, y - oth.y);
    }
	inline Point operator *(const double k) const {
		return Point(x * k, y * k);
	}
	inline double len(void) {
		return sqrt(x*x + y*y);
	}
	inline Point reflect(const Point& mid, double len) {
		Point tmp = *this - mid;
		double k = len * len / (tmp.len() * tmp.len());
		return tmp * k + mid;
	}
	inline void print(void) {
		printf("%lf %lf\n", x, y);
	}
}mid;

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

double R, r, Len; int k;

int main(void) {
	freopen("in", "r", stdin);
	int kase; scanf("%d", &kase); for (int _ = 1; _ <= kase; _++) {
		scanf("%lf%lf%d", &R, &r, &k);
		mid = Point(-R, 0); Len = r;
		Point left = Point(2 * r - R, 0), right = Point(R, 0);
		Point _left = left.reflect(mid, Len), _right = right.reflect(mid, Len);
		Point m = (_left + _right) * 0.5;
		double cir = m.x - _left.x;
		Point new_left = Point(_left.x, left.y + k * 2 * cir);
		Point new_right = Point(_right.x, right.y + k * 2 * cir);
		Point new_top = Point(m.x, m.y + k * 2 * cir - cir);
		Point _new_left = new_left.reflect(mid, Len);
		Point _new_right = new_right.reflect(mid, Len);
		Point _new_top = new_top.reflect(mid, Len);
		Line L1 = getMid(_new_left, _new_right);
		Line L2 = getMid(_new_right, _new_top);
		Point t = Intersect(L1, L2);
		double Ans = (t - _new_top).len();
		printf("%.9lf\n", Ans);
	}
	return 0;
}

