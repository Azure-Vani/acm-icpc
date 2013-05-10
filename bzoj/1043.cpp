#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>

namespace Solve{
	const long MAXN = 1020;
	const double eps = 1e-10;

	struct Cir{
		double r,x,y;
	}a[MAXN];
	
	#define sqr(x) ((x)*(x))
	#define Dis(x, y, x1, y1) (sqrt(sqr(x - x1) + sqr(y - y1)))
	long n; bool live[MAXN] = {0}; double D[MAXN][MAXN] = {0};

	void Input(void) {
		scanf("%ld", &n);
		for (long i = 1; i <= n; i++) {
			scanf("%lf %lf %lf", &a[i].r, &a[i].x, &a[i].y);
			for (long j = 1; j < i; j++) {
				double t; t = D[i][j] = D[j][i] = Dis(a[i].x, a[i].y, a[j].x, a[j].y);

				if( a[i].r >= a[j].r && t <= a[i].r - a[j].r)
					live[j] = true;
			}
		}
	}
	
	std::vector< std::pair<double, double> > Q[MAXN];
	#define AA(a, b, c) (acos( ( sqr(b) + sqr(c) - sqr(a) ) / (2 * b * c ) ))
	#define PI M_PI
	
	const double _2PI = 2 * M_PI;
	void Fuck(long u, long m) {
		double lx = a[u].x, ly = a[u].y + a[u].r;
		double t = D[u][m];double s = AA(Dis(lx, ly, a[m].x, a[m].y), t, a[u].r);

		if( a[m].x < a[u].x ) s = _2PI - s;

		double l = AA(a[m].r, t, a[u].r);
		double l1 = s - l, l2 = s + l;
		if( l2 - _2PI > eps) Q[u].push_back( std::make_pair(0, l2 - _2PI) ), l2 = _2PI;
		if( l1 < -eps ) Q[u].push_back( std::make_pair(l1 + _2PI , _2PI) ), l1 = 0;
		if( eps < l2 - l1)
			Q[u].push_back( std::make_pair(l1, l2) );
	}

	double Ans = 0;

	void Cal(long u) {
		std::sort(Q[u].begin(), Q[u].end());

		double now = 0, r = 0;
		for (long i = 0; i < Q[u].size(); i++) {
			if( Q[u][i].first - now > eps)
				r += (Q[u][i].second - Q[u][i].first), now = Q[u][i].second;
			else
				if( Q[u][i].second -now > eps)
					r += (Q[u][i].second - now), now = Q[u][i].second;
		}
		Ans += a[u].r * (_2PI - r);
	}

	void Work(void) {
		for (long i = 1; i <= n; i++) {
			if(live[i]) continue;
			for (long j = i + 1; j <= n; j++)
				Fuck(i, j);
			Cal(i);
			#ifdef Debug
				printf("%0.3lf\n", Ans);
			#endif
		}
		printf("%0.3lf\n", Ans);
	}
	void solve(void) {
		Input();
		Work();
	}

}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
