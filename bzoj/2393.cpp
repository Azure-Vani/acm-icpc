//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 1200;

	inline Int64 gcd(Int64 a, Int64 b) {return !b?a:gcd(b,a%b);}
	
	Int64 Ans = 0, Limit, List[MAXN];int n;
	
	void Dfs(int u, Int64 Now, bool flag) {
		if (u > n) {
			if (Now == 1) return;
			int c = flag?1:-1;
			Ans += c * Limit / Now;
			return;
		}
		Dfs(u + 1, Now, flag);
		Int64 lcm = List[u] * Now / gcd(List[u], Now);
		if (lcm > Limit) return;
		Dfs(u + 1, lcm, flag ^ 1);
	}

	inline void Product(int L) {
		for (int i = 0; i < (1 << L); i++) {
			n++; Int64 pow = 1;
			for (int j = 0; j < L; j++) {
				if (i & (1 << j)) List[n] += 2 * pow;
				else List[n] += 9 * pow;
				pow *= 10ll;
			}
		}
	}

	Int64 L, R;
	inline void solve(void) {
		scanf("%lld%lld", &L, &R);
		for (int i = 1; i <= 9; i++) 
			Product(i);
		std::sort(List + 1, List + n + 1);
		std::reverse(List + 1, List + n + 1);
		Int64 delta = 0;
		if (L > 1) {
			Limit = L - 1;
			Dfs(1, 1, false);
			delta = Ans; Ans = 0;
		}
		Limit = R;
		Dfs(1, 1, false);
		printf("%lld\n", Ans - delta);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
