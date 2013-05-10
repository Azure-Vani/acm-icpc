#define FILEIO

#include <algorithm>
#include <cstring>
#include <cstdio>
#include <string>

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

using namespace std;

typedef long long Int64;

namespace Solve {
	const int MAXN = 210;
	const int Mod = 1000000007;

	char ch[MAXN];
	int n;

	inline void Add(Int64 &a, Int64 b) {
		a += b;
		a %= Mod;
	}

	Int64 f[MAXN][MAXN];
	inline Int64 Cal(char* a, char* ae, char* b, char* be) {
		int n = ae - a + 1, m = be - b + 1;
		memset(f, 0, sizeof f);
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= m; j++) {
				f[i][j] += f[i][j - 1] + f[i - 1][j] - f[i - 1][j - 1];
				if (a[i - 1] == b[j - 1])
					f[i][j] += f[i - 1][j - 1] + 1;
				f[i][j] %= Mod;
			}
		Int64 ret = 0;
		for (int i = 1; i <= m; i++) 
			if (b[i - 1] == a[n - 1])
				Add(ret, f[n - 1][i - 1] + 1);
		return ret;
	}

	inline void solve(void) {
		gets(ch); n = strlen(ch);
		Int64 ret = 0;
		for (int i = 0; i < n - 1; i++) {
			Int64 tmp = Cal(ch, ch + i, ch + i + 1, ch + n - 1);
			Add(ret, tmp);
		}
		printf(LL "\n", ret);
	}

}
int main(void) {
#ifdef FILEIO
	freopen("in", "r", stdin);
#endif
	int T; scanf("%d\n", &T);
	while (T--) Solve::solve();
	return 0;
}
