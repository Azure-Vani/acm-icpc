#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cstring>
namespace Solve {
	const long MAXN = 1012;
	inline long Read(void) {
		long r = 0; int c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	long a[MAXN] = {0}, n;
	inline void Input(void) {
		n = Read();
		for (long i = 1; i <= n; i++) a[i] = Read();
	}
	long left[MAXN][MAXN] = {0}, right[MAXN][MAXN] = {0};
	void Dfs(long l, long r) {
		if (left[l][r] != -1) return;
		if (l == r) {
			left[l][r] = right[l][r] = 0;
			return;
		}
		Dfs(l, r - 1);
		Dfs(l + 1, r);
		long L = left[l][r - 1], R = right[l + 1][r], &_L = left[l][r], &_R = right[l][r];
		if (L <= R)
			_L = a[r] == R ? 0 : a[r] > R || a[r] < L ? a[r] : a[r] + 1,
			_R = a[l] == L ? 0 : a[l] > R || a[l] < L ? a[l] : a[l] - 1;
		else
			_L = a[r] == R ? 0 : a[r] < R || a[r] > L ? a[r] : a[r] - 1,
			_R = a[l] == L ? 0 : a[l] < R || a[r] > L ? a[l] : a[l] + 1;
		return;
	}
	void Work(void) {
		Input();
		memset(left, -1, sizeof left);
		Dfs(1, n);
		puts(right[1][n] == a[n] ? "0" : "1");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	long __; scanf("%ld", &__);
	while (__--)
		Solve::Work();
	return 0;
}
