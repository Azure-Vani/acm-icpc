//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
	const int MAXN = 53;
	const int inf = 0x6eeeeeee;
	
	char a[MAXN];int n;
	void Input(void) {
		gets(a + 1);
		a[0] = '$';n = strlen(a + 1);
	}
	
	inline bool Same(int l1, int r1, int l2, int r2) {
		if (r1 - l1 != r2 - l2) return false;
		int l = 0;
		while (l1 + l <= r1 && a[l1 + l] == a[l2 + l]) l++;
		return l1 + l > r1;
	}
	
	int f[MAXN][MAXN] = {0};
	void Work(void) {
		f[1][1] = 1;
		for (int i = 2; i <= n; i++) {
			for (int j = 1; j < i; j++) {
				f[i][j] = inf;
				for (int k = j; k < i; k++)
					f[i][j] = std::min(f[i][j], f[k][j] + i - k);
				int mid = (i + j) >> 1; mid++;
				if (((i - j) & 1) && Same(mid, i, mid * 2 - i - 1, mid - 1))
					f[i][j] = std::min(f[i][j], f[mid - 1][j] + 1);
			}
			f[i][i] = inf;
			for (int j = 1; j < i; j++)
				f[i][i] = std::min(f[i][i], f[i - 1][j] + 2);
		}
		int A = inf;
		for (int i = 1; i <= n; i++) A = std::min(A, f[n][i]);
		printf("%d\n", A);
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
