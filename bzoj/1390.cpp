//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 105;
	const int inf = 1050000000;

	struct Point {
		int x, y;
		inline Point operator -(const Point& oth) const {
			Point ret;
			ret.x = x - oth.x;
			ret.y = y - oth.y;
			return ret;
		}
		inline int operator *(const Point& oth) const {
			return x * oth.y - oth.x * y;
		}
		inline bool operator ==(const Point& oth) const {
			return x == oth.x && y == oth.y;
		}
	}tree[MAXN], a[MAXN];

	int n, m, N;
	inline void Input(void) {
		scanf("%d%d", &n, &m); N = n;
		for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y);
		for (int j = 1; j <= m; j++) scanf("%d%d", &tree[j].x, &tree[j].y);
	}

	Point stack[MAXN], base;int top, k;

	#define sqr(a) ((a)*(a))
	#define dis(a, b) (sqr(a.x - b.x) + sqr(a.y - b.y))
	inline bool cmp(const Point& a, const Point& b) {
		int t = (a - base) * (b - base);
		if (t != 0) return t > 0; else return dis(a, base) <= dis(b, base);
	}

	inline void Make(void) {
		int x = inf, y = inf;
		for (int i = 1; i <= n; i++) if (a[i].y < y || (a[i].y == y && a[i].x < x)) {
			y = a[i].y, x = a[i].x; k = i;
		}
		base = a[k];
		std::sort(a + 1, a + n + 1, cmp);
		stack[++top] = a[1], stack[++top] = a[2];
		for (int i = 3; i <= n; i++) {
			while (top > 1 && (a[i] - stack[top]) * (stack[top - 1] - stack[top]) <= 0)
				top--;
			stack[++top] = a[i];
		}
		n = top; stack[n + 1] = stack[1];
	}

	bool In[MAXN];

	#define min(a, b) ((a)<(b)?(a):(b))
	#define max(a, b) ((a)>(b)?(a):(b))
/*
	inline bool InSeg(const Point& now, const Point& a, const Point& b) {
			return (now - a) * (now - b) == 0 && now.x >= min(a.x, b.x) && now.x <= max(a.x, b.x);
	}

	inline bool Check(const Point& a1, const Point& b1, const Point& a2, const Point& b2) {
		if (min(a1.x, b1.x) > max(a2.x, b2.x) || max(a1.x, b1.x) < min(a2.x, b2.x) ||
				min(a1.y, b1.y) > max(a2.y, b2.y) || max(a1.y, b1.y) < min(a2.y, b2.y))
			return false;
		return ((a1 - a2) * (b2 - a2)) * ((b1 - a2) * (b2 - a2)) <= 0 &&
			((a2 - a1) * (b1 - a1)) * ((b2 - a1) * (b1 - a2)) <= 0;
	}

	inline bool Gao(const Point& now) {
		bool cnt = false;
		Point tmp; tmp.x = now.x, tmp.y = 2000;
		for (int i = 1; i <= n; i++) if (stack[i].x != stack[i + 1].x) {
			if (InSeg(now, stack[i], stack[i + 1]))
				return true;
			if (InSeg(stack[i], now, tmp)) {
				cnt ^= (stack[i].x > stack[i + 1].x);
				continue;
			}
			if (InSeg(stack[i + 1], now, tmp)) {
				cnt ^= (stack[i + 1].x > stack[i].x);
				continue;
			}
			cnt ^= Check(now, tmp, stack[i], stack[i + 1]);
		}
		return cnt;
	}*/

	inline bool Gao(const Point& now) {
		for (int i = 1; i <= n; i++) {
			if ((now - stack[i]) * (stack[i + 1] - stack[i]) > 0)
				return false;
		}
		return true;
	}

	int cnt = 0; bool vis[MAXN];
	int map[MAXN][MAXN], Dis[MAXN][MAXN];

	inline void Graph(void) {
		n = N;
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= n; j++) if (i != j) {
				int ok = 1;
				for (int k = 1; k <= m; k++) if (vis[k]) {
					if ((tree[k] - a[i]) * (a[j] - a[i]) > 0) {
						ok = 0;
						break;
					}
				}
				map[i][j] = ok;
			}
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) if (i != j) {
				if (map[i][j] == 0)
					map[i][j] = MAXN;
				Dis[i][j] = map[i][j];
			}
	}

	inline void Floyd(void) {
		int ret = MAXN;
		for (int k = 1; k <= n; k++) {
			for (int j = 1; j < k; j++)
				for (int i = 1; i < k; i++) if (i != j)
					ret = min(ret, Dis[i][j] + map[j][k] + map[k][i]);
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n ;j++)
					Dis[i][j] = min(Dis[i][j], Dis[i][k] + Dis[k][j]);
		}
		printf("%d\n", ret * 20 + (m - cnt) * 111);
	}

	inline void solve(void) {
		Input();
		Make();
		for (int i = 1; i <= m; i++) {
			vis[i] = Gao(tree[i]);
			cnt += vis[i];
		}
		if (cnt == 0) {printf("%d\n", m * 111); return;}
		Graph();
		Floyd();
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
