//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>
#include <list>

#define rep(i,l,r) for(int i = (l); i <= (r); i++)
#define In(a, b, c) (((a) >= (b)) && ((a) <= (c)))

namespace Solve {
	const int MAXN = 1000010;

	struct Edge {
		int y, c; Edge *next;
		Edge(int y, int c, Edge *next):y(y), c(c), next(next){}
	}*a[MAXN];

	int ScanInt(void) {
		int c, r = 0, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0';
		while ( isdigit(d = getchar())) r = r * 10 + d - '0';
		return c=='-'?-r:r;
	}

	int n, m, parent[MAXN], dis[MAXN];
	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 2; i <= n; i++) {
			int y = ScanInt(), z = ScanInt();
			a[y] = new Edge(i, z, a[y]);
			parent[i] = y;
			dis[i] = z;
		}
	}

	struct pair {
		int value1, pos1, value2, pos2;
		inline void Update(const pair& oth, const int& a, const int &k) {
			int tmp = oth.value1 + k;
			if (tmp > value1) {
				value2 = value1;
				pos2 = pos1;
				value1 = tmp;
				pos1 = a;
			} else
			if (tmp > value2) {
				value2 = tmp;
				pos2 = a;
			}
		}
	}f[MAXN];

	int d[MAXN], up[MAXN], List[MAXN];
	inline void Bfs(void) {
		int head = 1, tail = 1; d[1] = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next)
				d[++tail] = p->y;
		}
		for (int i = n; i >= 2; i--) {
			int u = d[i], t = parent[u];
			f[t].Update(f[u], u, dis[u]);
		}
		for (int i = 1; i <= n; i++) {
			int u = d[i];
			for (Edge *p = a[u]; p; p = p->next) {
				if (p->y == f[u].pos1)
					up[p->y] = std::max(f[u].value2, up[u]) + p->c;
				else
					up[p->y] = std::max(f[u].value1, up[u]) + p->c;
			}
			List[u] = std::max(up[u], f[u].value1);
		}
	}

	int Min[MAXN], Max[MAXN];
	int hmin, hmax, tmin, tmax;
	inline void Dp(void) {
		int ret = 1, l = 1;
		hmin = hmax = 1;
		for (int i = 1; i <= n; i++) {
			while (tmin >= hmin && List[Min[tmin]] > List[i])
				tmin--;
			while (tmax >= hmax && List[Max[tmax]] < List[i])
				tmax--;
			Min[++tmin] = i;
			Max[++tmax] = i;
			while (List[Max[hmax]] - List[Min[hmin]] > m && l <= i) {
				if (Max[hmax] <= l) hmax++;
				if (Min[hmin] <= l) hmin++;
				l++;
			}
			if (i - l + 1 > ret) ret = i - l + 1;
		}
		printf("%d\n", ret);
	}

	void solve(void) {
		Input();
		Bfs();
		Dp();
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
