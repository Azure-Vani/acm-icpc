#include <cstdio>
#include <cstring>
#include <algorithm>
namespace Solve {
	const int MAXN = 11;const int MAXM = 1 << MAXN; const int inf = 1000000000;
	int f[MAXM][MAXM], fee[MAXM][2], a[MAXM][MAXM], log2[MAXM], cost[MAXN];
	int n, N, M;
	void Input(void) {
		scanf("%d", &n); N = 1 << n, M = (N << 1);
		for (int i = 0; i < N; i++) scanf("%d", &fee[i][0]);
		for (int i = 0; i < N; i++) scanf("%d", &fee[i][1 - (fee[i][0] ^= 1)]);
		for (int i = 0; i < N - 1; i++) for (int j = i + 1; j < N; j++) scanf("%d", &a[i][j]), a[j][i] = a[i][j];
	}
	#define lch(x) ((x) << 1)
	#define rch(x) (((x) << 1) + 1)
	void Initialize(void) {
		log2[1] = 0;
		for (int i = 2; i < M; i++) log2[i] =  log2[i >> 1] + 1;
		for (int i = N; i < M; i++, memset(cost, 0, sizeof cost)) {
			for (int now = i, level = 1; level < N; level <<= 1) {
				now ^= level; int &t = cost[log2[level]];
				for (int j = now; j < now + level; j++) t += a[i - N][j - N];
				if (now & level) now -= level;
			}
			for (int S = 1, p; S < N; S++) 
				p = S & -S, f[i][rch(S)] = f[i][rch(S - p)] + cost[log2[p]];
			for (int S = 0; S < N; S++) f[i][lch(S)] = f[i][rch(N - 1 - S)] + fee[i - N][0];
			for (int S = 0; S < N; S++) f[i][rch(S)] += fee[i - N][1];
		}
	}
	void Work(void) {
		for (int i = N - 1; i > 0; i--)
			for (int S = 0; S < M; S += M >> log2[i])
				for (int sum = N >> log2[i], half = sum >> 1, d; sum >= 0; sum--) {
					f[i][S + sum] = inf, d = (sum < half) * (half << 1);
					for (int L = std::min(sum, half); L >= 0 && sum - L <= half; L--)
						f[i][S + sum] = std::min(f[i][S + sum], f[lch(i)][S + d + L] + f[rch(i)][S + d + sum - L]);
				}
		int Ans = inf;
		for (int i = 0; i <= N; i++) Ans = std::min(Ans, f[1][i]);
		printf("%d\n", Ans);
	}
	void solve(void) {
		Input();
		Initialize();
		Work();
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
