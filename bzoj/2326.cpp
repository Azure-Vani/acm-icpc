//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
namespace Solve {
	const int MAXN = 10;
	
	#define LL "%lld"
	typedef unsigned long long Int64;
	
	Int64 Mod;
	#define Mult(a, b) { \
		Int64 c[MAXN][MAXN] = {0}; \
		for (int i = 1; i <= 3; i++) \
			for (int j = 1; j <= 3; j++) { \
				Int64 tmp = 0; \
				for (int k = 1; k <= 3; k++)\
					tmp = (tmp % Mod + a[i][k] % Mod * b[k][j] % Mod) % Mod;\
				c[i][j] = tmp;\
			}\
		memcpy(a, c, sizeof c);\
	}

	void Pow(Int64 M[MAXN][MAXN], Int64 n) {
		Int64 ret[MAXN][MAXN] = {0};
		for (int i = 1; i <= 3; i++) ret[i][i] = 1;
		while (n) {
			if (n & 1) Mult(ret, M);
			Mult(M, M);
			n >>= 1;
		}
		memcpy(M, ret, sizeof ret);
	}

	Int64 Work(Int64 S, Int64 n, Int64 base) {
		Int64 M[MAXN][MAXN] = {0};
		M[1][1] = base % Mod;
		M[2][1] = M[2][2] = M[3][2] = M[3][3] = 1;
		Pow(M, n);
		return (Int64) ((S % Mod * M[1][1] % Mod + base / 10 % Mod * M[2][1] % Mod + M[3][1]) % Mod);
	}

	void solve(void) {
		Int64 n, S = 0;
		scanf(LL LL, &n, &Mod);
		for (Int64 i = 10; ;i *= 10) {
			if (i > n) {
				S = Work(S, n - i / 10 + 1, i);
				break;
			}
			S = Work(S, i - i / 10, i);
		}
		printf(LL "\n", S);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
