//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	typedef long long Int64;
	const Int64 mod1 = 100001009;
	const Int64 mod2 = mod1 + 17;
	const Int64 base1 = 10003;
	const Int64 base2 = 170721;
	const int MAXN = 1000020;

	int a[MAXN], n; char ch[MAXN];
	Int64 sum1[MAXN], sum2[MAXN], pow1[MAXN], pow2[MAXN];

	inline void Input(void) {
		scanf("%d\n", &n); scanf("%s\n", ch); pow1[0] = pow2[0] = 1;
		for (int i = 1; i <= n; i++) a[i] = ch[i - 1] - 'a' + 1;
		for (int i = 1; i <= n; i++) {
			pow1[i] = pow1[i - 1] * base1 % mod1;
			pow2[i] = pow2[i - 1] * base2 % mod2;
			sum1[i] = (sum1[i - 1] * base1 % mod1 + a[i]) % mod1;
			sum2[i] = (sum2[i - 1] * base2 % mod2 + a[i]) % mod2;
		}
	}

	pair<Int64, Int64> Get(int l, int r) {
		pair<Int64, Int64> ret;
		ret.first = (sum1[r] - (sum1[l - 1] * pow1[r - l + 1] % mod1)) % mod1;
		ret.second = (sum2[r] - (sum2[l - 1] * pow2[r - l + 1] % mod2)) % mod2;
		if (ret.first < 0) ret.first += mod1;
		if (ret.second < 0) ret.second += mod2;
		return ret;
	}

	inline bool Equal(int l1, int r1, int l2, int r2) {
		pair<Int64, Int64> A = Get(l1, r1);
		pair<Int64, Int64> B = Get(l2, r2);
		return A == B;
	}

	inline void Work(void) {
		int Ans = 0;
		for (int L = (n >> 1), last = 1; L >= 0; L--) {
			int j = min(last + 2, (n - L * 2) >> 1);
			while (j > 0 && !Equal(L + 1, L + j, n - L - j + 1 ,n - L)) j--;
			if (Equal(1, L, n - L + 1, n)){
				Ans = max(Ans, j + L);
			}
			last = j;
		}
		printf("%d\n", Ans);
	}

	inline void solve(void) {
		Input();
		Work();
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