//#define Debug
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace DATA {
	const int MAXN = 60050;
	#define Lowbit(x) ((x) & (-(x)))
	class TreeArray {public:
		int n, a[MAXN];
		inline void Set(int _n) {n = _n;}
		inline int Cal(int u) {int ret = 0;for (int i = u; i > 0; i -= Lowbit(i)) ret += a[i];return ret;}
		inline int Ins(int u, int t) {for (int i = u; i <= n; i += Lowbit(i)) a[i] += t;}
		inline int Sum(int l, int r) {return Cal(r) - Cal(l - 1);}
	};
}
namespace Solve {
	const int MAXN = 30050;
	const int MAXQ = 300050;

	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	inline void ScanStr(char *ch) {
		int l = 0, c;
		while (c = getchar(), !islower(c)) {}
		ch[l++] = c;
		while (c = getchar(),  islower(c)) ch[l++] = c;
		ch[l] = '\0';
	}
	
	int n, Q, value[MAXN];

	struct Query {
		int type, x, y; bool yes;
	}T[MAXQ];
	struct Edge {
		int y; Edge* next, *opt; bool flag;
		Edge(int y, Edge* next):next(next), y(y){flag = true;}
	}*a[MAXN];
	
	inline void AddEdge(int x, int y) {
		a[x] = new Edge(y, a[x]);
		a[y] = new Edge(x, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}

	int f[MAXN];
	int Find(int x) {if (x == f[x]) return x;return f[x] = Find(f[x]);}
	inline void Union(int a, int b) {f[Find(a)] = Find(b);}
	
	void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) value[i] = ScanInt();
		for (int i = 1; i <= n; i++) f[i] = i;
		Q = ScanInt();
		char ch[10];
		for (int i = 1; i <= Q; i++) {
			ScanStr(ch);
			T[i].type = ch[0];
			T[i].x = ScanInt(), T[i].y = ScanInt();
			if (ch[0] == 'b')
				if (Find(T[i].x) != Find(T[i].y)) {
					AddEdge(T[i].x, T[i].y);
					Union(T[i].x, T[i].y);
					T[i].yes = true;
				}
			if (ch[0] == 'e')
				T[i].yes = (Find(T[i].x) != Find(T[i].y));
		}
	}

	bool vis[MAXN];
	int list[MAXN << 1], nList = 0, root[MAXN], now, fim[MAXN], out[MAXN];

	void Dfs(int u) {
		vis[u] = true;
		list[++nList] = value[u]; fim[u] = nList;
		assert(nList <= 60000);
		root[u] = now;
		for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			Dfs(p->y);
		}
		list[++nList] = -value[u]; out[u] = nList;
	}

	int d[MAXN], belong[MAXN], deep[MAXN], p[MAXN], son[MAXN];
	void Cut(int u) {
		int head = 1, tail = 1;
		d[1] = u;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->flag) {
				d[++tail] = p->y;
				deep[p->y] = deep[now] + 1;
				Solve::p[p->y] = now;
			}
		}
		for (int i = tail; i >= 1; i--) {
			int t = d[i];
			son[p[t]] += ++son[t];
		}
		for (int i = 1; i <= tail; i++) {
			int t = d[i], nowson = 0, max = 0;
			if (belong[t] == 0) belong[t] = t;
			for (Edge *p = a[t]; p; p = p->next) if (p->flag && son[p->y] > max)
				max = son[p->y], nowson = p->y;
			if (nowson) belong[nowson] = belong[t];
		}
	}

	DATA::TreeArray T_T;

	inline void Prepare(void) {
		for (int i = 1; i <= n; i++) if (!vis[i]) {
			now = nList + 1;
			Dfs(i);
			Cut(i);
		}
		T_T.Set(nList);
		for (int i = 1; i <= nList; i++) T_T.Ins(i, list[i]);
	}
	
	inline int LCA(int a, int b) {
		while (true) {
			if (deep[a] > deep[b]) std::swap(a, b);
			if (belong[a] == belong[b]) return a;
			if (deep[belong[a]] < deep[belong[b]]) b = p[belong[b]];
			else a = p[belong[a]];
		}
	}


	inline int Cal(int u) {return T_T.Sum(root[u], fim[u]);}
	inline void Trans(int where, int u) {
		T_T.Ins(fim[where], u - list[fim[where]]);
		T_T.Ins(out[where], -u - list[out[where]]);
		list[fim[where]] = u, list[out[where]] = -u;
	}

	void Work(void) {
		for (int i = 1; i <= Q; i++) {
			int x = T[i].x, y = T[i].y, type = T[i].type;
			if (type == 'e') {
				if (T[i].yes) puts("impossible"); else {
					int A = LCA(x, y);
					printf("%d\n", Cal(x) + Cal(y) - 2 * Cal(A) + list[fim[A]]);
				}
			}else
			if (type == 'b') {
				if (T[i].yes) puts("yes");else puts("no");
			}else
			if (type == 'p') 
				Trans(x, y);
		}
	}

	void solve(void) {
		Input();
		Prepare();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
