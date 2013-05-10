#include <cstdio>
#include <algorithm>
#define min(a,b) ((a)<(b)?(a):(b))
namespace Solve {
	const int MAXN = 1000010;
	const int Mod = 19930726;

	typedef long long Int64;
	int n, a[MAXN], hash[MAXN], Len[MAXN]; Int64 k, s = 0;

	inline void Input(void) {
		scanf("%d%lld\n", &n, &k);
		for (int i = 1; i <= n; i++) a[i] = getchar() - 'a' + 1;
	}

	inline void Extend(void) {
		register int MaxR = -1, where = 0;
		for (register int i = 1, it; i <= n; i++) {
			it = 0;
			if (i <= MaxR) {
				it = Len[(where << 1) - i];
				if (i + it > MaxR)
					it = MaxR - i;
			}
			while (i - it > 0 && i + it <= n && a[i - it] == a[i + it]) it++;
			hash[Len[i] = --it, s += it + 1, (it << 1) + 1]++;
			if (i + it > MaxR) {
				MaxR = i + it;
				where = i;
			}
		}
	}
	
	inline int Pow(int a, Int64 n) {
		int r = 1;
		while (n) {
			if (n&1) r = (Int64) r * a % Mod;
			n >>= 1;
			a = (Int64) a * a % Mod;
		}
		return r;
	}

	inline int Work(void) {
		if (s < k)  return -1;
		int ret = 1;
		for (register int i = n, tmp, t; i >= 1 && k;i--) if (hash[i]) {
			k -= (t = min(hash[i], k));
			tmp = Pow(i, t);
			ret = (Int64) ret * tmp % Mod;
			if (i > 2) hash[i - 2] += hash[i];
		}
		return ret;
	}

	inline void solve(void) {
		Input();
		Extend();
		printf("%d\n", Work());
	}
}
int main(void) {
	//freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}
