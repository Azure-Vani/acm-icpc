#include <queue>
#include <cstdio>
#include <algorithm>
#include <stack>
namespace Solve {
	const int MAXN = 100050;
	const int inf = 100000000;

	int a[MAXN], b[MAXN], n, pos[MAXN];
	void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", a + i), pos[a[i]] = i;
		b[n + 1] = inf;
		for (int i = n; i >= 1; i--) b[i] = std::min(b[i + 1], a[i]);
	}

	struct Node {Node *l, *r;int k;Node(int k):k(k),l(NULL),r(NULL){}};
	int ran(){static int x = 1;x += (x << 2) + 1; x &= 0x7fffffff; return x & 65536;}
	Node *M(Node *p, Node *q) {
		return (!p||!q)?(p?p:q):(p->k>q->k?M(q,p):((ran()?p->l=M(p->l,q):p->r=M(p->r,q)),p));
	};

	struct Edge {int y;Edge*next; Edge(int y, Edge *next):y(y),next(next){}}*E[MAXN];
	#define AddEdge(x, y) {\
		E[x] = new Edge(y, E[x]); E[y] = new Edge(x, E[y]);\
	}

	std::stack<Node*> T;
	inline void Prepare(void) {
		for (int i = 1; i <= n; i++) {
			Node *p = new Node(a[i]);
			while (!T.empty() && T.top()->k < a[i]) {AddEdge(pos[T.top()->k], i); p = M(T.top(), p), T.pop();}
			T.push(p);
			while (!T.empty()) { p = T.top(); T.pop(); while (p && p->k < b[i + 1]) p = M(p->l, p->r); if (p) {T.push(p); break;}}
		}
	}
	int color[MAXN], now = 1;
	inline void Work(void) {
		std::stack<int> S[2]; color[n + 1] = 1;
		for (int i = 1, tmp = 0;S[color[i] - 1].push(a[i]), i <= n;i++) do {tmp = 0;
			for (int k = 0; k <= 1; k++) if (!S[k].empty() && S[k].top() == now) now++, S[k].pop(), tmp = 1;
		}while (tmp);
		if (now > n) {
			puts("TAK");
			for (int i = 1; i < n; i++) printf("%d ", color[i]); printf("%d\n", color[n]);
		}else puts("NIE");
	}
	void Dfs(int u, int c) {color[u] = c; for (Edge *p = E[u]; p; p = p->next) if (!color[p->y]) Dfs(p->y, c^3);}
	void solve(void) {
		Input();
		Prepare();
		for (int i = 1; i <= n; i++) if (!color[i]) Dfs(i, 1);
		Work();
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
