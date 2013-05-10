//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 10000009;
	const int Mod = 20101009;
	
	int n, m;
	
	int prime[MAXN], miu[MAXN], cnt; bool tag[MAXN];
	void GetPrime(int n) {
		tag[1] = true;
		miu[1] = 1;
		for (int i = 2; i <= n; i++) {
			if (!tag[i]) prime[++cnt] = i, miu[i] = -1;
			for (int j = 1; j <= cnt && i * prime[j] <= n; j++) {
				tag[prime[j] * i] = true;
				if (i % prime[j] == 0) {
					miu[i * prime[j]] = 0;
					break;
				}else
					miu[i * prime[j]] = -miu[i];
			}
		}
		for (int i = 1; i <= n; i++) miu[i] = ((Int64) miu[i] * i * i + miu[i - 1]) % Mod;
	}

	inline Int64 Cal(int n, int m) {
		Int64 ret = 0;
		for (int start = 1, end; start <= m; start = end + 1) {
			Int64 v0 = n / start, v1 = m / start;
			end = std::min(n / v0, m / v1);
			Int64 sum = miu[end] - miu[start - 1];
			Int64 tmp = ((v0 * (v0 + 1) >> 1) % Mod) * ((v1 * (v1 + 1) >> 1) % Mod) % Mod;
			ret = (ret + sum * tmp) % Mod;
		}
		return ret;
	}

	void solve(void) {
		scanf("%d%d", &n, &m);
		if (n < m) std::swap(n, m);
		GetPrime(n);
		Int64 Ans = 0;
		for (int start = 1, end; start <= m; start = end + 1) {
			int v0 = n / start, v1 = m / start;
			Int64 tmp = Cal(v0, v1);
			end = std::min(n / v0, m / v1);
			Int64 sum = ((Int64)(end + start) * (end - start + 1) >> 1) % Mod;
			Ans = (Ans + tmp * sum) % Mod;
		}
		while (Ans < 0) Ans += Mod;
		printf(LL "\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
