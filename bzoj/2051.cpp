//#define Debug
#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 50020;
	const int MAXQ = 230;

	struct Edge {
		int y, z; Edge *next, *opt; bool flag;
		Edge(int y, int z, Edge *next):y(y), z(z), next(next){flag = true;}
		Edge(){}
		void* operator new(size_t, void* p) {return p;}
	}*a[MAXN], POOL[MAXN << 1], *data = POOL;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n, k, Limit;
	inline void Input(void) {
		scanf("%d%d", &n, &k);k++;
		for (int i = 1, x, y, z; i < n; i++) {
			scanf("%d%d%d", &x, &y, &z);
			a[x] = new((void*)data++) Edge(y, z, a[x]);
			a[y] = new((void*)data++) Edge(x, z, a[y]);
			a[x]->opt = a[y];
			a[y]->opt = a[x];
			Limit += z;
		}
	}

	struct Interval {
		int l, r;
	}c[MAXN]; int cnt = 0;
	int list[MAXN], deep[MAXN];

	void Dfs(int u) {
		list[ c[u].l = ++cnt ] = u;
		for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			deep[p->y] = deep[u] + p->z;
			Dfs(p->y);
		}
		c[u].r = cnt;
	}

	inline int Binary(int a[], int l, int r, int u) {
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (u <= a[mid])
				r = mid - 1;
			else
				l = mid + 1;
		}
		return r;
	}

	struct Pair {
		int a[MAXQ + 3], c[MAXQ + 3], cnt, delta;
		inline void Set(int b[], int n) {
			memcpy(a + 1, b, sizeof(int) * n);
			memcpy(c + 1, b, sizeof(int) * n);
			std::sort(a + 1, a + n + 1);
			cnt = n, delta = 0;
		}
		inline void Add(int l, int r, int u) {
			for (int i = l; i <= r; i++) c[i] += u;
			memcpy(a, c, sizeof (int) * (cnt + 1));
			std::sort(a + 1, a + cnt + 1);
		}
		inline int Cal(int u) {
			int ret = Binary(a, 1, cnt, u - delta);
			return ret;
		}
	}T[MAXQ + 3]; int sum = 0;

	#define Belong(x) (((x) - 1) / MAXQ + 1)
	inline void Add(int l, int r, int u) {
		if (l > r) return;
		int t1 = Belong(l), t2 = Belong(r);
		if (t1 == t2) {
			T[t1].Add(l - (t1 - 1) * MAXQ, r - (t1 - 1) * MAXQ, u);
			return;
		}
		if (t1 == Belong(l - 1)) {
			T[t1].Add(l - (t1 - 1) * MAXQ, T[t1].cnt, u);
			t1++;
		}
		if (t2 == Belong(r + 1)) {
			T[t2].Add(1, r - (t2 - 1) * MAXQ, u);
			t2--;
		}
		for (int i = t1; i <= t2; i++)
			T[i].delta += u;
	}

	inline int Work(void) {
		int l = 0, r = Limit;
		while (l <= r) {
			int mid = (l + r) >> 1, tmp = 0;
			for (int i = 1; i <= sum; i++)
				tmp += T[i].Cal(mid);
			if (tmp <= k - 1)
				l = mid + 1;
			else
				r = mid - 1;
		}
		return r;
	}

	int Ans[MAXN];
	void Gao(int t) {
		Ans[t] = Work();
		for (Edge *p = a[t]; p; p = p->next) if (p->flag) {
			int u = p->y;
			Add(1, n, p->z);
			Add(c[u].l, c[u].r, -p->z * 2);
			Gao(p->y);
			Add(1, n, -p->z);
			Add(c[u].l, c[u].r, p->z * 2);
		}
	}

	int path[MAXN];
	void solve(void) {
		Input();
		Dfs(1);
		for (int i = 1; i <= n; i++) path[i] = deep[list[i]];
		for (int i = 1; i <= n; i += MAXQ) {
			sum++;
			T[sum].Set(path+ i, std::min(n - i + 1, MAXQ));
		}
		Gao(1);
		for (int i = 1; i <= n; i++) printf("%d\n", Ans[i]);
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
