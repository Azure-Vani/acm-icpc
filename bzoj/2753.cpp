//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 2000020;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y, z; Edge *next;
		Edge(int y, int z, Edge *next):y(y), z(z), next(next){}
	}*a[MAXN];

	int n, m, h[MAXN];

	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) h[i] = ScanInt();
		while (m--) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			if (x[h] >= y[h]) a[x] = new Edge(y, z, a[x]);
			if (y[h] >= x[h]) a[y] = new Edge(x, z, a[y]);
		}
	}

	int belong[MAXN], tim[MAXN], instack[MAXN], stack[MAXN], top = 0, low[MAXN], cnt = 0, sum = 0;

	inline void Dfs(int u) {
		low[u] = tim[u] = ++cnt;
		stack[++top] = u; instack[u] = true;
		for (Edge *p = a[u]; p; p = p->next) {
			if (tim[p->y] == 0) {
				Dfs(p->y);
				low[u] = min(low[u], low[p->y]);
			} else if (instack[p->y])
				low[u] = min(low[u], tim[p->y]);
		}
		if (low[u] == tim[u]) {
			sum++;
			int j;
			do {
				j = stack[top--];
				belong[j] = sum;
				instack[j] = false;
			}while (j != u);
		}
	}

	struct Node {
		int x, y, z;
		inline friend bool operator <(const Node& a, const Node &b) {
			return a.z < b.z;
		}
		inline void Set(int x, int y, int z) {
			this->x = x, this->y = y, this->z = z;
		}
	}E[MAXN];

	int f[MAXN];
	inline int get(int x) {return x==f[x]?x:(f[x] = get(f[x]));}

	inline void MST(void) {
		int cnt = 0, num = 0; long long ret = 0;
		for (int i = 1; i <= n; i++) if (tim[i]) {
			num++;
			for (Edge *p = a[i]; p; p = p->next) {
				if (belong[i] != belong[p->y])
					E[++cnt].Set(0, p->y, p->z);
				else
					E[++cnt].Set(i, p->y, p->z);
			}
		}
		sort(E + 1, E + cnt + 1);
		for (int i = 1; i <= n; i++) f[i] = i;
		for (int i = 1; i <= cnt; i++) {
			int x = get(E[i].x), y = get(E[i].y);
			if (x == y) continue;
			ret = ret + (long long)E[i].z;
			f[x] = y;
		}
		printf("%d %lld\n", num, ret);
	}

	inline void solve(void) {
		Input();
		Dfs(1);
		MST();
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
