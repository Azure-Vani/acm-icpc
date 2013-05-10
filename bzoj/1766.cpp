//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 105;
	const int MAXM = 2000020;
	int n, A;

	struct Point {
		int x, y;
		inline friend bool operator <(const Point& a, const Point& b) {
			if (a.x == b.x) return a.y < b.y; else return a.x < b.x;
		}
	}a[MAXN];

	inline void Input(void) {
		scanf("%d%d", &n, &A);
		for (int i = 1; i <= n; i++) {
			scanf("%d%d", &a[i].x, &a[i].y);
		}
		std::sort(a + 1, a + n + 1);
	}

	int f[MAXN][MAXN][MAXN], vis[MAXN][MAXN][MAXN];

	inline int Dfs(int l, int r, int h) {
		if (l > r) return 0;
		while (l <= r && a[l].y <= a[h].y) l++;
		while (r >= l && a[r].y <= a[h].y) r--;
		if (vis[l][r][h]) return f[l][r][h];
		vis[l][r][h] = true;
		int &ret = f[l][r][h];
		bool ok = false;
		int minx = 0x7fffffff, maxx = -1, maxy = -1;
		for (int i = l; i <= r; i++) if (a[i].y > a[h].y) {
			ok = true;
			minx = std::min(minx, a[i].x);
			maxx = std::max(maxx, a[i].x);
			maxy = std::max(maxy, a[i].y);
		}
		if (!ok) return ret = 0;
		if ((maxx - minx) * maxy <= A) return ret = 1;
		ret = 0x7fffffff;
		for (int k = l; k < r; k++) {
			int v1 = Dfs(l, k, h);
			int v2 = Dfs(k + 1, r, h);
			ret = std::min(ret, v1 + v2);
		}
		double H = A / (a[r].x - a[l].x);
		if (H > a[h].y) {
			int L = n + 1, R = 0, maxh = -1, what = 0;
			for (int i = l; i <= r; i++) if (a[i].y > H) {
				L = std::min(L, i); R = std::max(R, i);
			}else if (a[i].y > maxh) maxh = a[i].y, what = i;
			int t = Dfs(L, R, what);
			if (t + 1 < ret) ret = t + 1;
		}
		return ret;
	}

	inline void solve(void) {
		Input();
		a[++n] = a[1]; a[n].y = -1;
		std::sort(a + 1, a + n + 1);
		printf("%d\n", Dfs(2, n, 1));
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
