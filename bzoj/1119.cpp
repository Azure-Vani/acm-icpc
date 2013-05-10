#include <cctype>
#include <cstdio>
#include <algorithm>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	const int inf = 1050000000;
	const int MAXN = 1000100;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int pos[MAXN], a[MAXN], b[MAXN], c[MAXN], MM = inf, n;
	void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) MM = std::min(MM, c[i] = ScanInt());
		for (int i = 1; i <= n; i++) pos[a[i] = ScanInt()] = i;
		for (int i = 1; i <= n; i++) b[i] = ScanInt();
	}

	bool vis[MAXN];
	long long Ans = 0;
	void solve(void) {
		Input();
		for (int i = 1; i <= n; i++) if (!vis[i]) {
			vis[i] = true;
			int min = inf, l = i, cnt = 0;
			long long sum = 0;
			do {
				int t = pos[b[l]]; sum += c[a[l]];
				min = std::min(c[a[l]], min);
				vis[l = t] = true, cnt++;
			}while (l != i);
			Ans += std::min(min * (cnt - 2) + sum, MM * (cnt + 1) + sum + min);
		}
		printf(LL "\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
