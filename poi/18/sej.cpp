#include <cstdio>
#include <algorithm>
#include <vector>
#include <set>

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

using namespace std;

typedef long long Int64;

const int MAXN = 250020;
const int MAXM = 10000010;

int k; Int64 n, a[MAXN];
vector<Int64> factor, f;
set<Int64> S;

Int64 gcd(Int64 a, Int64 b) {return !b ? a : gcd(b, a % b);}

int main(void) {
	//freopen("in", "r", stdin);
	scanf(LL "%d", &n, &k);
	for (int i = 1; i <= k; i++) scanf(LL, a + i), a[i] = gcd(a[i], n);
	Int64 tmp = n;
	for (int i = 1; (Int64)i * i <= n; i++) {
		if (i != 1 && tmp % i == 0) {
			factor.push_back(i);
			while (tmp % i == 0) tmp /= i;
		}
		if (n % i == 0) {
			f.push_back(i);
			if ((Int64)i * i != n) f.push_back(n / i);
		}
	}
	Int64 Ans = 0; sort(f.begin(), f.end());
	if (tmp != 1) factor.push_back(tmp);
	for (int i = 1; i < k; i++) S.insert(a[i]);
	for (int i = f.size() - 1; i >= 0; i--) {
		Int64 now = f[i];
		if (S.find(now) != S.end()) continue;
		bool ok = true;
		for (int j = 0; j < (int)factor.size(); j++) {
			if (S.find(now * factor[j]) != S.end()) {ok = false; break;}
		}
		if (!ok) S.insert(now); else if (a[k] % now == 0) Ans = now;
	}
	printf(LL "\n", n / Ans);
	return 0;
}

