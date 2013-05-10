#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {

	const int MAXN = 100010;

	struct Node {
		int d, p;
	}a[MAXN];

	int b[MAXN], n, m;

	set<pair<int, int> > T;
	bool cmp(Node x, Node y) { return x.d < y.d; }

	inline void solve(void) {
		while (scanf("%d%d", &n, &m) == 2) {
			rep(i,n) scanf("%d", b + i);
			rep(i,m) scanf("%d", &a[i].d);
			rep(i,m) scanf("%d", &a[i].p);
			T.clear();
			sort(b + 1, b + n + 1);
			sort(a + 1, a + m + 1, cmp);
			int p = m;long long Ans = 0;
			for (int i = n; i >= 1; i--) {
				while (p > 0 && a[p].d >= b[i]) {
					T.insert(mp(a[p].p, p));
					p--;
				}
				if (T.empty()) {Ans = -1; break;}
				else {
					set<pair<int, int> >::iterator it = T.begin();
					Ans = Ans + (long long)it->first;
					T.erase(it);
				}
			}
			if (Ans == -1) puts("No"); else printf("%I64d\n", Ans);
		}
	}
}

int main(void) {
	#ifdef FILEIO
		//freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
