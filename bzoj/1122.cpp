//#define Debug
#include <cstdio>
#include <algorithm>
#include <list>
#define mp std::make_pair
namespace Solve {
	typedef std::list< std::pair<int, int> > II;
	const int MAXN = 2000010;
	int a[MAXN]; int n, p, q, x, y;

	void Input(void) {
		scanf("%d%d%d%d%d\n", &n, &p, &q, &x, &y);
		for (int i = 1; i <= n; i++) a[i + n] = a[i] = (getchar() == '+') ? 1 : -1;
	}

	int sum[MAXN];
	II Q;

	#define F(x) ((abs(x) + 1) >> 1)
	void Work(void) {
		for (int i = 1; i <= n << 1; i++) sum[i] = sum[i - 1] + a[i];
		int Ans = 0x7fffffff;
		for (int i = 1, delta = q - sum[n] - p; i <= n << 1; i++) {
			while (!Q.empty() && Q.back().first >= sum[i]) Q.pop_back();
			Q.push_back(mp(sum[i], i));
			if (i - Q.front().second + 1 > n) Q.pop_front();
			if (i > n) {
				int Min = Q.front().first - sum[i - n];
				int tmp;
				if (Min + p >= 0)
					tmp = (n * 2 - i) * y + F(delta) * x;
				else
					tmp = (n * 2 - i) * y + F(Min + p) * x + F((Min + p - 1) / 2 * 2 + delta) * x;
				Ans = std::min(Ans, tmp);
			}
		}
		printf("%d\n", Ans);
	}
	void solve(void) {
		Input();
		Work();
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
