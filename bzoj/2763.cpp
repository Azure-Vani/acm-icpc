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
	const int MAXN = 60010;

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

	int n, m, s, t, k;

	inline void Input(void) {
		n = ScanInt(), m = ScanInt(), k = ScanInt(), s = ScanInt(), t = ScanInt();
		while (m--) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
		}
	}

	int dis[12][MAXN];
	bool vis[12][MAXN];
	pair<int, int> d[MAXN * 12];

	int inf;

	inline void Spfa(void) {
		memset(dis, 55, sizeof dis);
		inf = dis[0][0];
		dis[0][s] = 0;
		int head = 1, tail = 1, sum = 1;
		d[1] = mp(0, s);
		vis[0][s] = true;
		while (sum) {
			int t = d[head].first, now = d[head].second; head++; if (head >= MAXN * 12 - 1) head = 1; sum--;
			for (Edge *p = a[now]; p; p = p->next) {
				if (dis[t][p->y] > dis[t][now] + p->z) {
					dis[t][p->y] = dis[t][now] + p->z;
					if (!vis[t][p->y]) {
						tail++, sum++; if (tail >= MAXN * 12 - 1) tail = 1;
						d[tail] = mp(t, p->y);
					}
				}
				if (t < k && dis[t + 1][p->y] > dis[t][now]) {
					dis[t + 1][p->y] = dis[t][now];
					if (!vis[t + 1][p->y]) {
						tail++, sum++; if (tail >= MAXN * 12 - 1) tail = 1;
						d[tail] = mp(t + 1, p->y);
					}
				}
			}
		}
	}

	inline void solve(void) {
		Input();
		Spfa();
		for (int i = k; i >= 0; i--) if (dis[i][t] != inf) {printf("%d\n", dis[i][t]); break;}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}