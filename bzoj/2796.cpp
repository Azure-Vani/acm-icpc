//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <map>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 10000;
	typedef long long Int64;
	
	Int64 fib[MAXN];
	int n = 86;

	map<Int64, int> f;

	inline void Prepare(void) {
		fib[0] = fib[1] = 1;
		for (int i = 2; i <= n; i++) {
			fib[i] = fib[i - 1] + fib[i - 2];
			f[fib[i]] = 1;
			if (fib[i] > 4e17) break;
		}f[1] = 1;
	}

	inline int Dfs(Int64 k) {
		if (f.count(k)) return f[k]; 
		int tmp = 1000000000;
		for (int i = 1; i <= n; i++) if (fib[i] > k) {
			tmp = min(Dfs(k - fib[i - 1]), Dfs(fib[i] - k)) + 1;
			break;
		}
		return f[k] = tmp;
	}

	inline void solve(void) {
		Int64 k; scanf("%lld", &k);
		printf("%d\n", Dfs(k));
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::Prepare();
	int t; scanf("%d", &t);
	while (t--)
	Solve::solve();
	return 0;
}
