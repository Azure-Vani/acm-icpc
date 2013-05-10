//#define Debug
#include <cassert>
#include <stack>
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 100009;
	
	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y;Int64 z; Edge *next;
		Edge(int y, Int64 z, Edge* next):y(y), z(z), next(next){}
	}*a[MAXN];

	int n;Int64 v[MAXN], w[MAXN];
	
	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i < n; i++) {
			int x = ScanInt(), y = ScanInt();Int64 z = ScanInt();
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
		}
		for (int i = 2; i <= n; i++) 
			w[i] = ScanInt(), v[i] = ScanInt();
	}

	int stack[MAXN], top;
	Int64 X[MAXN], Y[MAXN], d[MAXN], f[MAXN];
	
	void Dfs1(int u, int f) {
		for (Edge *p = a[u]; p; p = p->next) if (p->y != f) {
			d[p->y] += d[u] + p->z;
			Dfs1(p->y, u);
		}
	}

	#define Cross(a, b, c) \
	((double)(Y[b] - Y[c]) / (double)(X[b] - X[c]) >= (double)(Y[a] - Y[c]) / (double) (X[a] - X[c]))
	#define Slope(l1, l2, k) ((Y[l2] - Y[l1]) >= k * (X[l2] - X[l1]))

	inline int Get(Int64 k) {
		int l = 1, r = top;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (mid == r) return stack[mid];
			if (mid == 1) {
				int l1 = stack[1], l2 = stack[2];
				if (Slope(l1, l2, k))
					return l1;
				else return l2;
			}
			int l1 = stack[mid - 1], l2 = stack[mid + 1], t = stack[mid];
			bool c1 = Slope(l1, t, k), c2 = Slope(t, l2, k);
			if (c1 && c2) r = mid - 1;else
			if (!c1 && !c2) l = mid + 1;else
			return t;
		}
	}
	
	inline int Push(int i) {
		int l = 1, r = top;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (Cross(i, stack[mid], stack[mid + 1]))
				r = mid;
			else
				l = mid + 1;
		}
		top = l;
		r = stack[top + 1]; stack[++top] = i;
		return r;
	}
	
	int vis[MAXN];

	struct Node {
		int u, F, p1, w, p2;
		inline void Set(int _u, int _p1, int _w, int _p2, int _F = -1) {
			u = _u, p1 = _p1, w = _w, p2 = _p2;
			if (_F > 0) F = _F;
		}
	}DfsStack[MAXN]; int dtop = 0;

	#define Renew(u, j) { f[u] = f[j] + (d[u] - d[j]) * v[u] + w[u]; X[u] = d[u], Y[u] = f[u];}
	void Dfs(int uu) {
		dtop = 0;
		DfsStack[++dtop].Set(uu, 0, 0, 0, 1);
		while (dtop) {
			int u = DfsStack[dtop].u, F = DfsStack[dtop].F;
			if (vis[u] != 2) {
				if (vis[u] == 0) {
					Renew(u, Get(v[u]));
					int p1 = top, w = Push(u), p2 = top;
					DfsStack[dtop].Set(u, p1, w, p2);
					vis[u] = 1;
				}
				if (a[u]) {
					if (a[u]->y != F)
						DfsStack[++dtop].Set(a[u]->y, 0, 0, 0, u);
					a[u] = a[u]->next;
				}
				if (!a[u]) vis[u] = 2;
			}else {
				top = DfsStack[dtop].p1; 
				stack[DfsStack[dtop].p2] = DfsStack[dtop].w;
				dtop--;
			}
		}
	}

	void solve(void) {
		Input();
		Dfs1(1, 0);
		stack[++top] = 1;
		for (Edge *p = a[1]; p; p = p->next) 
			Dfs(p->y);
		for (int i = 2; i < n; i++) printf("%lld ", f[i]); printf("%lld\n", f[n]);
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
