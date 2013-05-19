//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <map>

#define mp make_pair
#define pb push_back
#define cl(a) memset(a,0,sizeof a);
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {
	const int MAXN = 200;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y; Edge *next, *opt; bool flag;
		Edge(int y, Edge *next):y(y), next(next){flag = true;}
	}*e[MAXN];

	pair<int, int> a[1010];
	map<pair<int, int>, int> M;
	vector<int> Ans;

	int n, m, vis[MAXN], x, y, tmp[MAXN];

	void Dfs(int u) {
		vis[u] = true;
		for (Edge *p = e[u]; p; p = p->next) if (!vis[p->y]) Dfs(p->y);
	}

	inline bool check(int u, int v) {
		return (u == x && v == y) || (u == y && v == x);
	}

	void findCircle(int u) {
		tmp[u] = 1;
		for (Edge *p = e[u]; p; p = p->next) if (tmp[p->y] == 0 && !check(u, p->y)) {
			findCircle(p->y);
		}
	}

	bool incircle[MAXN]; int cur;

	inline void find(int u) {
		if (cur == u && tmp[u] == true) incircle[u] = true;
		if (tmp[u]) return;
		tmp[u] = 1;
		for (Edge *p = e[u]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			find(p->y);
			p->opt->flag = true;
		}
	}

	inline void solve(void) {
		n = ScanInt(), m = ScanInt();
		rep(i,m) {
			x = ScanInt(), y = ScanInt();
			if (x > y) swap(x, y);
			a[i].first = x, a[i].second = y;
			M[mp(x,y)]++;
			e[x] = new Edge(y, e[x]);
			e[y] = new Edge(x, e[y]);
			e[x]->opt = e[y], e[y]->opt = e[x];
		}
		bool ok = false, noEdge = true; int g3 = 0, g2 = 0;
		Dfs(1);
		for (int i = 2; i <= n; i++) {
			cur = i;
			cl(tmp); tmp[1] = true; find(i);
		}
		for (int i = 2; i <= n; i++) if (M.count(mp(1,i))) {
			int t = M[mp(1,i)];
			if (t >= 3) g3++;
			if (t >= 2) g2++;
		}
		for (int i = 2; i <= n; i++) if (vis[i]) {
			if (!M.count(mp(1, i))) {
				Ans.pb(i);
			} else {
				noEdge = false;
				x = 1, y = i;
				int t = M[mp(1, i)];
				cl(tmp);
				findCircle(i);
				if (tmp[1]) ok = true;
				if (t > 1 && incircle[i]) ok = true;
				if (t & 1) {
					Ans.pb(i);
				} else {
					ok = true;
					if (tmp[1] || (g2 - (t >= 2)) >= 1 || incircle[i]) Ans.pb(i);
				}
			}
		}
		if (g3 >= 2) ok = true;
		if (ok || noEdge) printf("1 ");
		foreach(it, Ans) printf("%d ", *it); puts("");
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

