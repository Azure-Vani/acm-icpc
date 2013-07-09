//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <iostream>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 1000010;

	int n, r, a[MAXN];

	inline pair<int, int> gcd(int a, int b) {
		if (!b) {
			if (a == 1) {
				Solve::a[0] = 1;
				return mp(0 ,a - 1);
			} else return mp(-1, -1);
		}
		pair<int, int> ret = gcd(b, a % b);
		if (ret.first == -1) return mp(-1, -1);
		int times = ret.first, t = ret.second;
		Solve::a[times + 1] = a / b;
		return mp(times + 1, t + a / b);
	}

	inline void solve(void) {
		cin >>n>>r;
		if (n == 1 && r == 1) {
			puts("0\nT");
			return;
		}
		int Ans = 1000000, pos; bool ok = false;
		pair<int, int> ret;
		for (int last = 1; last <= r; last++) {
			ret = gcd(r, last);
			if (ret.first == -1) continue;
			if (ret.second == n && (ret.second - ret.first - 1) < Ans) 
				Ans = ret.second - ret.first - 1, pos = last, ok = true;
		}
		ret = gcd(r, pos);
		if (ok) {
			cout <<Ans<<endl;
			char ch[] = {'B', 'T'}; a[1]--;
			for (int i = 0; i <= n - Ans - 1; i++) {
				int t = (i + 1) & 1;
				for (int j = 1; j <= a[i]; j++) putchar(ch[t]);
			}
		}else puts("IMPOSSIBLE");
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
