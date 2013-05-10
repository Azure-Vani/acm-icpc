//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>

#define rep(i,l,r) for(int i = l; i <= r; i++)

namespace Solve {
	struct Pair {
		int v, index;
		inline void Scan(void) {scanf("%d", &v);}
	}a[200010];
	int n;

	inline bool cmp(const Pair& a, const Pair& b) {
		if (a.v == b.v) return a.index < b.index;
		return a.v < b.v;
	}

	int f[200010][2];

	void solve(void) {
		scanf("%d", &n);
		rep(i,1,n) a[i].Scan(), a[i].index = i;
		std::sort(a + 1, a + n + 1, cmp);
		int L = ~0U>>1, R = L, i = 1;
		while (i <= n) {
			int j = i; while (j < n && a[j + 1].v == a[i].v) j++;
			f[j][0] = std::min(f[i - 1][1], f[i - 1][0] + (a[i].index < R));
			f[j][1] = std::min(f[i - 1][1] + (L < a[j].index), f[i - 1][0] + 1);
			L = a[i].index, R = a[j].index;
			i = j + 1;
		}
		printf("%d\n", std::min(f[n][0], f[n][1]) + 1);
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
