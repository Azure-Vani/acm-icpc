//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
namespace Solve {
	const int MAXN = 500050;

	struct Edge {
		int y; Edge* next, *opt; bool flag;
		Edge(){}
		Edge(int y, Edge* next):y(y), next(next) { flag = true; }
		void* operator new(size_t, void* p){ return p; }
	}*a[MAXN], POOL[MAXN << 1], *data = POOL;

	int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	int n, m;
	void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i < n; i++) {
			int x = ScanInt(), y = ScanInt();
			a[x] = new((void*)data++) Edge(y, a[x]);
			a[y] = new((void*)data++) Edge(x, a[y]);
			a[x]->opt = a[y];
			a[y]->opt = a[x];
		}
	}

	int deep[MAXN], P[MAXN], Line[MAXN], Size[MAXN], d[MAXN];
	void Prepare(void) {
		int head = 1, tail = 1;
		d[1] = 1;
		while (head <= tail) {
			int now = d[head++];
			for (Edge *p = a[now]; p; p = p->next)
				if (p->flag) {
					p->opt->flag = false;
					deep[p->y] = deep[now] + 1;
					d[++tail] = p->y;
					P[p->y] = now;
				}
		}

		for (int i = n; i >= 1; i--)
			Size[P[d[i]]] += ++Size[d[i]];
		for (int i = 1; i <= n; i++) {
			int t = d[i], What = 0, max = 0;
			for (Edge* p = a[t]; p;p = p->next)
				if (p->flag && Size[p->y] > max)
					max = p->y, What = p->y;
			if (!Line[t]) Line[t] = t;
			Line[What] = Line[t];
		}
	}

	inline int GetF(int a, int b) {
		while (true) {
			if (deep[a] < deep[b]) std::swap(a, b);
			if (Line[a] == Line[b]) return b;
			if (deep[Line[a]] < deep[Line[b]]) std::swap(a, b);
			a = P[Line[a]];
		}
	}

	inline int Dis(int a, int b, int A = 0) {
		if (!A) A = GetF(a, b);
		return deep[a] + deep[b] - (deep[A] << 1);
	}

	int MainWork(void) {
		for (int i = 1; i <= m; i++) {
			int a = ScanInt(), b = ScanInt(), c = ScanInt();
			int l1 = GetF(a, b), l2 = GetF(a, c), l3 = GetF(b, c);
			int Sum, Where;
			if (deep[l1] >= deep[l2] && deep[l1] >= deep[l3]) {		
				Where = l1;
				Sum = Dis(a, b, l1) + Dis(c, l1);
			}else
			if (deep[l2] >= deep[l1] && deep[l2] >= deep[l3]) {
				Where = l2;
				Sum = Dis(a, c, l2) + Dis(b, l2);
			}else
			if (deep[l3] >= deep[l1] && deep[l3] >= deep[l2]) {
				Where = l3;
				Sum = Dis(b, c, l3) + Dis(a, l3);
			}
			printf("%d %d\n", Where, Sum);
		}
	}
	void solve(void) {
		Input();
		Prepare();
		MainWork();
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