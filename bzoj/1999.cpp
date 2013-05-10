#include <queue>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
namespace Solve {
	const int MAXN = 500050;
	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Edge {
		int y, z; Edge* next;
		Edge(){}
		Edge(int y, int z, Edge* next):y(y), z(z), next(next){}
		inline void* operator new(size_t, void* p){ return p;}
	}*a[MAXN], POOL[MAXN << 1], *data = POOL;

	int n, s;
	void Input(void) {
		n = ScanInt(), s = ScanInt();
		for (int i = 1, x, y, z; i < n; i++) {
			x = ScanInt(), y = ScanInt(), z = ScanInt();
			a[x] = new((void*)data++) Edge(y, z, a[x]);
			a[y] = new((void*)data++) Edge(x, z, a[y]);
		}
	}

	int level[MAXN], pre[MAXN]; bool In[MAXN];
	int Bfs(int u) {
		level[u] = 0;
		std::queue<int> Q;
		Q.push(u);int L = 0, ret = 0; In[u] = true;
		while (Q.size()) {
			int now = Q.front();Q.pop();
			for (Edge* p = a[now]; p; p = p->next)
				if (!In[p->y]) {
					In[p->y] = true;
					level[p->y] = level[now] + p->z, pre[p->y] = now;
					if (level[p->y] > L) L = level[p->y], ret = p->y;
					Q.push(p->y);
				}
		}
		return ret;
	}

	int d[MAXN], nNode, subTree[MAXN], dis[MAXN], front[MAXN], behind[MAXN];
	void Initialize(void) {
		int vs = Bfs(1);memset(In, 0, sizeof In); memset(pre, 0, sizeof pre);int vt = Bfs(vs); memset(In, 0, sizeof In);
		while (vt) In[d[++nNode] = vt] = true, dis[nNode] = level[vt], vt = pre[vt];
		for (int i = 1, now; i <= nNode; i++)
			now = Bfs(d[i]), subTree[i] = level[now];
		front[1] = 0;
		for (int i = 2; i <= nNode; i++) front[i] = std::max(front[i - 1] + dis[i - 1] - dis[i], subTree[i]);
		behind[nNode] = 0;
		for (int i = nNode - 1; i >= 1; i--) behind[i] = std::max(behind[i + 1] + dis[i] - dis[i + 1], subTree[i]);
	}

	int Q[MAXN];
	void Work(void) {
		int head = 1, tail = 0, Ans = 0x7fffffff, F = 0;
		dis[F] = 0x6eeeeeee;
		for (int i = 1; i <= nNode; i++) {
			while (head <= tail && dis[Q[head]] - dis[i] < -s) head++;
			while (head <= tail && subTree[i] >= subTree[Q[tail]]) tail--;
			Q[++tail] = i;
			while (dis[i] - dis[F] < -s) F++;
			Ans = std::min(Ans, std::max(subTree[Q[head]], std::max(front[F], behind[i])));
		}
		printf("%d\n", Ans);
	}

	void solve(void) {
		Input();
		Initialize();
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
