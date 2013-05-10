#define STDIO
#define INPUT "in"
#define OUTPUT "out"

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	typedef long long Int64;
	const int Mod = 999911659;
	const int MAXP = 521;

	Int64 n;int p, last, l;
	Int64 cnt[MAXP];
	bool hash[MAXP]; int ModList[MAXP], fim[MAXP];

	inline void GetCnt(void) {
		int mod = 1 % p;
		while (!hash[mod] && l < n && (hash[fim[mod] = ++l, ModList[l] = mod] = true, mod = (Int64) ((Int64) mod * 10 + 1ll) % p, true));
		last = ModList[l];
		int begin = fim[mod];
		for (int i = 1; i < begin; i++) cnt[i]++;
		for (int i = begin; i <= l; i++)
			cnt[i] += (Int64) (n - begin + 1) / (l - begin + 1);
		int circle = (n - begin + 1) % (l - begin + 1);
		for (int i = 1; i <= circle; i++)
			cnt[(last = ModList[i + begin - 1]), i]++;
		last = (p - last) % p;
	}

	int inv[10]; int c[MAXP][MAXP];

	inline int Cal(int t, int m) {
		static bool virgo = true;
		if (virgo) {
			virgo = false;
			inv[1] = 1;
			for (int i = 2; i <= 9; i++)
				inv[i] = (Int64) inv[Mod % i] * ((Int64)Mod - Mod / i) % Mod;
			memset(c, -1, sizeof c);
		}
		if (c[t][m] != -1) return c[t][m];
		int& ret = c[t][m]; ret = 1;
		Int64 n = cnt[t] + m - 1;
		for (Int64 i = n; i > n - m; i--) ret = (Int64) ret * (i % Mod) % Mod;
		for (int i = 1; i <= m; i++) ret = (Int64) ret * inv[i] % Mod;
		return ret;
	}

	inline void Renew(int &a, int b) {
		a += b;
		if (a >= Mod) a -= Mod;
	}

	int f[MAXP][MAXP][10];
	inline Int64 Work(void) {
		f[0][0][0] = 1;
		for (int i = 0; i < l; i++) {
			for (int j = 0; j < p; j++) {
				for (int k = 0; k <= 8; k++) if (f[i][j][k]) {
					int now = f[i][j][k];
					for (int s = 0; s + k <= 8; s++)
						Renew(f[i + 1][(Int64) ((Int64)ModList[i + 1] * s + (Int64)j) % p][s + k], (Int64) now * Cal(i + 1, s) % Mod);
				}
			}
		}
		Int64 ret = 0;
		for (int i = 0; i <= 8; i++) {
			ret += f[l][last][i];
			if (ret >= Mod) ret -= Mod;
		}
		return ret;
	}

	void solve(FILE *fin, FILE *fout) {
		fscanf(fin, LL "%d", &n, &p);
		GetCnt();
		Int64 Ans = Work();
		fprintf(fout, LL "\n", Ans);
	}
}

int main(void) {
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
	     *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, stdout);
	fclose(fin);
	fclose(fout);
#endif
	return 0;
}
