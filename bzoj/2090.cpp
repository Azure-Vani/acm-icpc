//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#define max(a, b) ((a)>(b)?(a):(b))
namespace Solve {
	const int MAXN = 500050;
	const int MAXM = 1000050;

	int n, k, a[MAXN];
	char opt[MAXN];

	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	inline int ScanChr(void) {
		int c;
		while (c = getchar(), c != '=' && c != '<' && c != '>') {}
		return c;
	}

	int m;
	void Input(void) {
		n = ScanInt(), k = ScanInt();
		for (int i = 1; i <= n; i++) a[i] = ScanInt(), m = max(m, a[i]);
		for (int i = 0; i < k; i++) opt[i] = ScanChr();
	}

	#define Lowbit(x) ((x) & (-(x)))
	class BIT {public:
		int a[MAXM], n;
		inline void Set(int _n){n = _n;}
		inline void Insert(int u, int t) {for (int i = u; i <= n; i += Lowbit(i)) a[i] = max(a[i], t);}
		inline int Ask(int u) {int ret = 0;for (int i = u; i >= 1; i -= Lowbit(i)) ret = max(ret, a[i]);return ret;}
	}T, rev_T;

	int Same[MAXM];
	void Work(void) {
		T.Set(m); rev_T.Set(m);
		int l = 0, ret = 0;
		for (int i = 1; i <= n; i++) {
			int Now = 0, t1, t2, t3;
			t1 = T.Ask(a[i] - 1);
			t2 = rev_T.Ask(m - a[i]);
			t3 = Same[a[i]];
			Now = max(t1, max(t2, t3)) + 1;
			char tmp = opt[(Now - 1)% k];
			if (tmp == '>') rev_T.Insert(m - a[i] + 1,  Now);else
			if (tmp == '<') T.Insert(a[i], Now);else
			if (tmp == '=') Same[a[i]] = max(Same[a[i]], Now);
			ret = max(ret, Now);
		}
		printf("%d\n", ret);
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
