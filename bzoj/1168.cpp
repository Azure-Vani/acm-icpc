//#define Debug
#include <cstdio>
#include <algorithm>
#include <vector>
namespace Solve {
	const int MAXN = 25;
	const int inf = 2000000000;
	struct _{int x, y;_(int a, int b):x(a), y(b){} _(){}} a[MAXN], c[MAXN];
	std::vector<_> T;
	bool cmp(const _& a, const _& b){return a.x < b.x;}
	int n, Ax = inf, Ay = inf, S = 0, deltax = 0, deltay = 0;

	void Dfs(int now, int X, int Y) {
		if (now == n + 1) {
			T.push_back(_(X, S - Y));
			return;
		}
		Dfs(now + 1, a[now].x + X, a[now].y + Y);
		Dfs(now + 1, X, Y);
	}
	void solve(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", &c[i].x);
		for (int i = 1; i <= n; i++) scanf("%d", &c[i].y);
		int N = 0;
		for (int i = 1; i <= n; i++) {
			if (c[i].x && c[i].y) a[++N] = c[i], S += a[N].y;
			else deltax += c[i].x, deltay += c[i].y;
		}
		n = N;
		Dfs(1, 0, 0);
		std::sort(T.begin(), T.end(), cmp);
		int max = -1;
		std::vector<_> Q;
		for (int i = T.size() - 1; i >= 0; i--)
			if (T[i].y > max) {
				Q.push_back(T[i]);
				max = std::max(max, T[i].y);
			}
		std::reverse(Q.begin(), Q.end());
		S = inf;
		for (int i = 1; i < Q.size(); i++){
			if ((long long) (Q[i - 1].x + Q[i].y + 2) < S) {
				S = Q[i - 1].x + Q[i].y + 2;
				Ax = Q[i - 1].x + 1, Ay = Q[i].y + 1;
			}
		}
		printf("%d %d\n", Ax + deltax, Ay + deltay);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
