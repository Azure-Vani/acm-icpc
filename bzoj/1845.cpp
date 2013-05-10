#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
namespace Solve{
	const long MAXN = 120;
	const double exp = 1e-11;
	const double inf = 1e10;

	struct A{
		double x1,x2,x3,y1,y2,y3;
	}a[MAXN];
	struct P{
		double x,y;
	}b[MAXN];
	long n;

	double CC(double x,double x1,double y1,double x2,double y2) {
		if ( fabs( x1 - x2 ) < exp ) return inf;
		if ( x1 > x2 ) std::swap( x1 , x2) , std::swap ( y1, y2 );
		if ( x1 > x || x2 < x) return inf;

		double k = (y1 - y2) / (x1 - x2), b = y1 - k * x1;
		return k * x + b;
	}

	P GetPoint(A u, double x) {
		double l = inf, r = -inf;

		double t = CC(x, u.x1, u.y1, u.x2, u.y2);
		if (t != inf) l = std::min(l, t), r = std::max(r, t);
		t = CC(x, u.x2, u.y2, u.x3, u.y3);
		if (t != inf) l = std::min(l, t), r = std::max(r, t);
		t = CC(x, u.x3, u.y3, u.x1, u.y1);
		if (t != inf) l = std::min(l, t), r = std::max(r, t);
		
		P R;
		if (l > r) R.x = R.y = 0; else R.x = l, R.y = r;
		return R;
	}
	
	inline bool cmp(P a, P b) {return a.x < b.x;}
	double Work(double t) {
		for (long i = 1; i <= n; i++)
			b[i] = GetPoint(a[i], t);

		std::sort(b + 1, b + n + 1, cmp);
		double T = 0, now = -inf;
		for (long i = 1; i <= n; i++)
			if (b[i].x >= now)
				T += (b[i].y - b[i].x), now = b[i].y;
			else 
			if (b[i].y >= now)
				T += (b[i].y - now), now = b[i].y;
		return T;
	}

	double F(double l,double r,double mid,double ll,double lr,double lmid,double res) {
		double m1 = (l + mid) / 2, m2 = (mid + r) / 2, r1 = Work(m1), r2 = Work(m2), g1 = (ll + lmid + r1 * 4) * (mid - l), g2 = (lmid + lr + r2 * 4) * (r - mid);
		if ( std::fabs(g1 + g2 - res) < exp ) 
			return g1 + g2;
		else 
			return F(l, mid, m1, ll, lmid, r1, g1) + F(mid, r, m2, lmid, lr, r2, g2);
	}
	
	const double sin30 = std::sin(M_PI/12);
	const double cos30 = std::cos(M_PI/12);

	inline void Trans(double &x,double &y) {	// This function is to circle those point, such as sgu120.
		double a = x, b = y;
		a = x * cos30 + y * sin30;		// In fact, I don't know that why I have to do so.
		b = -x * sin30 + y * cos30;		// But University Gu have done it.
		x = a, y = b;				// So I think it is correct to do it.
	}

	std::vector <double> Q;
	void Input(void) {
		 scanf("%ld", &n);
		for (long i = 1; i <= n; i++){
			scanf("%lf %lf %lf %lf %lf %lf", &a[i].x1, &a[i].y1, &a[i].x2, &a[i].y2, &a[i].x3, &a[i].y3);
			Trans(a[i].x1, a[i].y1);
			Trans(a[i].x2, a[i].y2);
			Trans(a[i].x3, a[i].y3);
		}

		for (long i = 1; i <= n; i++) Q.push_back(a[i].x1), Q.push_back(a[i].x2), Q.push_back(a[i].x3);
		std::sort( Q.begin(), Q.end() );
		
		double S = 0;
		for (long i = 1; i < Q.size(); i++) {
			double l = Q[i - 1], r = Q[i]; double mid = (l + r) / 2.0;
			double lres = Work(l), rres = Work(r), mres = Work(mid);
			S += F(l, r, mid, lres, rres, mres, lres + rres + 4 * mres);
		}
		printf("%.2lf\n",S/6);
	}
}
int main(int argc, char **argv) {
	#ifdef Debug
		freopen("1.in","r",stdin);
	#endif
	Solve::Input();
	return 0;
}
