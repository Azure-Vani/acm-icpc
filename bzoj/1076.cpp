//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 105;
	const int MAXM = 40000;

	double f[MAXN][MAXM];
	int k, n, p[16], c[16];

	void Input(void) {
		scanf("%d%d", &k, &n);
		for (int i = 1; i <= n; i++) {
			scanf("%d", c + i);
			int u;
			while (scanf("%d", &u), u != 0)
				p[i] |= 1 << u - 1;
		}
	}

	void Work(void) {
		Input();
		for (int i = k; i >= 1; i--)
			for (int State = 0; State <= (1 << n) - 1; State++) {
				double Temp = 0;
				for (int now = 1; now <= n; now++)
					Temp += std::max(f[i + 1][State], (State & p[now]) == p[now] ? f[i + 1][State | (1 << now - 1)] + c[now] : 0) / n;
				f[i][State] = Temp;
			}
		printf("%.6lf\n", f[1][0]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}