#define FILEIO

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#define INPUT "dream6.in"
#define OUTPUT "op"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <queue>
#include <set>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 200010;

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
		int y; Int64 z; Edge *next, *opt; bool flag;
		Edge(int y, Int64 z, Edge* next):y(y), z(z), next(next){flag = false;}
	}*a[MAXN], *e[MAXN];

	struct _ {
		int x, y;
	}query[MAXN];

	inline void AddEdge(int x, int y, Int64 z, Edge *a[]) {
		a[x] = new Edge(y, z, a[x]);
		a[y] = new Edge(x, z, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}

	int n, m, s, t, q;

	inline void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= m; i++) {
			int x = ScanInt() + 1, y = ScanInt() + 1;Int64 z = ScanInt();
			assert(z != 0);
			AddEdge(x, y, z, a);
		}
		s = ScanInt() + 1, t = ScanInt() + 1;
		q = ScanInt();
		for (int i = 1; i <= q; i++) {
			query[i].x = ScanInt() + 1;
			query[i].y = ScanInt() + 1;
		}
	}

	Int64 disx[MAXN], disy[MAXN];

	inline void Dijkstra(int u, Int64 dis[], QII &T) {
		for (int i = 0; i <= n; i++) dis[i] = 100000000000000000ll;
		dis[u] = 0; T.push(mp(0, u));
		for (int i = 1; i < n; i++) {
			while (!T.empty() && -T.top().first > dis[T.top().second]) T.pop();
			if (T.empty()) break;
			int tmp = T.top().second; T.pop();
			for (Edge *p = a[tmp]; p; p = p->next) 
				if (dis[p->y] > dis[tmp] + p->z)
					T.push(mp(-(dis[p->y] = dis[tmp] + p->z), p->y));
		}
	}

	int father[MAXN], deep[MAXN];
	bool vis[MAXN];

	inline void Build(int u) {
		vis[u] = true;
		for (Edge *p = a[u]; p; p = p->next) if (disx[p->y] == disx[u] + p->z && !vis[p->y]) {
			p->flag = p->opt->flag = true;
			e[u] = new Edge(p->y, p->z, e[u]);
			deep[p->y] = deep[u] + 1;
			father[p->y] = u;
			Build(p->y);
		}
	}

	Int64 Ans[MAXN];
	int pos[MAXN], belong[MAXN], other[MAXN];
	bool inPath[MAXN];

	inline void Color(int u, int c) {
		belong[u] = c;
		for (Edge *p = e[u]; p; p = p->next)
			Color(p->y, c);
	}

	inline void Init(void) {
		int tmp = t, d = 0, last = 0;
		while (tmp) {
			d++;
			inPath[tmp] = true;
			belong[tmp] = d;
			for (Edge *p = e[tmp]; p; p = p->next) if (p->y != last)
				Color(p->y, d);
			last = tmp;
			tmp = father[tmp];
		}
		for (int i = 1; i <= q; i++) {
			int &x = query[i].x, &y = query[i].y;
			if (deep[x] > deep[y]) swap(x, y);
			if (inPath[y] && father[y] == x) {
				if (pos[y] == 0) pos[y] = i;
				else other[i] = pos[y];
			}
			else
				Ans[i] = disx[t];
		}
	}

	QII S;

	inline void Dfs(int u) {
		if (pos[u] != 0) {
			while (!S.empty() && S.top().second > belong[u]) S.pop();
			if (S.empty()) Ans[pos[u]] = -1; else Ans[pos[u]] = -S.top().first;
		}
		for (Edge *p = a[u]; p; p = p->next) if (!p->flag && belong[u] > belong[p->y]) {
			S.push(mp(-(disx[u] + p->z+ disy[p->y]), belong[p->y]));
		}
		for (Edge *p = e[u]; p; p = p->next) if (!inPath[p->y]) {
			Dfs(p->y);
		}
		for (Edge *p = e[u]; p; p = p->next) if ( inPath[p->y]) {
			Dfs(p->y);
		}
	}

	QII T1, T2;

	inline void solve(void) {
		Input();
		Dijkstra(s, disx, T1);
		Dijkstra(t, disy, T2);
		if (disx[t] == disx[0]) {
			for (int i = 1; i <= q; i++) puts("Infinity");
			return;
		}
		deep[s] = 1;
		Build(s);
		Init();
		Dfs(s);
		for (int i = 1; i <= q; i++) {
			if (Ans[i] != -1) {
				if (other[i] == 0)
					printf(LL "\n", Ans[i]);
				else
					printf(LL "\n", Ans[other[i]]);
			}
			else puts("Infinity");
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

