#include <cstdio>
#include <cstring>
#include <iostream>
namespace Solve {

	const int MAXN = 205;
	long double f[2][MAXN][MAXN], g[2][MAXN][MAXN], fsum[2][MAXN][MAXN], gsum[2][MAXN][MAXN];

	void solve(void) {
		int n, m;
		scanf("%d%d", &n, &m);
		f[1][1][1] = 1;

		int now = 0;
		for (int i = 2; i <= n; i++, now ^= 1) {
			memset(f[now], 0, sizeof f[now]);
			memset(g[now], 0, sizeof g[now]);
			f[now][i][i] = f[now ^ 1][i - 1][i - 1] / m;
			
			for (int H = 1; H <= i; H++) {
				for (int T = 2; T <= i - H; T++) {
					f[now][H][T] = f[now ^ 1][H][T - 1] / m;
					g[now][H][T] = g[now ^ 1][H][T - 1] / m;
				}
				f[now][H][1] = gsum[now ^ 1][H][i - 1] / m;
				g[now][H][1] = ((m - 2) * gsum[now ^ 1][H][i - 1] + (m - 1) * (fsum[now ^ 1][H][i - 2] + f[now ^ 1][H][i - 1])) / m;
			}

			memset(fsum, 0, sizeof fsum);
			memset(gsum, 0, sizeof gsum);
			for (int H = 1; H <= i; H++)
				for (int T = 1; T <= i; T++) {
					fsum[now][H][T] = fsum[now][H][T - 1] + f[now][H][T] * T;
					gsum[now][H][T] = gsum[now][H][T - 1] + g[now][H][T] * T;
				}
		}

		long double Ans = 0;
		for (int H = 1; H <= n; H++)
			for (int T = 1; T <= n - H; T++)
				Ans += f[now ^ 1][H][T] * (T + H) + g[now ^ 1][H][T] * T * H;
		Ans += f[now ^ 1][n][n] * n;
		std::cout.precision(5);
		std::cout << std::fixed << Ans << std::endl;
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
