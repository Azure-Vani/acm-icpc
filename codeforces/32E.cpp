#include <cstdio>
#include <algorithm>

using namespace std;

struct point {
	double x, y;
}l1, r1, l2, r2;

inline point operator - (point x, point y) {
	point z; z.x = x.x - y.x, z.y = x.y - y.y;
	return z;
}
inline int operator == (point x, point y) {
	return x.x == y.x && x.y == y.y;
}
inline long double operator ^ (point x, point y) {
	return (long double) x.x * y.y - (long double) x.y * y.x;
}
inline int test(point x, point l, point r) {
	if (l.x > r.x || l.x == r.x && l.y > r.y) {
		point t; t = l, l = r, r = t;
	}
	if (l.x == r.x) {
		double t = l.x; l.x = l.y, l.y = t;
		t = r.x, r.x = r.y, r.y = t;
		t = x.x, x.x = x.y, x.y = t;
	}
	if (x.x < l.x) return -2;
	else if (x.x == l.x) return -1;
	else if (x.x == r.x) return 1;
	else if (x.x > r.x) return 2;
	else return 0;
} 
int test_intersection(point l1, point r1, point l2, point r2) {
	if (l1 == r1 && l2 == r2)
		if (l1 == l2) return 1; else return 0;
	else if (l1 == r1) {
		if ((l1 - l2) ^ (r2 - l2)) return 0;
		int f = test(l1, l2, r2);
		if (f == -2 || f == 2) return 0;
		else return 1;
	} else if (l2 == r2) {
		if ((l2 - l1) ^ (r1 - l1)) return 0;
		int f = test(l2, l1, r1);
		if (f == -2 || f == 2) return 0;
		else return 1;
	}
	point k1 = r1 - l1, k2 = r2 - l2;
	long double x = k1 ^ k2, y = (l2 - l1) ^ k1;
	if (!x && !y) {
		int f1 = test(l2, l1, r1), f2 = test(r2, l1, r1);
		if (f1 < 0 && f2 > 0 || f1 > 0 && f2 < 0 || !f1 || !f2) return 2;
		else if (f1 == -2 && f2 == -2 || f1 == 2 && f2 == 2) return 0;
		else if (f1 == -1 || f1 == 1) return 1;
		else return 1;
	} else if (!x) return 0;
	if (x < 0 && (y < x || y > 0)) return 0;
	if (x > 0 && (y < 0 || y > x)) return 0;
	y = (l2 - l1) ^ k2;
	if (x < 0 && (y < x || y > 0)) return 0;
	if (x > 0 && (y < 0 || y > x)) return 0;
	return 1;
}

inline point f(point now, point a, point b) {
	double A = b.y - a.y, B = a.x - b.x, C = a.y * (b.x - a.x) - a.x * (b.y - a.y);
	point ret; double D = (double) (A * now.x + B * now.y + C) / (A * A + B * B);
	ret.x = now.x - 2ll * A * D;
	ret.y = now.y - 2ll * B * D;
	return ret;
}

point a, b, w1, w2, m1, m2;

int main(void) {
	freopen("in", "r", stdin);
	scanf("%lf%lf%lf%lf", &a.x, &a.y, &b.x, &b.y);
	scanf("%lf%lf%lf%lf", &w1.x, &w1.y, &w2.x, &w2.y);
	scanf("%lf%lf%lf%lf", &m1.x, &m1.y, &m2.x, &m2.y);
	if (test_intersection(a, b, w1, w2) == 0 && test_intersection(a, b, m1, m2) == 0) {
		puts("YES");
	} else {
		point tmp = f(a, m1, m2), tmp2 = f(b, m1, m2);
		if (test_intersection(tmp, b, m1, m2) > 0 && test_intersection(tmp, b, w1, w2) == 0 && test_intersection(tmp2, a, m1, m2) > 0 && test_intersection(tmp2, a, w1, w2) == 0) {
			puts("YES");
		} else puts("NO");
	}
	return 0;
}

