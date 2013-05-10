#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 105;
	const int inf = 0x6eeeeeee;
	
	char a[MAXN]; int n;
	void Input(void) {
		gets(a + 1);
		a[0] = '$';
		n = strlen(a + 1);
	}
	
	inline int Length(int u) {
		int ret = 0;
		while (u > 0) ret++, u /= 10;
		return ret;
	}
	
	inline bool Same(int l1, int r1, int l2, int r2) {
		if (l1 - r1 != l2 - r2) return false;
		int l = 0;
		while (l1 + l <= r1 && a[l1 + l] == a[l2 + l]) l++;
		return l1 + l > r1;
	}
	
	int f[MAXN][MAXN];
	void Work(void) {
		for (int i = 1; i <= n; i++) f[i][i] = 1;
		for (int i = n; i >= 1; i--)
			for (int j = i + 1; j <= n; j++) {
				f[i][j] = inf;
				for (int k = j - 1; k >= i; k--)
					f[i][j] = std::min(f[i][j], f[i][k] + f[k + 1][j]);
				int t;
				for (int k = j; (t = k * 2 - j - 1) >= i; k--) {
					int l = k, r = j, left;
					for (int num = 2; (left = 2 * l - r - 1) >= i; num++)
						if (Same(left, l - 1, l, r)) {
							int L = f[l][r];
							f[i][j] = std::min(f[i][j], f[i][left - 1] + L + 2 + Length(num));
							int c = l; l = left, r = c - 1;
						} else break;
				}
			}
		printf("%d\n", f[1][n]);
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
}
