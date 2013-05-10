//#define Debug
#include <cstdio>
#include <cctype>
#include <algorithm>
#include <queue>
#include <cstring>
#define MP(a, b) std::make_pair(a, b)
namespace Solve {
	const int MAXV = 1850;
	
	int ScanInt(void) {
		int c, r;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y, z; Edge* next;
		Edge(int y, int z, Edge*next) : y(y), z(z), next(next) {}
	}*e[MAXV], *a[MAXV];

	#define Add(x, y, z, a) {\
		a[x] = new Edge(y, z, a[x]);\
		a[y] = new Edge(x, z, a[y]);\
	}

	int n, _, S1, T1, S2, T2;
	void Input(void) {
		n = ScanInt(), _ = ScanInt();
		S1 = ScanInt(), T1 = ScanInt(), S2 = ScanInt(), T2 = ScanInt();
		while (_--) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			Add(x, y, z, e);
		}
	}

	typedef std::pair<int, int> II;

	void Dijkstra(int s, int dis[]) {
		memset(dis, 101, sizeof(int) * (n + 1));
		dis[s] = 0;
		std::priority_queue<II> Q;
		Q.push(MP(0, s));

		for (int i = 1; i < n; i++) {
			while (-Q.top().first > dis[Q.top().second]) Q.pop();
			int now = Q.top().second; dis[now] = -Q.top().first; Q.pop();
			for (Edge *p = e[now]; p; p = p->next)
				if (dis[p->y] > dis[now] + p->z)
					Q.push(MP(-(dis[p->y] = dis[now] + p->z), p->y));
		}
	}

	int Dis1[MAXV], Dis2[MAXV], Dis3[MAXV], Dis4[MAXV], D1, D2;
	int Queue[MAXV], nNode = 0;
	int top;
	bool In[MAXV];

	bool Check(int u) {
		return (D1 == Dis1[u] + Dis3[u] && D2 == Dis2[u] + Dis4[u]);
	}
	bool cmp(int a, int b) {
		return Dis1[a] < Dis1[b];
	}
	bool InPath(int u, Edge* p) {
		return std::min(Dis1[u] + Dis3[p->y], Dis1[p->y] + Dis3[u]) + p->z == D1 &&
		       std::min(Dis2[u] + Dis4[p->y], Dis2[p->y] + Dis4[u]) + p->z == D2;
	}

	void Shortestpath(void) {
		Dijkstra(S1, Dis1);
		Dijkstra(S2, Dis2);
		Dijkstra(T1, Dis3);
		Dijkstra(T2, Dis4);
		D1 = Dis1[T1], D2 = Dis2[T2];
		for (int i = 1; i <= n; i++)
			if (Check(i))
				In[ Queue[top++] = i ] = true;
		std::sort(Queue, Queue + top, cmp);
	}

	int f[MAXV];
	void Dp(void) {
		int Ans = 0;
		for (int i = 0; i < top; i++) {
			int t = Queue[i]; Ans = std::max(Ans, f[t]);
			for (Edge* p = e[t]; p; p = p->next)
				if (In[p->y] && InPath(t, p))
					f[p->y] = std::max(f[p->y], f[t] + p->z);
		}
		printf("%d\n", Ans);
	}
	void solve(void) {
		Input();
		Shortestpath();
		Dp();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
