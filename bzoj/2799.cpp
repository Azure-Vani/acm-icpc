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
	const int MAXN =1000010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge* next):y(y), next(next){}
	}*a[MAXN];

	int n, c[MAXN], root, v[MAXN];
	int Ans[MAXN], head = 1, tail = 0;
	pair<int, int> d[MAXN];

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) {
			int p = ScanInt(), t = ScanInt();
			c[t] = i; v[i] = t;
			Ans[i] = t;
			if (i != p) a[p] = new Edge(i, a[p]); else root = i;
		}
	}

	inline void Work(void) {
		c[n] = root; v[root] = n, Ans[root] = n;
		int flag = 0;
		for (int i = n; i >= 1; i--) {
			if (c[i]) {
				int tmp = c[i];
				for (Edge *p = a[tmp]; p; p = p->next) if (!v[p->y]) {
					d[++tail] = mp(p->y, i - 1);
				}
			} else {
				int w = 0;
				while (head <= tail && d[head].second >= i) {
					flag++, w = d[head++].first;
					for (Edge *p = a[w]; p; p = p->next) d[++tail] = mp(p->y, i - 1);
				}
				if (flag == 1) Ans[w] = i;
				flag--;
			}
		}
		for (int i = 1; i <= n; i++) printf("%d\n", Ans[i]);
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
