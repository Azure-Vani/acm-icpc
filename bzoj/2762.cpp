//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <set>
#include <map>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 1000010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct fac{
		long long x, y;
		fac(long long x, long long y):x(x), y(y){}
		fac(){}
		friend bool operator <(const fac& a, const fac& b) {
			if (a.y * b.y < 0)
			return (long long) a.x * b.y > (long long) b.x * a.y;
			else
			return (long long) a.x * b.y < (long long) b.x * a.y;
		}
	};

	struct Query {
		int type; int dir; int c;
		fac a;
	}Q[MAXN];

	set<fac> SII; map<fac, int> MII;

	int n, sum = 0, fim[MAXN], L = 0;

	inline void Input(void) {
		n = ScanInt();
		int cnt = 0;
		for (int i = 1; i <= n; i++) {
			int cc; while (!isupper(cc = getchar()));
			if (cc == 'A') {
				Q[i].type = 1;
				int a = ScanInt(), b = ScanInt(), c = ScanInt();
				if (a == 0) {
					Q[i].dir = -1;
					Q[i].c = (b > c);
				}
				if (a < 0) {
					Q[i].a = fac(c - b, a);
				}
				if (a > 0) {
					Q[i].a = fac(c - b, a);
					Q[i].dir = 1;
				}
				fim[++cnt] = i;
			}
			if (cc == 'D') {
				Q[i].type = 2;
				Q[i].dir = ScanInt();
			}
			if (cc == 'Q') {
				Q[i].type = 3;
				Q[i].a = fac(ScanInt(), 1);
			}
		}
		for (int i = 1; i <= n; i++) if (Q[i].type != 2 && Q[i].dir != -1) SII.insert(Q[i].a);
		foreach(it, SII) MII[*it] = ++L;
		for (int i = 1; i <= n; i++) if (Q[i].type != 2 && Q[i].dir != -1) Q[i].c = MII[Q[i].a];
	}

	int l1[MAXN], l2[MAXN];

	inline void insert(int a[], int u, int d) {
		for (;u <= L; u += u&-u) a[u] += d;
	}

	inline int Cal(int a[], int u) {
		int ret = 0; for (;u;u -= u&-u) ret += a[u];
		return ret;
	}

	bool vis[MAXN];

	inline void Work(void) {
		for (int i = 1; i <= n; i++) {
			if (Q[i].type == 1) {
				if (Q[i].dir == 0) {
					insert(l2, L - Q[i].c + 1, 1);
				}
				if (Q[i].dir == 1) {
					insert(l1, Q[i].c, 1);
				}
				if (Q[i].dir == -1)
					sum += Q[i].c;
			}
			if (Q[i].type == 2) {
				int t = fim[Q[i].dir];
				if (vis[t]) continue; vis[t] = true;
				if (Q[t].dir == 0) {
					insert(l2, L - Q[t].c + 1, -1);
				}
				if (Q[t].dir == 1) {
					insert(l1, Q[t].c, -1);
				}
				if (Q[t].dir == -1) sum -= Q[t].c;
			}
			if (Q[i].type == 3) {
				int A1 = Cal(l2, L - Q[i].c);
				int A2 = Cal(l1, Q[i].c - 1);
				printf("%d\n", A1 + A2 + sum);
			}
		}
	}

	inline void solve(void) {
		Input();
		Work();
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