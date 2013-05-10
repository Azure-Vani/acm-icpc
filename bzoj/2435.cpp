#include <cctype>
#include <cstdio>
#include <algorithm>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 1000010;

	inline Int64 abs(Int64 a) {
		return a<0?-a:a;
	}

	inline int ScanInt(void) {
		int r = 0, c;
		while (!isdigit(c = getchar()));
		r = c - '0';
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y; Int64 cost; Edge *next;
		Edge(int y, Int64 cost, Edge *next):y(y), cost(cost), next(next){}
	}*a[MAXN];
	inline void AddEdge(int x, int y, Int64 c) {
		a[x] = new Edge(y, c, a[x]);
		a[y] = new Edge(x, c, a[y]);
	}

	int n;

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i < n; i++) {
			int x = ScanInt(), y = ScanInt(); Int64 c = ScanInt();
			AddEdge(x, y, c);
		}
	}
	
	int d[MAXN], p[MAXN], sum[MAXN];
	Int64 cost[MAXN];

	inline Int64 Work(void) {
		int head = 1, tail = 1; d[1] = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next) if (p->y != Solve::p[now]) {
				Solve::p[d[++tail] = p->y] = now;
				cost[p->y] = p->cost;
			}
		}
		for (int i = n; i >= 1; i--) sum[p[d[i]]] += ++sum[d[i]];
		Int64 ret = 0;
		for (int i = 2; i <= n; i++)
			ret += abs(sum[i] - (n - sum[i])) * cost[i];
		return ret;
	}

	inline void solve(void) {
		Input();
		printf("%lld\n", Work());
	}
}
int main(void) {
	//freopen("2435.in", "r", stdin);
	Solve::solve();
	return 0;
}
