//#define FILEIO

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

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
	const int MAXN = 500010;
	typedef long long Int64;
	const Int64 flag = 1000000000000000200ll;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y; Edge *next; int z;
		Edge(int y, Edge *next, int z):y(y), next(next), z(z){}
	}*a[MAXN];

	int n, m;Int64 p[MAXN];

	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) p[i] = ScanInt();
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			z = p[x] + p[y] - z;
			a[x] = new Edge(y, a[x], z);
			a[y] = new Edge(x, a[y], z);
		}
	}

	bool vis[MAXN], fail = false;
	Int64 delta[MAXN], sign[MAXN];
	vector<int> cur; Int64 now;

	inline void Dfs(int u, int f) {
		if (fail) return;
		vis[u] = true;
		cur.pb(u);
		for (Edge *p = a[u]; p; p = p->next) if (p->y != f) {
			if (!vis[p->y]) {
				delta[p->y] = p->z - delta[u];
				sign[p->y] = -sign[u];
				Dfs(p->y, u);
			} else {
				if (sign[u] == sign[p->y]) {
					Int64 tmp = (p->z - delta[u] - delta[p->y]) / (sign[u] + sign[p->y]);
					if ((now == flag || now == tmp) && (p->z - delta[u] - delta[p->y]) % (sign[u] + sign[p->y]) == 0)  {
						now = tmp;
					} else {
						fail = true;
						return;
					}
				} else {
					if (delta[u] + delta[p->y] != p->z) {
						fail = true;
						return;
					}
				}
			}
		}
	}

	inline void Work(void) {
		Int64 low = 0, high = 0;
		for (int i = 1; i <= n && !fail; i++) if (!vis[i]) {
			now = flag;
			cur.clear();
			sign[i] = 1;
			Dfs(i, 0);
			if (now == flag) {
				Int64 L = 0, R = p[i], s = 0; Int64 d = 0;
				foreach(it, cur) {
					int t = *it;
					if (sign[t] < 0) {
						L = max(L, delta[t] - p[t]);
						R = min(R, delta[t]);
					} else {
						L = max(L, -delta[t]);
						R = min(R, p[t] - delta[t]);
					}
					d += delta[t]; s += sign[t];
				}
				if (L > R) {fail = true; break;}
				if (s < 0) swap(L, R);
				low += d + s * L, high += d + s * R;
			} else {
				Int64 sum = 0;
				foreach(it, cur) {
					int t = *it;
					Int64 tmp = now * sign[t] + delta[t];
					if (tmp < 0 || tmp > p[t]) {
						fail = true;
						break;
					}
					sum += tmp;
				}
				low += sum, high += sum;
			}
		}
		if (fail) puts("NIE"); else
		printf(LL " " LL "\n", low, high);
	}

	inline void solve(void) {
		Input();
		Work();
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