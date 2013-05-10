//#define Debug
#include <cstdio>
#include <algorithm>
#include <set>
namespace Solve {
	struct pair{int index, value; pair(int x, int y):index(x), value(y){}; friend bool operator <(pair a, pair b) {return a.value < b.value;}};
	typedef std::set<pair> VII;
	const int MAXN = 1005;
	const int inf = 1000000000;

	int n, a[MAXN], pos[MAXN];
	void Input(void) {
		scanf("%d", &n);
		VII T;
		for (int i = 1; i <= n; i++) {
			int t;
			scanf("%d", &t);
			T.insert(pair(i, t));
		}
		VII::iterator it; int l = n;
		for (it = T.begin(); it != T.end(); it++)
			a[it->index] = l, pos[l--] = it->index;
	}

	int f[MAXN][MAXN], s[MAXN][MAXN];
	void Dp(void) {
		a[n + 1] = n + 1;
		for (int i = 1; i <= n; i++) f[n + 1][i] = inf;
		f[n + 1][n + 1] = 0;

		for (int i = n; i >= 1; i--) {
			int s1 = 0;
			for (int j = 1; j < pos[i]; j++) s1 += (a[j] < i);
			int s2 = 0;
			for (int j = 1; j <= n + 1; j++) {
				s2 += (a[j] < i);
				f[i][j] = f[i + 1][j] + s1 + s2 + 2;
				s[i][j] = s[i + 1][j] + 1;
			}
			int add = 0;
			for (int j = pos[i] + 1; j <= n + 1; j++) {
				int tmp = f[i + 1][j] + add;
				if (tmp < f[i][pos[i]])
					f[i][pos[i]] = tmp, s[i][pos[i]] = s[i + 1][j];
				if (i > a[j])
					add += i - a[j];
			}
		}

		int mincost = inf, where = -1;
		for (int i = 1; i <= n + 1; i++)
			if (mincost > f[1][i]) {
				mincost = f[1][i];
				where = i;
			}
		printf("%d\n", s[1][where]);
	}
	void solve(void) {
		Input();
		Dp();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
