#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 100010;

	class BIT{public:
		int a[MAXN], n;
		#define LowBit(x) ((x) & (-(x)))
		inline void Set(int _n){n = _n;}
		inline void Insert(int u, int t) {for (int i = u; i <= n; i += LowBit(i)) a[i] += t;}
		inline int  Cal(int u) {int ret = 0;for (int i = u; i >= 1; i -= LowBit(i)) ret += a[i]; return ret;}
	}T;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n; int hash[MAXN];
	void solve(void) {
		T.Set(n  = (ScanInt() << 1));
		int Ans = 0;
		for (int i = 1, tmp; i <= n; i++) {
			tmp = ScanInt();
			if (hash[tmp]) {
				Ans += T.Cal(i) - T.Cal(hash[tmp] - 1) - 1;
				T.Insert(hash[tmp], -1);
			}else
				T.Insert(hash[tmp] = i, 1);
		}
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
