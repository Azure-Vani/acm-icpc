//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
namespace Solve {
	const int MAXV = 22;
	const int MAXM = 124;
	const int MOD = 45989;
	int ScanInt(void) {
		int c, r;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	struct pair {
		int x, y;
		inline void Set(int _x, int _y){x = _x, y = _y;}
	}Fim[MAXM];
	int M[MAXM][MAXM], Map[MAXV][MAXV];
	bool c[MAXV][MAXV];
	int n, m, t, S, T, nEdge;

	void Input(void) {
		n = ScanInt(), m = ScanInt(), t = ScanInt(), S = ScanInt(), T = ScanInt();
		for (int _ = 0; _ < m; _++) {
			int x = ScanInt(), y = ScanInt();
			c[x][y] = c[y][x] = true;
			Fim[Map[x][y] = _ << 1].Set(x, y), Fim[Map[y][x] = _ << 1  ^ 1].Set(y, x);
		}
		nEdge = (m << 1) - 1;

		for (int i = 0; i <= nEdge; i++)
			for (int j = 0; j <= nEdge; j++)
				if (i != j && Fim[i].y == Fim[j].x && j != (i ^ 1))
					M[j][i]++;
	}

	#define Mul(a, b) {\
		int c[MAXM][MAXM] = {0};\
		for (int i = 0; i <= nEdge; i++)\
			for (int j = 0; j <= nEdge; j++)\
				for (int k = 0; k <= nEdge; k++)\
					c[i][j] = (c[i][j] + a[i][k] * b[k][j]) % MOD;\
		memcpy(a, c, sizeof a);\
	}
	void Pow(int n) {
		int ret[MAXM][MAXM] = {0};
		for (int i = 0; i <= nEdge; i++)
			ret[i][i] = 1;
		while (n) {
			if (n & 1) Mul(ret, M);
			Mul(M, M);
			n >>= 1;
		}
		memcpy(M, ret, sizeof M);
	}
	void Work(void) {
		Pow(t - 1);
		int Ans = 0;
		for (int i = 0; i <= nEdge; i++)
			if (Fim[i].y == T)
				for (int j = 0; j <= nEdge; j++)
					if (Fim[j].x == S)
						Ans = (Ans + M[i][j]) % MOD;
		printf("%d\n", Ans);
	}
	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
