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
	typedef long long Int64;
	const int MAXN = 100;

	Int64 p[MAXN], a[6], ans[6]; int n;

	inline void solve(void) {
		cin >> n;
		for (int i = 1; i <= n; i++) cin >>p[i];// sort(p + 1, p + n + 1);
		for (int i = 1; i <= 5; i++) cin >>a[i];
		Int64 sum = 0;
		for (int i = 1; i <= n; i++) {
			sum += p[i];
			for (int j = 5; j >= 1; j--) {
				ans[j] += sum / a[j];
				sum %= a[j];
			}
		}
		for (int i = 1; i <= 4; i++) cout <<ans[i]<< ' '; cout <<ans[5]<<endl;
		cout <<sum<<endl;
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
