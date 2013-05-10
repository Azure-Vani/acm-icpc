#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 1000010;
	const int Mod = 1000000007;

	bool tag[MAXN]; int prime[MAXN], cnt;

	int n;

	inline void Generate(void) {
		for (int i = 2; i <= n; i++) {
			if (!tag[i]) prime[++cnt] = i;
			for (int j = 1; j <= cnt && prime[j] * i <= n; j++) {
				tag[prime[j] * i] = true;
				if (i % prime[j] == 0) break;
			}
		}
	}

	int a[MAXN];

	inline void Factor(void) {
		for (int i = 1; i <= cnt; i++) {
			int t = n;
			while (t) a[i] += t / prime[i], t /= prime[i];
		}
	}

	int f[MAXN];

	inline int Count(void) {
		f[0] = 1;
		for (int i = 1; i <= cnt; i++) {
			f[i] = (f[i - 1] + (long long)a[i] * f[i - 1] * 2ll % Mod) % Mod;
		}
		return f[cnt];
	}

	inline void solve(void) {
		scanf("%d", &n);
		Generate();
		Factor();
		printf("%d\n", Count());
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		//freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
