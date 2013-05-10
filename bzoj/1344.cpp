#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	const int MAXN = 3;
	const int Mod = 1000000000;
	typedef unsigned long long Int64;

	#define Mult(a, b) {\
		Int64 c[MAXN][MAXN];\
		for (int i = 0; i < 3; i++)\
			for (int j = 0; j < 3; j++) {\
				Int64 tmp = 0;\
				for (int k = 0; k < 3; k++)\
					tmp = (tmp + (a[i][k] * b[k][j]) % Mod) % Mod;\
				c[i][j] = tmp;\
			}\
		memcpy(a, c, sizeof a);\
	}

	Int64 M[MAXN][MAXN] = {{0,0,2},{0,0,1},{1,2,4}};
	void Work(int n) {
		Int64 ret[MAXN][MAXN] = {{1,0,0},{0,1,0},{0,0,1}};
		while (n) {
			if (n & 1) Mult(ret, M);
			Mult(M, M);
			n >>= 1;
		}
		memcpy(M, ret, sizeof M);
	}
	void solve(void) {
		int n; scanf("%d", &n);
		if (n == 1) {puts("0"); exit(0);}
		Work(n - 2);
		Int64 a[3] = {0, 2, 1}, b[3] = {0}, c[3] = {2,0,1};
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				b[i] = ((b[i] + (a[j] * M[j][i]) % Mod) % Mod);
		Int64 Ans = 0;
		for (int i = 0; i < 3; i++)
			Ans = ((Ans + (b[i] * c[i]) % Mod) % Mod);
		printf(LL "\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
