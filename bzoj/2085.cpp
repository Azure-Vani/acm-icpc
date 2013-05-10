//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	typedef long long Int64;
	const Int64 inf = 10000000000000000ll;
	const int MAXN = 205;
	const int MAXM = 120005;
	const int Base = 13331;
	const Int64 Mod = 399199997;

	int n, m = 0; Int64 pow;
	char ch[MAXM], *a[MAXN], *v = ch + 1;
	Int64 M[MAXN][MAXN];
	Int64 Hash[MAXM], p[MAXM];

	inline Int64 hash(char *p, int L) {
		int i = p - ch; Int64 ret = Hash[i + L - 1] - Hash[i - 1] * Solve::p[L] % Mod;
		while (ret < 0) ret += Mod;
		return ret;
	}
	inline int Cal(char a[], char b[]) {
		int na = strlen(a), nb = strlen(b);
		if (nb <= na && a != b)
			for (int i = 0; nb + i - 1 <= na; i++)
				if (hash(a + i, nb) == hash(b, nb)) return 0;
		for (int i = a == b ? na - 1 : std::min(nb, na); i >= 1; i--) {
			Int64 t1 = hash(b, i), t2 = hash(a + na - i, i);
			if (t1 == t2) return nb - i;
		}
		return nb;
	}

	void Input(void) {
		scanf("%d%lld\n", &n, &pow);
		for (int i = 1; i <= n; i++) gets(v), a[i] = v, v += strlen(v) + 1, m += strlen(a[i]);
		m += n - 1, p[0] = 1;
		for (int i = 1; i <= m; i++) Hash[i] = (Hash[i - 1] * Base + ch[i]) % Mod, p[i] = (p[i - 1] * Base) % Mod;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				M[i][j] = Cal(a[i], a[j]);
	}

	inline void Mult(Int64 a[MAXN][MAXN], Int64 b[MAXN][MAXN]) {
		Int64 c[MAXN][MAXN] = {0};
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++){
				Int64 tmp = inf;
				for (int k = 1; k <= n; k++)
					tmp = std::min(tmp, a[i][k] + b[k][j]);
				c[i][j] = tmp;
			}
		memcpy(a, c, sizeof c);
	}

	void Pow(int n) {
		Int64 ret[MAXN][MAXN];
		for (int i = 1; i <= Solve::n; i++) for (int j = 1; j <= Solve::n; j++) if (i != j) ret[i][j] = inf; else ret[i][j] = 0;
		while (n) {
			if (n&1) Mult(ret, M);
			Mult(M,M);
			n >>= 1;
		}
		memcpy(M, ret, sizeof ret);
	}

	void solve(void) {
		Input();
		Pow(pow - 1);
		Int64 Ans = inf;
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) Ans = std::min(Ans, (Int64)strlen(a[i]) + M[i][j]);
		printf("%lld\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("cho.in", "r", stdin);
		freopen("cho.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
