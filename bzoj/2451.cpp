//#define FILEIO

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>
#include <map>
#include <cstdlib>

#define rep(i,l,r) for(int i = (l); i <= (r); i++)
#define In(a, b, c) (((a) >= (b)) && ((a) <= (c)))

namespace Solve {
	typedef long long Int64;
	const int MAXN = 52;
	int n, fim[MAXN];;
	Int64 neighbor[MAXN], N = 0;
	std::map<Int64, Int64> T, G;

	inline void Input(void) {
		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++) fim[i] = i;
		for (int i = 1; i <= n; i++) std::swap(fim[i], fim[rand() % n + 1]);
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= n; j++)
				if ('1' == getchar()) neighbor[fim[i]] |= (1ll << fim[j]);
			G[1ll << fim[i]] = neighbor[fim[i]];
			scanf("\n");
		}
	}

	Int64 Dfs(Int64 S) {
		if (!S) return 1;
		Int64 ret = T[S], pos = 1ll, next = S, d = 0, now, tmp = S, debug = S;
		if (ret > 0) return ret; ret = 1ll;
		for (;S; S >>= 1, pos <<= 1) if (S&1ll) {
			now = G[pos] & tmp;
			if (now == (tmp ^ pos)) ret <<= 1, next ^= pos;
			else if (!now) ++d, next ^= pos;
		}
		if (!next) return T[debug] = ret + d;
		pos = next & -next;
		ret = ret * (Dfs(next & G[pos]) + Dfs(next ^ pos)) + d;
		N++;
		return T[debug] = ret;
	}

	inline void solve(void) {
		Input();
		printf(LL "\n", Dfs((1ll << (n + 1)) - 2));
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
