//#define Debug
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 100010;
	const int MAXM = 300010;

	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y, z, index; Edge *next, *opt; bool flag;
		Edge(int y, int z, Edge *next):y(y), z(z), next(next){flag = true;}
	}*a[MAXN];

	struct pair {int x, y, z, index;} E[MAXM];
	int n, m;
	inline bool cmp(const pair& a, const pair& b) {
		return a.z < b.z;
	}

	void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= m; i++) {
			E[i].x = ScanInt(), E[i].y = ScanInt(), E[i].z = ScanInt();
			a[E[i].x] = new Edge(E[i].y, E[i].z, a[E[i].x]);
			a[E[i].y] = new Edge(E[i].x, E[i].z, a[E[i].y]);
			a[E[i].x]->opt = a[E[i].y];
			a[E[i].y]->opt = a[E[i].x];
			E[i].index = a[E[i].x]->index = a[E[i].y]->index = i;
		}
		std::sort(E + 1, E + m + 1, cmp);
	}

	int father[MAXN]; bool vis[MAXM];
	int Get(int x) {return (father[x] == x) ? x : (father[x] = Get(father[x]));}

	int d[MAXN], deep[MAXN];
	struct Node {
		int first, second, index;
		Node():first(0),second(0),index(0){ }
		inline void Set(int _index, int c) {
			first = c, second = 0, index = _index;
		}
	}f[MAXN][20];
	inline Node Merge(const Node& a, const Node& b) {
		Node ret;
		ret.first = std::max(a.first, b.first);
		ret.second = ((a.first == b.first) ? std::max(a.second, b.second) : std::min(a.first, b.first));
		return ret;
	}

	Int64 MST = 0;
	void Prepare(void) {
		for (int i = 1; i <= n; i++) father[i] = i;

		int l = 0;
		for (int i = 1; i <= m; i++) if (Get(E[i].x) != Get(E[i].y)) {
			father[Get(E[i].x)] = Get(E[i].y);
			MST += E[i].z; vis[E[i].index] = true;
			if (++l == m - 1) break;
		}
	}

	void Bfs(void) {
		int head = 1, tail = 1;
		d[1] = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->flag && vis[p->index]) {
				p->opt->flag = false;
				f[d[++tail] = p->y][0].Set(now, p->z);
				deep[p->y] = deep[now] + 1;
			}
		}
		
		for (int _ = 1; _ <= tail; _++) {
			int i = d[_];
			for (int j = 1; (1 << j) <= deep[i]; j++) {
				int t = f[i][j - 1].index;
				f[i][j] = Merge(f[i][j - 1], f[t][j - 1]);
				f[i][j].index = f[t][j - 1].index;
			}
		}
	}

	inline Node Goup(int& u, int delta) {
		Node r;
		for (int i = 18; i >= 0; i--) 
			if ((delta & (1 << i)) != 0) {
				r = Merge(r, f[u][i]);
				u = f[u][i].index;
			}
		return r;
	}

	inline Node Gao(int a, int b) {
		if (deep[a] > deep[b]) std::swap(a, b);
		Node Ans = Goup(b, deep[b] - deep[a]);
		if (a == b) return Ans;
		for (int i = 18; i >= 0; i--)
			if (f[a][i].index != f[b][i].index) {
				Ans = Merge(Ans, Merge(f[a][i], f[b][i]));
				a = f[a][i].index, b = f[b][i].index;
			}
		Ans = Merge(Ans, Merge(f[a][0], f[b][0]));
		return Ans;
	}

	void Work(void) {
		Int64 Ans = 1000000000000200ll;
		for (int i = 1; i <= m; i++) if (!vis[E[i].index]) {
			Node tmp = Gao(E[i].x, E[i].y);
			assert(tmp.first != 0);
			if (E[i].z == tmp.first)
				Ans = std::min(Ans, MST - tmp.second + E[i].z);
			else
				Ans = std::min(Ans, MST - tmp.first + E[i].z);
		}
		printf("%lld\n", Ans);
	}
	void solve(void) {
		Input();
		Prepare();
		Bfs();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
