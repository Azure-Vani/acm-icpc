//#define Debug
#include <cstdio>
namespace Solve {
	const long MAXN = 12;
	double a[MAXN][MAXN] = {0};
	long n;
	void Input(void) {
		scanf("%ld", &n);
		double u, p[MAXN] = {0}, S = 0;
		for (long i = 1; i <= n; i++)
			scanf("%lf", p + i), S += (p[i] * p[i]);
		for (long i = 1; i <= n; i++) {
			double T = 0;
			for (long j = 1; j <= n; j++) {
				scanf("%lf", &u); T += (u * u);
				a[i][j] = 2 * (u - p[j]);
			}
			a[i][n + 1] = T - S;
		}
	}
	void Gauss(void) {
		Input();
		for (long k = 1; k < n; k++) 
			for (long j = k + 1; j <= n; j++) {
				double delta = a[j][k] / a[k][k];
				for (long i = k + 1; i <= n + 1; i++)
					a[j][i] -= (a[k][i] * delta);
			}
		for (long i = n; i >= 1; i--) {
			double sum = 0;
			for (long j = n; j >= i + 1; j--)
				sum += (a[i][j] * a[n + 1][j]);
			a[n + 1][i] = (a[i][n + 1] - sum) / a[i][i];
		}
		for (long i = 1; i < n; i++) printf("%.3lf ", a[n + 1][i]);
		printf("%.3lf\n", a[n + 1][n]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Gauss();
	return 0;
}
