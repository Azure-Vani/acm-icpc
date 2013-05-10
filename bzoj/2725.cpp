//#define FILEIO

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#define INPUT "dream.in"
#define OUTPUT "dream.out"

#include <cstdio>
#include <queue>
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
	const int MAXN = 400010;
	const long long inf = 100000000000000000ll;

	typedef long long Int64;
	typedef pair<Int64, int> PII;
	typedef priority_queue<PII> QII;

	inline Int64 ScanInt(void) {
		Int64 r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10ll + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y;Int64 z; Edge *next, *opt; bool flag;
		Edge(int y, Int64 z, Edge *next, bool f = false):y(y), z(z), next(next), flag(f){}
	}*a[MAXN], *e[MAXN];

	struct _ {
		int x, y;
	}query[MAXN];

	int n, m, q, s, t;

	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt(); Int64 z = ScanInt();
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
			a[x]->opt = a[y];
			a[y]->opt = a[x];
		}
		s = ScanInt(), t = ScanInt(), q = ScanInt();
		for (int i = 1; i <= q; i++) {
			int x = ScanInt(), y = ScanInt();
			query[i].x = x;
			query[i].y = y;
		}
	}

	Int64 disx[MAXN], disy[MAXN];

	inline void Dijkstra(int u, Int64 dis[], QII& T) {
		for (int i = 0; i <= n; i++) dis[i] = inf;
		dis[u] = 0;
		T.push(mp(0, u));
		for (int i = 1; i <= n - 1; i++) {
			while (!T.empty() && -T.top().first > dis[T.top().second]) T.pop();
			if (T.empty()) break;
			int t = T.top().second; T.pop();
			for (Edge *p = a[t]; p; p = p->next) 
				if (dis[p->y] > dis[t] + p->z)
					T.push(mp(-(dis[p->y] = dis[t] + p->z), p->y));
		}
	}

	inline void Build(void) {
		for (int i = 1; i <= n; i++) {
			for (Edge *p = a[i]; p; p = p->next) if (disx[p->y] == disx[i] + p->z) {
				e[i] = new Edge(p->y, p->z, e[i], true);
				e[p->y] = new Edge(i, p->z, e[p->y]);
				e[i]->opt = e[p->y];
				e[p->y]->opt = e[i];
			}
		}
	}

	int low[MAXN], dnf[MAXN], tim = 0, cur = 0, belong[MAXN], List[MAXN], father[MAXN];
	bool vist[MAXN], inPath[MAXN];

	inline void Color(int u, int c) {
		belong[u] = c;
		for (Edge *p = e[u]; p; p = p->next) if (p->flag && belong[p->y] == 0) {
			Color(p->y, c);
		}
	}

	inline bool Bridge(int u, Edge *f) {
		bool ret = (u == t);
		low[u] = dnf[u] = ++tim;
		for (Edge *p = e[u]; p; p = p->next) {
			if (p->flag) {
				if (!dnf[p->y]) {
					bool r = Bridge(p->y, p->opt);
					ret |= r;
					if (r) low[u] = min(low[u], low[p->y]);
				}
			} else if (p != f && dnf[p->y]) {
				low[u] = min(low[u], dnf[p->y]);
			}
		}
		if (low[u] == dnf[u] && ret) {
			inPath[u] = true;
			Color(u, ++cur);
			List[cur] = u;
			if (f) father[u] = f->y;
		}
		return ret;
	}

	int pos[MAXN], other[MAXN]; Int64 Ans[MAXN];

	inline void Init(void) {
		for (int i = 1; i <= q; i++) {
			int &x = query[i].x, &y = query[i].y;
			if (belong[x] < belong[y]) swap(x, y);
			if (x == father[y]) {
				if (!pos[y]) 
					pos[y] = i;
				else
					other[i] = pos[y];
			} else
				Ans[i] = disx[t];
		}
	}

	QII T1, T2, Q;

	bool hash[MAXN];

	void Dfs(int u) {
		if (hash[u]) return;
		hash[u] = true;
		for (Edge *p = a[u]; p; p = p->next) if (father[p->y] != u && belong[p->y] < belong[u]) {
			Q.push(mp(-(disx[u] + p->z + disy[p->y]), belong[p->y]));
		}
		for (Edge *p = e[u]; p; p = p->next) if (p->flag && !inPath[p->y]) {
			Dfs(p->y);
		}
	}

	inline void solve(void) {
		Input();
		Dijkstra(s, disx, T1);
		Dijkstra(t, disy, T2);
		if (disx[t] == disx[0]) {
			for (int i = 1; i <= q; i++) puts("Infinity");
			return;
		}
		Build();
		Bridge(s, NULL);
		Init();
		for (int i = cur; i >= 1; i--) {
			while (!Q.empty() && Q.top().second > i) Q.pop();
			if (pos[List[i]]) {
				if (Q.empty()) Ans[pos[List[i]]] = -1; else Ans[pos[List[i]]] = -Q.top().first;
			}
			Dfs(List[i]);
		}
		for (int i = 1; i <= q; i++) {
			if (Ans[i] == -1)
				puts("Infinity");
			else {
				if (other[i]) {
					if (Ans[other[i]] == -1) puts("Infinity");
					else printf(LL "\n", Ans[other[i]]);
				}
				else printf(LL "\n", Ans[i]);
			}
		}
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
