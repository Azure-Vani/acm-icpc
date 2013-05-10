#include <cstdio>
#include <cstring>
namespace Solve {
	#define LL "%ld"
	const long MAXN = 16;
	const long MAXM = (1 << (MAXN - 1)) + 10;
	const long MOD = 19901013;

	bool map[MAXN][MAXN] = {0}; long n, m;
	void Input(void) {
		scanf("%ld%ld\n", &n, &m);
		char tmp[MAXN];
		for (long i = 0; i < n; i++) {
			gets(tmp);
			for (long j = 0; j < m; j++)
				map[i][j] = (tmp[j] == '.');
		}
	}
	long S[MAXN][MAXN][MAXN][MAXN] = {0};
	#define It(i) (1 << (i))
	#define Yes(k, i) (!(k & (1<<i)))
	#define Make(k, i) (k | It(i))
	#define Add(S, a) (S = (S + a) % MOD)
	inline void Remove(long long &S, long a) {S -= a; while(S < 0) S += MOD;}
	long f[MAXN][MAXN][MAXM] = {0};
	inline void Gao(long l, long r, long u) {
		long L = (1 << (r + 1)), delta = (1 << l);
		for (long i = 0; i <= n; i++)
			for(long j = l; j <= r; j++)
				for (long k = 0; k <= L; k++)
					f[i][j][k] = 0;
		f[u][l][0] = 1;
		for (long i = u; i < n; i++)
			for (long j = l; j <= r; j++)
				for (long k = 0; k < L; k += delta) if (f[i][j][k] > 0) {
					long w = k;
					if (j < r) {
						long value = f[i][j][k];
						Add(f[i][j + 1][k - (k & It(j))], value);
						if (Yes(k, j)) {
							if (map[i][j] && map[i + 1][j])
								Add(f[i][j + 1][Make(k, j)], value);
							if (map[i][j] && map[i][j + 1] && Yes(k, j + 1))
								Add(f[i][j + 1][Make(k, j + 1)], value);
						}
					}else {
						long value = f[i][j][k];
						Add(f[i + 1][l][k - (k & It(j))], value);
						if (Yes(k, j)) {
							if (map[i][j] && map[i + 1][j])
								Add(f[i + 1][l][Make(k, r)], value);
						}
					}
					k = w;
				}
		for (long i = u; i < n; i++)
			S[l][r][u][i] = f[i + 1][l][0];
	}
	void MakeSum(void) {
		for (long l = 0; l < m; l++)
			for (long r = l; r < m; r++)
				for (long u = 0; u < n; u++) {
					Gao(l, r, u);
				}
	}
	long long A = 0;
	inline long GetList(long M, long* a) {
		long r = 0, l = 0;
		while (M > 0){ if(M & 1) a[++r] = l;l++; M >>= 1;}
		return r;
	}
	void IEP(void) {
		long End = ((1 << (m - 1)) - 1);
		for (long T = 0; T <= End; T++) {
			long p[MAXN] = {0};long long f[MAXN] = {0};
			long l = GetList(T, p);
			p[0] = -1, p[++l] = m - 1;
			for (long i = 0; i < n; i++) {
				f[i] = 1;
				for (long k = 1; k <= l; k++)
					f[i] = (f[i] * S[p[k - 1] + 1][p[k]][0][i]) % MOD;
				for (long j = 0; j < i; j++) {
					long long temp = f[j];
					for (long k = 1; k <= l; k++)
						temp = (temp * S[p[k - 1] + 1][p[k]][j + 1][i]) % MOD;
					Remove(f[i], temp);
				}
			}
			if (l & 1) Add(A, f[n - 1]); else Remove(A, f[n - 1]);
		}
	}
	void solve(void) {
		Input();
		MakeSum();
		IEP();
		while (A < 0) A += MOD;
		printf(LL "\n", A % MOD);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
