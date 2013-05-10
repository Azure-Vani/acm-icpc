#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cassert>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 1000050;

	inline Int64 ScanInt(void) {
		int c; Int64 r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = (Int64) (r * 10ll + c - '0');
		return r;
	}

	Int64 a[MAXN], m; int n, k;
	void Input(void) {
		scanf("%d%d", &n, &k); m = ScanInt();
		for (int i = 1; i <= n; i++) a[i] = ScanInt(), assert(a[i] > a[i - 1]);
	}

	int f[2][MAXN], l = 0;
	bool now = 0, next = 1;
	int Ans[MAXN];
	void Prepare(void) {
		int l = 1, r = k + 1;
		for (int i = 1; i <= n; i++) {
			Ans[i] = i;
			while (r < i) r++;
			while (r - l + 1 < k + 1) r++;
			while (r - l + 1 > k + 1) l++;
			while (l < i && r < n && std::max(a[r] - a[i], a[i] - a[l]) > std::max(a[r + 1] - a[i], a[i] - a[l + 1])) l++, r++;
			assert(l <= i);
			assert(i <= r);
			if (a[i] - a[l] >= a[r] - a[i])
				f[next][i] = l;
			else
				f[next][i] = r;
		}
	}

	void Work(void) {
		Int64 pos = 1;
		while (pos <= m) {
			now ^= 1, next ^= 1;
			if (m & pos)
				for (register int i = 1; i <= n; i++)
					Ans[i] = f[now][Ans[i]];
			for (register int i = 1; i <= n; i++) f[next][i] = f[now][f[now][i]];
			pos <<= 1;
		}
		for (int i = 1; i < n; i++) printf("%d ", Ans[i]); printf("%d\n", Ans[n]);
	}
	void solve(void) {
		Input();
		Prepare();
		Work();
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
