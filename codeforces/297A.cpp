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

	string a, b;

	inline void solve(void) {
		cin >>a>>b; int n = a.length(), m = b.length();
		int s = 0; foreach(it, b) if (*it == '1') {s = 1; break;}
		if (s == 0) {puts("YES"); return;}
		for (int i = 1; i <= min(n,m); i++) if (a.substr(n - i, i) == b.substr(0, i)) {
			int t = 0;
			for (int j = n - i; j < n; j++) if (a[j] == '1') t ^= 1;
			bool ok = true;
			for (int j = i; j < m; j++) {
				if (b[j] != '0' + t) {ok = false; break;}
				if (b[j] == '1') t ^= 1;
			}
			if (ok) {puts("YES"); return;}
		}
		puts("NO");
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
