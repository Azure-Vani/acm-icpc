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

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	map<int, int> a, b, c;

	inline void solve(void) {
		int n = ScanInt(), m = ScanInt(), k = ScanInt();
		rep(i,n) {int t = ScanInt(); a[1000000000 - t]++;}
		rep(i,m) {int t = ScanInt(); b[1000000000 - t]++;}
		foreach(it, a) c[it->first] = a[it->first] - b[it->first];
		foreach(it, b) c[it->first] = a[it->first] - b[it->first];
		long long s = 0;
		foreach(it, c) {
			s = s + (long long)it->second; 
			if (s > 0) {puts("YES"); return;}
		}
		puts("NO");
	}
}

int main(void) {
	#ifdef FILEIO
//		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
