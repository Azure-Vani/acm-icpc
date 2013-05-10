//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <map>

#define pb push_back
#define mp make_pair
#define foreach(i,n) for(__typeof(n.begin()) (i) = n.begin(); (i) != n.end(); ++(i))

using namespace std;
typedef long long Int64;

namespace Solve {
	const int MAXN = 19; 
	const int MAXP = 5200;
	const int Mod = 12000007;

	Int64 pow[MAXN], l, r, A, B, cur;

	std::map<Int64, Int64> f[19];

	int cnt = 0;
	Int64 Ans = 0;

	inline Int64 Digit(Int64 u) {
		if (u == 0) return 0;
		register Int64 ret = 1;
		while (u) ret *= u % 10, u /= 10;
		return ret;
	}

	inline Int64 Cal(Int64 L, Int64 R, Int64 p) {
		Int64 ret = 0;
		while (L <= R) {
			register Int64 len = 0, pow = 1;
			while (true) {
				register Int64 t_pow = pow * 10;
				if (L + t_pow - 1 <= R && L % t_pow == 0) 
					len++, pow = t_pow;
				else break;
			}
			Int64 pre = Digit(L / pow);
			L += pow;
			if (pre && !(p % pre)) ret += f[len][p / pre];
		}
		return ret;
	}

	void Product(Int64 p, int fac) {
		if (p > B) return;
		cnt++; cur = p;
		l = (long long)ceil((double)A / (double)p), r = (long long)floor((double)B / (double)p);
		Ans += Cal(l, r, p);
		if (fac <= 2) Product(p * 2, 2);
		if (fac <= 3) Product(p * 3, 3);
		if (fac <= 5) Product(p * 5, 5);
		if (fac <= 7) Product(p * 7, 7);
	}

	inline void Initialize(void) {
		f[0][1] = 1;
		for (int i = 0; i <= 17; i++) {
			for (std::map<Int64, Int64>::iterator it = f[i].begin(); it != f[i].end(); it++) {
				for (int j = 1; j <= 9; j++) 
					f[i + 1][j * it->first] += it->second;
			}
		}
	}
	
	inline void solve(void) {
		scanf("%lld%lld", &A, &B);
		Initialize();
		Product(1, 2);
		printf("%lld\n", Ans);
	}
}

int main(void) {
#ifdef FILEIO
	freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
#endif
	Solve::solve();
	return 0;
}
