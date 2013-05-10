//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <set>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 100000;

	int b[MAXN], a[MAXN], n, m;
	typedef vector<int> VII;
	vector<VII> Ans;
	multiset<int> M;
	
	inline void Cal(int x) {
		if (x <= 0 || x % 2) return; x >>= 1;
		M.clear();
		a[1] = x;
		for (int i = 1; i <= m; i++) M.insert(b[i]);
		for (int i = 2; i <= n; i++) {
			a[i] = *M.begin() - a[1];
			for (int j = 1; j < i; j++) {
				multiset<int>::iterator it = M.find(a[j] + a[i]);
				if (it == M.end()) return;
				M.erase(it);
			}
		}
		vector<int> tmp;
		for (int i = 1; i <= n; i++) tmp.pb(a[i]);
		Ans.pb(tmp);
	}

	inline void solve(void) {
		scanf("%d", &n); m = n * (n - 1) / 2;
		for (int i = 1; i <= m; i++) {
			scanf("%d", b + i);
		}
		sort(b + 1, b + 1 + m);
		for (int i = 3; i <= min(m, n + 5); i++) if (b[i] != b[i + 1]) {
			Cal(b[1] + b[2] - b[i]);
		}
		printf("%d\n", Ans.size());
		foreach(it, Ans) {
			foreach(ot, (*it)) printf("%d ", *ot);
			putchar('\n');
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
