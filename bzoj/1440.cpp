//#define Debug
/*
 problem:
 	given n, x, and m, calculate sigma(x^i*i^x, 1<=i<=n) % m
 solution:
 	f(n, x) = sigma(x^i*i^x, 1<=i<=n)
	f(n, x) - x*f(n-1, x) = sigma(x^i*i^x, 1<=i<=n) - x * sigma(x^i*i^x, 1<=i<=n-1)
				sigma((i^x - (i-1)^x) * x^i, 1<=i<=n)
				sigma(sigma(i^j * C(x, j) * (-1)^(x-j+1), 0<=j<=x-1) * x^i, 1<=i<=n)
				sigma((C(x,j) * (-1)^(x-j+1)) * sigma(i^j*x^i, 1<=i<=n), 0<=j<=x-1)
				sigma((C(x,j) * (-1)^(x-j+1)) * f(n, j), 0<=j<=x-1)
	f(n, x) = x*f(n-1, x) + sigma((C(x,j) * (-1)^(x-j+1)) * f(n, j), 0<=j<=x-1)
	matrix O((x*2)^3lgn)
	*/
#include <cstdio>
#include <algorithm>
#include <cstring>
#define T_T(x) (((x)&1)?-1:1)
#define rep(i,j,k) for (int i = j; i <= k; i++)
namespace Solve {
	typedef long long Int64;
	const int MAXN = 52;
	
	int M[MAXN][MAXN], C[MAXN][MAXN] = {1}, A[MAXN][MAXN];
	int n, x, Mod, L;

#define Mult(a, b) {\
	int c[MAXN][MAXN] = {0};\
	rep(i, 0, L) rep(j, 0, L) rep(k, 0, L) \
		c[i][j] = (Int64) ((Int64) c[i][j] + (Int64) a[i][k] * b[k][j] % Mod) % Mod;\
	memcpy(a, c, sizeof a);\
}

	inline void Pow(int n) {
		int ret[MAXN][MAXN] = {0};
		for (int i = 0; i <= L; i++) ret[i][i] = 1;
		while (n) {
			if (n & 1) Mult(ret, M);
			Mult(M, M);
			n >>= 1;
		}
		memcpy(M, ret, sizeof M);
	}

	int f[MAXN][MAXN];
	void solve(void) {
		scanf("%d%d%d", &n, &x, &Mod);
		rep(i,1,x) {
			C[i][0] = 1;
			rep(j,1,i) C[i][j] = (Int64) ((Int64) C[i - 1][j - 1] + (Int64) C[i - 1][j]) % Mod;
		}
		rep(i,0,x) rep(j,0,x) A[i][j] = C[i][j] * T_T(i - j + 1);
		M[0][0] = M[x + 1][0] = x;
		for (int i = 1; i <= x; i++) {
			for (int j = 0; j < i; j++) {
				for (int k = 0; k <= x + 1; k++)
					M[k][i] = (Int64) ((Int64) M[k][i] + (Int64) A[i][j] * M[k][j]) % Mod;
			}
			M[i][i] += x;
		}
		M[x + 1][x + 1] = 1;
		L = x + 1;
		Pow(n - 1);
		int Ans = 0;
		for (int i = 0; i <= x; i++)
			Ans = (Int64) ((Int64) Ans + (Int64) x * M[i][x] % Mod) % Mod;
		printf("%lld\n", ((Int64)Ans + (Int64)M[x + 1][x]) % Mod);
	}
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
