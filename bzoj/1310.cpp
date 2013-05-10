//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
namespace Solve {
	typedef unsigned long long Int64;
	#ifdef unix
		#define LL "%lld"
	#else
		#define LL "%I64d"
	#endif
	const int MAXN = 65;
	int n, m; Int64 Rank;
	Int64 f[MAXN][MAXN][2], c[MAXN][MAXN];

	void Dp(void) {
		f[0][0][1] = 1; f[1][0][1] = 2; f[2][0][1] = 2, f[2][1][0] = 2;
		for (int i = 1; i <= n - 2; i++)
			for (int j = 0; j < i; j++)
				for (int k = 0; k <= 1; k++) if (f[i][j][k]) {
					f[i + 2][j + 1][k ^ 1] += 2 * f[i][j][k];
					f[i + 2][j][k] += f[i][j][k];
					f[i + 2][j + 2][k] += f[i][j][k];
				}
		c[0][0] = 1;
		for (int i = 1; i <= n + 1; i++) {
			c[i][0] = 1;
			for (int j = 1; j <= m + 1; j++)
				c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}

	}
	
	bool ret[MAXN];

	inline Int64 Gao(int L, int s) {
		if (s == 0) return 0;
		Int64 r = 0;
		for (int j = 0; j <= s; j++)
			r += f[L][j][0] >> 1;
		for (int j = 1; j <= s; j++)
			r += f[L][j - 1][1];
		for (int j = 2; j <= s; j++)
			r += f[L][j - 2][0] >> 1;
		return r;
	}

	inline bool Check(bool st[]) {
		for (int i = 1; i <= n; i++) 
			if (st[i] != st[n - i + 1])
				return st[i] < st[n - i + 1];
		return true;
	}

	inline int Count(bool st[]) {
		int ret = 0;
		for (int i = 2; i <= n; i++) ret += (st[i] != st[i - 1]);
		return ret;
	}

	Int64 Cal(int now) {
		int tmp[MAXN] = {0};
		for (int i = 2; i <= now; i++)
			tmp[i] += tmp[i - 1] + (ret[i] != ret[i - 1]);

		if (now == n) {
			if (tmp[now] <= m && Check(ret) && Count(ret) <= m)return 1;
			else return 0;
		}

		Int64 r = 0;
		for (int i = 0; i <= now - 1; i++)
			if (ret[i + 1] == 0) {
				if (now + i + 1 <= n) {
					int L = n - (now + i + 1), delta = 0;
					if (i && ret[i] == 0) delta = 1;
					r += Gao(L, m - tmp[i] - tmp[now] - delta);
				}else {
					bool st[MAXN] = {0};
					memcpy(st + 1, ret + 1, sizeof(ret[0]) * (now));
					for (int j = n; j > now; j--) st[j] = ret[n - j + 1];
					if (Check(st) && Count(st) <= m) r++;
					break;
				}
			}
		int mid = n >> 1;
		if (now * 2 <= n) {
			Int64 t = 0;
			for (int i = 0; i <= m - tmp[now] * 2; i += 2)
				t += c[n - now * 2 + 1][i];
			for (int i = 0; i <= m - tmp[now] * 2; i += 2)
				t += c[(n - now * 2 + 1) >> 1][i >> 1];
			r += (t >> 1);
		}
		return r;
	}

	void Work(void) {
		for (int i = 1; i <= n; i++) {
			Int64 tmp = Cal(i);
			#ifdef Debug
				printf(LL "\n", tmp);
			#endif
			if (tmp < Rank)
				Rank -= tmp, ret[i] = 1;
		}
		if (Rank != 1) puts("NO SUCH STONE");else {
			for (int i = 1; i <= n; i++) putchar(ret[i] ? 'X' : 'I'); puts("");
		}
	}

	void solve(void) {
		scanf("%d%d" LL, &n, &m, &Rank);
		Dp();
		Work();
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
