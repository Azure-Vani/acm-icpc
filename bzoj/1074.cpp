//#define Debug
#include <cstdio>
#include <cmath>
namespace Solve {
	const long MAXN = 8;
	struct T {double x, y; T(){};T(double x, double y):x(x), y(y){}};
	struct Line {T P1,P2;}a[MAXN];long n;
	inline void Input(void) {
		scanf("%ld", &n);
		for (long i = 0; i < n; i++)
			scanf("%lf %lf %lf %lf", &a[i].P1.x, &a[i].P1.y, &a[i].P2.x, &a[i].P2.y);
	}
	inline double S1(double x1, double y1, double x2, double y2) {return x1 * y2 - x2 * y1;}
	#define sqr(x) ((x)*(x))
	bool More(double a, double b) {return a >= b; }
	inline T Cross(T P, Line L) {
		double x1 = L.P1.x, x2 = L.P2.x, y1 = L.P1.y, y2 = L.P2.y;
		double A = y1 - y2, B = x2 - x1, C = x1 * y2 - x2 * y1; 
		double delta = (A * P.x + B * P.y + C) / (sqr(A) + sqr(B));
		return T(P.x - 2 * A * delta, P.y - 2 * B * delta);
	}
	bool Out(T P){return More(P.x, 100) ||More(P.y, 100) || More(0, P.x) || More(0, P.y);}
	long Gao(T now, long k) {
		if (k < 0) return 
			Out(now) ? 0 : 1;
		double flag = S1(now.x - a[k].P1.x, now.y - a[k].P1.y, a[k].P2.x - a[k].P1.x, a[k].P2.y - a[k].P1.y);
		return More(flag, 0) ? 0 : Gao(now, k - 1) + Gao(Cross(now, a[k]), k - 1);
	}
	void Work(void) {
		Input();
		long Q; scanf("%ld", &Q);
		for (long oo = 1; oo <= Q; oo++) {
			double x, y;
			scanf("%lf %lf", &x, &y);
			printf("%ld\n", Gao(T(x, y), n - 1));
		}
	}
}
int main(int argc, char** argv) {
	Solve::Work();
	return 0;
}
