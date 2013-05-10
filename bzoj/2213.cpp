//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#define max(a, b) ((a)>(b)?(a):(b))
#define min(a, b) ((a)<(b)?(a):(b))
namespace Solve {
	const int MAXN = 1000050;
	const int MAXM = 28;

	int a[MAXN], n;
	inline void Input(void) {
		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++) a[i] = getchar() - 'a' + 1;
	}

	int sum[MAXM];
	int delta1[MAXM][MAXM], delta2[MAXM][MAXM];
	/*
	   (sum_now[x] - sum_pas[x]) - (sun_now[y] - sum_pas[y])   // Max is x, Min is y
	   (sum_now[x] - sum_now[y]) - (sum_pas[x] - sum_pas[y])
	*/

	inline void Updata(int a, int b) {
		delta2[a][b] = min(delta2[a][b], delta1[a][b]);
		delta1[a][b] = sum[a] - sum[b];
	}

	int Ans = 0;
	void solve(void) {
		Input();
		memset(delta2, 60, sizeof delta2);
		register int x;
		for (int i = 1; i <= n; i++) {
			sum[x = a[i]]++;
			for (int j = 1; j <= 26; j++) if (j != x){
				if (sum[j] != 0) {
					int tmp = sum[x] - sum[j];
					Ans = max(Ans, tmp - delta2[x][j]);
					tmp = -tmp;
					Ans = max(Ans, tmp - min(delta2[j][x], delta1[j][x]));
				}
				Updata(j, x);
				delta2[x][j] = min(delta2[x][j], sum[x] - sum[j]);
			}
		}
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
