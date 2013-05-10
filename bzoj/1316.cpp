//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 20050;
	const int inf = 0x6eeeeeee;
	int nNode, Q;

	struct Edge {
		int y, z; Edge *next, *opt; bool flag;
		Edge(int y, int z, Edge* next):y(y), z(z), next(next){flag = true;}
	}*e[MAXN], *a[MAXN];

	void AddEdge(int x, int y, int z) {
		a[x] = new Edge(y, z, a[x]);
		a[y] = new Edge(x, z, a[y]);
		a[x]->opt = a[y];
		a[y]->opt = a[x];
	}

	int ScanInt(void) {
		int r, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	void Input(void) {
		nNode = ScanInt(), Q = ScanInt();
		for (int i = 1; i < nNode; i++) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			e[x] = new Edge(y, z, e[x]);
			e[y] = new Edge(x, z, e[y]);
			e[x]->opt = e[y];
			e[y]->opt = e[x];
		}
	}
	
	Edge* d[MAXN]; int l;
	void AddNode(int u) {
		l = 0;
		for (Edge* p = e[u]; p; p = p->next) if (p->flag) {
			d[++l] = p;
		}
	
		int now = u;
		for (int i = 1; i <= l; i++) {
			AddEdge(now, d[i]->y, d[i]->z);
			if (i + 1 == l) {
				AddEdge(now, d[i + 1]->y, d[i + 1]->z);
				break;
			}else
				AddEdge(now, ++nNode, 0), now = nNode;
		}

		for (Edge* p = e[u]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			AddNode(p->y);
		}
	}

	#define abs(x) ((x) < 0 ? (-(x)) : (x))
	int size[MAXN], best, SumNode; Edge* Aim;

	int DfsSize(int u) {
		size[u] = 1;
		for (Edge* p = a[u]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			size[u] += DfsSize(p->y);
			p->opt->flag = true;
		}
		return size[u];
	}

	void DfsEdge(int u) {
		int now;
		for (Edge* p = a[u]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			now = abs(SumNode - 2 * size[p->y]);
			if (now < best)
				best = now, Aim = p;
			DfsEdge(p->y);
			p->opt->flag = true;
		}
	}

	Edge* GetEdge(int u) {
		Aim = NULL;
		SumNode = DfsSize(u);
		best = inf;
		DfsEdge(u);
		return Aim;
	}

	bool ret;
	int segx[MAXN], segy[MAXN], K;

	void Check(int a[], int b[], int delta) {
		int aLength = a[0], bLength = b[0];
		std::sort(a + 1, a + aLength + 1);
		std::sort(b + 1, b + bLength + 1);

		int j = bLength;
		for (int i = 1; i <= aLength && !ret; i++) {
			while (j > 0 && a[i] + b[j] > K - delta) j--;
			if (a[i] + b[j] == K - delta) ret = true;
		}
	}

	void DfsPath(int u, int seg[], int sum) {
		seg[ ++seg[0] ] = sum;
		for (Edge *p = a[u]; p; p = p->next) if (p->flag) {
			p->opt->flag = false;
			DfsPath(p->y, seg, sum + p->z);
			p->opt->flag = true;
		}
	}

	void Gao(Edge *now) {
		if (now == NULL) return;
		int x = now->y, y = now->opt->y;
		now->flag = now->opt->flag = false;
		
		segx[0] = segy[0] = 0;
		DfsPath(x, segx, 0);
		DfsPath(y, segy, 0);
		
		Check(segx, segy, now->z);

		if (!ret){
			Edge *xNext, *yNext;
			xNext = GetEdge(x);
			yNext = GetEdge(y);
			Gao(xNext);
			Gao(yNext);
		}
		now->flag = now->opt->flag = true;
	}

	void Answer(int now) {
		ret = false; K = now;
		Edge* P = GetEdge(1);
		Gao(P);
	}

	void Work(void) {
		for (int _ = 1; _ <= Q; _++) {
			int now = ScanInt();
			Answer(now);
			puts(ret ? "Yes" : "No");
		}
	}

	void solve(void) {
		Input();
		AddNode(1);
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
