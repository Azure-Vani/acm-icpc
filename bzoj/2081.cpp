//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <set>
#include <vector>
#define Rev(x) (n - (x) + 1)
namespace Solve {
	typedef long long Int64;
	typedef std::set<Int64> II;
	typedef std::vector<int> VII;
	const int MAXN = 200020;
	const int base = 13331;
	const Int64 Mod = 799999999;
	int a[MAXN], rev_a[MAXN], n;
	Int64 pow[MAXN];

	void Input(void) {
		scanf("%d", &n); pow[0] = 1;
		for (int i = 1; i <= n; i++) scanf("%d", a + i), rev_a[Rev(i)] = a[i], pow[i] = (pow[i - 1] * base) % Mod;
	}

	Int64 hash[MAXN], rev_hash[MAXN];
	inline void MakeHash(int a[], Int64 ret[]) {
		for (int i = 1; i <= n; i++) ret[i] = (ret[i - 1] * base + a[i]) % Mod;
	}
	
	inline Int64 Sum(int l, int r, Int64 hash[]) {
		Int64 ret = hash[r] - hash[l - 1] * pow[r - l + 1] % Mod;
		while (ret < 0) ret += Mod;
		return ret;
	}

	void Work(void) {
		VII Ans; int max = 0;II T;
		for (int k = 1; k <= n; k++, T.clear()) {
			for (int i = 1; i + k - 1 <= n; i += k) {
				Int64 h1 = Sum(i, i + k - 1, hash);
				Int64 h2 = Sum(Rev(i + k - 1), Rev(i), rev_hash);
				T.insert(std::min(h1, h2));
			}
			int tmp = T.size();
			if (tmp > max)
				Ans.clear(), Ans.push_back(k), max = tmp;
			else if (tmp == max)
				Ans.push_back(k);
		}
		printf("%d %d\n", max, Ans.size());
		for (int i = 0; i < Ans.size(); i++) printf("%d ", Ans[i]);
		puts("");
	}

	void solve(void) {
		Input();
		MakeHash(a, hash);
		MakeHash(rev_a, rev_hash);
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
