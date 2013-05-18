#define FILEIO

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
		int y, z; Edge *next;
		Edge(int y, int z, Edge *next):y(y), z(z), next(next){}
	}*a[MAXN];

	int n, m, k, mid, cnt, s, t;
	int d[MAXN], vis[MAXN], dis[MAXN];

	struct Route {
		int a[MAXN], length, num;
		Route(int *p, int _length, int _num) {
			length = _length, num = _num;
			REP(i,1,_num) a[i] = p[i];
		}
		friend bool operator <(const Route& x, const Route& y) {
			return x.length < y.length;
		}
	};

	vector<Route> Ans;

	int stack[MAXN], top = 0;

	void Dfs(int u, int sum, bool save = false) {
		if (u == t) {
			cnt++;
			if (save) {
				stack[++top] = t;
				Ans.push_back(Route(stack, sum, top));
				stack[top--] = 0;
			}
			return;
		}
		if (cnt >= k) return;
		stack[++top] = u;
		vis[u] = true;
		for (Edge *p = a[u]; p; p = p->next) if (!vis[p->y] && dis[p->y] + p->z + sum <= mid) {
			Dfs(p->y, sum + p->z, save);
		}
		vis[u] = false;
		stack[top--] = 0;
	}

	inline void solve(void) {
		n = ScanInt(), m = ScanInt(), k = ScanInt();
		rep(i,m) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
		}
		s = ScanInt(), t = ScanInt();
		rep(i,n) dis[i] = 1000000000; int head = 1, tail = 1, sum = 1;
		d[1] = t; vis[t] = true; dis[t] = 0;
		while (sum) {
			int now = d[head++]; if (head >= MAXN) head = 1; sum--;
			for (Edge *p = a[now]; p; p = p->next) if (dis[p->y] > dis[now] + p->z) {
				dis[p->y] = dis[now] + p->z;
				if (!vis[p->y]) {
					vis[p->y] = true;
					++tail; if (tail >= MAXN) tail = 1;
					d[tail] = p->y; sum++;
				}
			}
			vis[now] = false;
		}
		int l = 1, r = 1000000000;
		while (l <= r) {
			mid = (l + r) >> 1; cnt = 0;
			Dfs(s, 0);
			if (cnt < k) l = mid + 1;
			else r = mid - 1;
		}
		mid = l, cnt = 0;
		Dfs(s, 0, true);
		sort(Ans.begin(), Ans.end());
		printf("%d %d\n", Ans[k-1].length, Ans[k-1].num);
		for (int i = 1; i < Ans[k-1].num; i++) {
			printf("%d ", Ans[k-1].a[i]);
		}
		printf("%d\n", Ans[k-1].a[Ans[k-1].num]);
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

