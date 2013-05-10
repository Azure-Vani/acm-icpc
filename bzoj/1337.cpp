//#define Debug
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#define R(n) (rand() % (n) + 1)
namespace Solve {
	const int MAXN = 100005;
	const double eps = 1e-7;
	struct Point {
		double x, y;
	}a[MAXN];
	int n;
	double X, Y, R;

	void Input(void) {
		scanf("%d", &n);
		for (int _ = 1; _ <= n; _++) scanf("%lf %lf", &a[_].x, &a[_].y);
		for (int _ = 1; _ <= n; _++) std::swap(a[_], a[R(n)]);
	}

	#define pow(x) ((x)*(x))
	inline void Cal(const Point& a, const Point& b, const Point& c) {
		double u1 = (pow(b.x) - pow(a.x) + pow(b.y) - pow(a.y)) / 2,
		       u2 = (pow(c.x) - pow(a.x) + pow(c.y) - pow(a.y)) / 2,
		       d11 = b.x - a.x, d12 = b.y - a.y,
		       d21 = c.x - a.x, d22 = c.y - a.y;
		X = ((u1 * d22) - (u2 * d12)) / (d11 * d22 - d21 * d12);
		Y = ((u2 * d11) - (u1 * d21)) / (d11 * d22 - d21 * d12);
		R = sqrt(pow(X - a.x) + pow(Y - a.y));
	}
		
	void Work(void) {
		Input();
		X = a[1].x, Y = a[1].y, R = 0;
		for (int i = 2; i <= n; i++) {
			if (pow(a[i].x - X) + pow(a[i].y - Y) <= pow(R) + eps) continue;
			X = (a[i].x + a[1].x) / 2, Y = (a[i].y + a[1].y) / 2;
			R = sqrt(pow(X - a[i].x) + pow(Y - a[i].y));

			for (int j = 2; j < i; j++) {
				if (pow(a[j].x - X) + pow(a[j].y - Y) <= pow(R) + eps) continue;
				X = (a[i].x + a[j].x) / 2, Y = (a[i].y + a[j].y) / 2;
				R = sqrt(pow(X - a[i].x) + pow(Y - a[i].y));
				
				for (int k = 1; k < j; k++) {
					if (pow(a[k].x - X) + pow(a[k].y - Y) <= pow(R) + eps) continue;
					Cal(a[i], a[j], a[k]);
				}
			}
		}
		printf("%.3lf\n", R);
		//printf("%.10lf %.10lf\n", X, Y);
	}
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}
