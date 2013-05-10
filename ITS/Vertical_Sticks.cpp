#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 55;
	const int MAXM = 1010;

	int a[MAXN], n, T; long double C[MAXN][MAXN];

	long double f[MAXN][MAXN];

	inline void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
	}

	inline long double Work(void) {
		sort(a + 1, a + n + 1);
		long double Ans = 1;
		for (int i = 2; i <= n; i++) {
			long double sum = 0;
			for (int j = 1; j <= n; j++) {
				int h = 1;
				while (a[h] < a[j]) h++;
				h = n - h;
				int res = i - 1;
				if (h <= n - res - 1) f[res][0] = res + 1.0;
				for (int used = std::max(1, h - n + res + 1); used <= h && used <= res; used++) {
					long double p = (long double)(used) / (long double)(res);
					f[res][used] = (f[res - 1][used] + 1) * (1.0 - p) + p;
				}
				long double tmp = 0;
				for (int k = 0; k <= h && k <= i - 1; k++) {
					long double p = C[h][k] * C[n - 1 - h][i - 1 - k] / C[n - 1][i - 1];
					tmp += p * f[i - 1][k];
				}
				sum += tmp;
			}
			Ans += sum / n;
		}
		return Ans;
	}

	inline void Initialize(void) {
		C[0][0] = 1;
		for (int i = 1; i <= 50; i++) {
			C[i][0] = 1;
			for (int j = 1; j <= 50; j++) {
				C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
			}
		}
	}

	inline void solve(void) {
		Initialize();
		int T; scanf("%d", &T);
		while (T--) {
			Input();
			printf("%.2Lf\n", Work());
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

