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
#include "cliclib.h"

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 30010;

	int n, f[100][MAXN]; bool vis[100][MAXN];

	int fim[MAXN], list[MAXN], cnt;

	int Dfs(int x, int y) {
		if (x + y >= n) return 0;
		if (vis[fim[x]][y]) return f[fim[x]][y];
		int &tmp = f[fim[x]][y]; vis[fim[x]][y] = true;
		int l1 = Dfs(1, x + y);
		int l2 = Dfs(x << 1, y);
		int l3 = Dfs(x * 3,  y);
		if (l1 == 0) return tmp = 1;
		if (l2 == 0) return tmp = 2;
		if (l3 == 0) return tmp = 3;
		return tmp = 0;
	}

	int x = 1, y = 0;

	inline void Gao(int a) {
		if (a == 1) y += x, x = 1;
		if (a == 2) x <<= 1;
		if (a == 3) x *= 3;
	}

	inline void solve(void) {
		n = inicjuj();
		for (int i = 1; i <= n; i++) {
			int t = i;
			while (t % 2 == 0) t /= 2;
			while (t % 3 == 0) t /= 3;
			if (t == 1) list[++cnt] = t, fim[i] = cnt;
		}
		Dfs(1, 0);
		while (true) {
			int t = f[fim[x]][y];
			alojzy(t);
			Gao(t);
			t = bajtazar();
			Gao(t);
		}
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

