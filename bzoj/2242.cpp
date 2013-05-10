//#define Debug
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
namespace Solve {
	typedef long long Int65;
	
	int Mod;

	inline int Pow(int a, int n) {
		int r = 1;
		while (n) {if (n&1) r = (Int65) r * a % Mod; a = (Int65) a * a % Mod; n >>= 1;}
		return r;
	}

	inline int Ex_gcd(int a, int b, int& x, int& y) {
		if (!b) {
			x = 1, y = 0;
			return a;
		}
		int r = Ex_gcd(b, a % b, x, y);
		int t = x; x = y, y = t - a / b * y;
		return r;
	}

	inline int _E(int a, int b) {
		int x, y;
		int t = Ex_gcd(a, Mod, x, y);
		if (b % t) return -1;
		x = (Int65) x * b / t % Mod;
		return x < 0 ? (x + Mod) : x;
	}
	
	const int MOD = 1200007;
	class HASH {public:
		struct _{
			int index, value;_ *next;
			_(int i, int v):index(i), value(v){}
		}*a[MOD], *b[MOD];
		inline void Insert(int value, int index) {
			int t = index % MOD;
			_* tmp = new _(index, value);
			if (b[t] == NULL) a[t] = b[t] = tmp;
			else a[t]->next = tmp, a[t] = tmp;
		}
		inline int Find(int index) {
			int t = index % MOD;
			for (_* p = a[t]; p; p = p->next) if (p->index == index)
				return p->value;
			return -1;
		}
		inline void clear(void) {
			memset(a, NULL, sizeof a); memset(b, NULL, sizeof a);
		}
	}T;

	inline int BabyStep(int a, int b) {
		T.clear(); b %= Mod; if (a % Mod == 0) return (b==0)?1:((b==1)?0:-1);
		int m = (int)ceil(sqrt(Mod));
		int tmp = 1; T.Insert(0, 1);
		for (int i = 1; i <= m; i++) 
			tmp = (Int65) tmp * a % Mod, T.Insert(i, tmp);
		int opp = _E(tmp, 1), gss = b;
		for (int i = 0, d; i <= m; i++) {
			if ((d = T.Find(gss)) != -1)
				return i * m + d;
			gss = (Int65) gss * opp % Mod;
		}
		return -1;
	}
	
	inline void solve(void) {
		int type, ncase; scanf("%d%d", &ncase, &type);
		while (ncase--) {
			int a, b, r; scanf("%d%d%d", &a, &b, &Mod);
			if (type == 1) r = Pow(a, b);
			else if (type == 2) r = _E(a, b);
			else r = BabyStep(a, b);
			if (r != -1) printf("%d\n", r); else puts("Orz, I cannot find x!");
		}
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
