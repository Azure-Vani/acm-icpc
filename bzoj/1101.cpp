//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
const int MAXN = 50001;
int miu[MAXN], Prime[MAXN], l = 0;
int tag[MAXN];
void GetPrime(void) {
	for (int i = 2; i < MAXN; i++) {
		if (!tag[i]) Prime[++l] = i, tag[i] = i;
		for (int j = 1; j <= l && Prime[j] * i < MAXN; j++) {
			tag[i * Prime[j]] = Prime[j];
			if (i % Prime[j] == 0)
				break;
		}
	}
}

inline int Gao(int u) {
	int s = 1;
	while (u != 1) {
		if (tag[u] == tag[u / tag[u]]) return 0;
		u /= tag[u];
		s *= -1;
	}
	return s;
}

void GetMiu(void) {
	miu[1] = 1;
	for (int i = 2; i < MAXN; i++) miu[i] += miu[i - 1] + Gao(i);
}

namespace Solve {
	long long Ans;
	void Work(int a, int b, int k) {
		a /= k, b /= k;
		int N = a, delta;
		for (int i = 1; i <= N; i = delta + 1) {
			delta = std::min(a / (a / i), b / (b / i));
			Ans += (long long)(a / i) * (b / i) * (miu[delta] - miu[i - 1]);
		}
	}

	inline int ScanInt(void) {
		int c, r;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = (r << 1) + (r << 3) + c - '0';
		return r;
	}

	void solve(void) {
		int a, b, k; scanf("%d%d%d", &a, &b, &k);
		if (a > b) std::swap(a, b);
		Ans = 0;
		Work(a, b, k);
		printf("%lld\n", Ans);
	}
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w" ,stdout);
	#endif
	GetPrime();
	GetMiu();
	int _; scanf("%d", &_);
	while (_--) 
		Solve::solve();
	return 0;
}
