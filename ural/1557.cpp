#define FILEIO

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>

#define rep(i,l,r) for(register int i = (l); i <= (r); i++)
#define In(a, b, c) (((a) >= (b)) && ((a) <= (c)))

namespace Solve {
	typedef long long Int64;
	const int MAXN = 2500;
	const int MAXM = 200020;
	
	struct Edge {
		int y; Edge* opt, *next; bool inTree, isBridge;
		Edge(int y, Edge *next):y(y), next(next){isBridge = inTree = false;}
	}*a[MAXN], *e[MAXN];
	int m, n, N; Int64 M = 0;
	
	int ScanInt(void) {
		int c, r = 0, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0';
		while ( isdigit(d = getchar())) r = r * 10 + d - '0';
		return c=='-'?-r:r;
	}

	inline void Input(void) {
		n = N = ScanInt(), m = M = ScanInt();
		register int tmp = 0;
		rep(i,1,m) {
			int x = ScanInt(), y = ScanInt();
			if (x == y) {tmp++; continue;}
			a[x] = new Edge(y, a[x]);
			a[y] = new Edge(x, a[y]);
			a[x]->opt = a[y]; a[y]->opt = a[x];
		}
	}

	int s[MAXN], tim[MAXN], time = 0, cover[MAXN], deep[MAXN], p[MAXN];
	Int64 ans1 = 0, ans2 = 0;

	inline bool GetBridge(int u, int path) {
		tim[u] = ++time;
		deep[u] = path;
		for (Edge *p = a[u]; p; p = p->next) if (!tim[p->y]) {
			p->isBridge = p->opt->isBridge = GetBridge(p->y, path + 1);
			Solve::p[p->y] = u;
			p->inTree = p->opt->inTree = true;
			s[u] += s[p->y];
		} else if (!p->inTree && tim[p->y] < tim[u]) {
			s[u]++;
			cover[p->y]++;
		}
		s[u] -= cover[u];
		return s[u] == 1;
	}

	int color[MAXN], cur = 0;

	inline void Floodfill(int u) {
		color[u] = cur;
		for (Edge *p = a[u]; p; p = p->next) if (p->isBridge && !color[p->y])
			Floodfill(p->y);
	}

	inline void reBuildGraph(void) {
		for (int i = 1; i <= n; i++) if (!color[i]) {
			cur++;
			Floodfill(i);
		}
		for (int i = 1; i <= n; i++)
			for (Edge *p = a[i]; p; p = p->next) {
				int x = color[i], y = color[p->y];
				if (x > y) {
					e[x] = new Edge(y, e[x]);
					e[y] = new Edge(x, e[y]);
					e[x]->opt = e[y], e[y]->opt = e[x];
				}
			}
		n = cur;
		for (int i = 1; i <= n; i++) a[i] = e[i];
	}

	struct Pair {
		int x, y;
	}E[MAXM];

	inline bool cmp(const Pair& a, const Pair& b) {
		return deep[a.x] > deep[b.x];
	}

	inline void reMakeGraph(void) {
		time = cur = 0;
		memset(tim, 0, sizeof tim);
		memset(color, 0, sizeof color);
		memset(s, 0, sizeof s);
		memset(cover, 0, sizeof cover);
		memset(deep, 0, sizeof deep);
		memset(p, 0, sizeof p);
		GetBridge(1, 1);
		for (int i = 1; i <= n; i++) ans2 += (s[i] == 2);
		int tmp = 0;
		for (int i = 1; i <= n; i++)
			for (Edge *p = a[i]; p; p = p->next) if (!p->inTree) {
				if (deep[i] < deep[p->y]) {
					E[++tmp].x = i, E[tmp].y = p->y;
				}
			}
		std::sort(E + 1, E + tmp + 1, cmp);
		m = tmp;
	}

	int Low[MAXN];
	int f[MAXN];
	inline int Find(int x) {return x == f[x] ? x : f[x] = Find(f[x]);}

	inline void Color(int x, int y) {
		register int Limit = deep[x];
		while (y = Find(y), deep[y] > Limit) {
			Low[y] = x;
			f[y] = Find(p[y]);
		}
	}

	inline void CalLow(void) {
		for (int i = 1; i <= n; i++) f[i] = i;
		for (int i = 1; i <= m; i++) {
			Color(E[i].x, E[i].y);
		}
	}

	struct Ask {
		int k, pos;
	}Q[MAXM << 1];
	struct Node_Ask {
		int k, index; Node_Ask *next;
		Node_Ask(int k, int index, Node_Ask *next):k(k), index(index), next(next){}
	}*ask[MAXN];
	int ans[MAXN << 1], hash[MAXM];

	inline void GetAsk(void) {
		for (register int i = 2; i <= n; i++) {
			register int tmp = (i - 1) << 1;
			Q[tmp - 1].k = s[i];
			Q[tmp - 1].pos = i;
			Q[tmp].k = s[i];
			Q[tmp].pos = Low[i];
		}
		for (int i = 1; i <= (n - 1) * 2; i++) {
			ask[Q[i].pos] = new Node_Ask(Q[i].k, i, ask[Q[i].pos]);
		}
	}

	inline void FinalDfs(int u) {
		if (u != 1) hash[s[u]]++;
		for (Node_Ask *p = ask[u]; p; p = p->next)
			ans[p->index] = hash[p->k];
		for (Edge *p = a[u]; p; p = p->next) if (p->y != Solve::p[u] && p->inTree) 
			FinalDfs(p->y);
		if (u != 1) hash[s[u]]--;
	}

	int NodeSum[MAXN];
	inline Int64 FinalCal(void) {
		for (int i = 2; i <= n; i++) {
			register int tmp = (i - 1) << 1;
			NodeSum[i] = ans[tmp - 1] - ans[tmp] - 1;
		}
		for (int i = 2; i <= n; i++)
			ans2 += NodeSum[i];
		Int64 ret = ((M * (M - 1) - (M - ans1) * (M - ans1 - 1)) >> 1) + ans2;
		return ret;
	}

	inline void solve(void) {
		Input();
		GetBridge(1, 1);
		for (int i = 1; i <= n; i++) ans1 += (s[i] == 1);
		reBuildGraph();
		reMakeGraph();
		CalLow();
		GetAsk();
		FinalDfs(1);
		Int64 ret = FinalCal();
		printf(LL "\n",ret);
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

