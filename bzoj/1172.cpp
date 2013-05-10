#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long Int64;

namespace Solve {
	const int MAXN = 310, MAXM = 10010, MAXP = 200001, MAXX = 1000100;
	
	int n, m, k, Mod, M = 0;
	int a[MAXN][MAXM];

	inline void Input(void) {
		scanf("%d%d%d%d", &n, &m, &k, &Mod);
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= m; j++) 
				scanf("%d", &a[i][j]), M = std::max(M, a[i][j]);
	}

	int fim[MAXP], tag, List[MAXM], gcd[MAXX], next[MAXN][MAXN];
	
	inline int Gcd(int a, int b) {
		return !b?a:Gcd(b, a % b);
	}

	inline void Initialize(void) {
		for (int i = 1; i <= k; i++) if (k % i == 0) List[ fim[i] = ++tag ] = i;
		for (int i = 0; i <= M; i++) gcd[i] = fim[Gcd(i, k)];
		for (int i = 1; i <= tag; i++) 
			for (int j = 1; j <= tag; j++) 
				for (int k = tag; k >= 1; k--) if ((Int64) List[i] * List[j] % List[k] == 0) {
					next[i][j] = k;
					break;
				}
	}

	inline void Add(int &a, int b) {
		b %= Mod;
		a += b;
		if (a >= Mod) a -= Mod;
	}

	int f[MAXN][MAXN], g[3][MAXN];
	inline void Work(void) {
		for (int i = 1; i <= m; i++) Add(f[1][gcd[a[1][i]]], 1);
		for (int i = 2; i <= n; i++) {
			memset(g, 0, sizeof g);
			for (int j = 1; j <= m; j++) Add(g[1][gcd[a[i][j]]], 1);
			if (i != n)
				for (int j = 1; j <= tag; j++) 
					for (int k = j; k <= tag; k++) 
						if (j != k) Add(g[2][next[j][k]], (Int64) g[1][j] * g[1][k] % Mod * 2ll % Mod);
						else Add(g[2][next[j][k]], (Int64) g[1][j] * (g[1][k] - 1) % Mod);
			for (int j = 1; j <= tag; j++) 
				for (int k = 1; k <= tag; k++) 
					Add(f[i][next[j][k]], (Int64) f[i - 1][j] * (g[1][k] + g[2][k]) % Mod);
		}
		printf("%d\n", f[n][fim[k]]);
	}

	inline void solve(void) {
		Input();
		Initialize();
		Work();
	}
}

int main(void) {
//	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}
