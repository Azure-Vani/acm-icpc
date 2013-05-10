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
#include <map>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {

	long long n, kase;;
	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	const int MAXN = 500010;
	int pre[MAXN], afterl[MAXN], afterr[MAXN], pre1[MAXN], next[MAXN], pre[MAXN], c[MAXN], l[MAXN], r[MAXN];
	set<int> S; map<int, int> M;

	inline void solve(void) {
		kase = ScanInt();
		rep(_, kase) {
			printf("Case #%d: ", _); n = ScanInt();
			int tmp = 0; S.clear(); M.clear();
			rep(i,n) c[i] = ScanInt(), S.insert(c[i]);
			foreach(it, S) M[*it] = ++tmp; rep(i,n) c[i] = M[c[i]];
			rep(i,n) prev[i] = i - 1, next[i] = i + 1;
			for (int i = n; i >= 1; i--) {
				l[i] = prev[c[i]], r[i] = next[c[i]];
				next[prev[c[i]]] = next[c[i]], prev[next[c[i]]] = prev[c[i]];
			}
			pre[0] = 0, afterr[0] = 0, pre1[0] = 0;
			long long cnt = 0, cnt1 = 0;
			rep(i,n) {
				int L = l[i], R = r[i];
			}
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
