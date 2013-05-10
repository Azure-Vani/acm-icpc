#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cctype>

#define cl(a) memset(a, 0, sizeof a)

using namespace std;

namespace Solve {
	const int MAXN = 100010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*e[MAXN];
	inline void Add(int x, int y) {
		e[x] = new Edge(y, e[x]);
		e[y] = new Edge(x, e[y]);
	}

	struct Node {
		int x; Node *l, *r;
		Node(int _x = 0):x(_x){l = r = 0;}
	}*stack[MAXN]; int top = 0;
	inline Node* merge(Node *L, Node *R) {
		if (L == NULL) return R;
		if (R == NULL) return L;
		if (L->x > R->x) swap(L, R);
		return L->r = merge(L->r, R), swap(L->l, L->r), L;
	}

	int a[MAXN], n, b[MAXN], color[MAXN];

	void Dfs(int u, int f, int c) {
		color[u] = c;
		for (Edge *p = e[u]; p; p = p->next) if (p->y != f) Dfs(p->y, u, c ^ 3);
	}

	int A[MAXN], B[MAXN], C[MAXN], ta = 0, tb = 0, tc = 0, pos[MAXN];
	vector<int> Ans;

	inline void solve(void) {
		n = ScanInt();
		cl(color); cl(A); cl(B); cl(C), cl(pos), cl(e), cl(b), cl(a), cl(stack); top = ta = tb = tc = 0; Ans.resize(0);
		for (int i = 1; i <= n; i++) pos[a[i] = ScanInt()] = i; b[n] = a[n];
		for (int j = n - 1; j >= 1; j--) b[j] = min(b[j + 1], a[j]);
		for (int i = 1; i <= n; i++) {
			Node *tmp = new Node(a[i]);
			while (top && stack[top]->x < a[i]) Add(pos[stack[top]->x], i), tmp = merge(tmp, stack[top--]);
			stack[++top] = tmp;
			while (top) {
				while (stack[top] && stack[top]->x < b[i + 1]) stack[top] = merge(stack[top]->l, stack[top]->r);
				if (!stack[top]) top--; else break;
			}
		}
		for (int i = 1; i <= n; i++) if (!color[i]) Dfs(i, 0, 1);
		A[0] = B[0] = n + 1; top = 1;
		for (int i = 1; i <= n * 2; i++) {
			if (A[ta] > a[top] && color[top] == 1) A[++ta] = a[top++], Ans.push_back(1);
			else if (A[ta] == C[tc] + 1) C[++tc] = A[ta--], Ans.push_back(2);
			else if (B[tb] > a[top] && color[top] == 2) B[++tb] = a[top++], Ans.push_back(3);
			else if (B[tb] == C[tc] + 1) C[++tc] = B[tb--], Ans.push_back(4);
			else {puts("0"); return;}
		}
		for (int i = 0; i < (int)Ans.size() - 1; i++) printf("%c ", Ans[i] + 'a' - 1);
		printf("%c\n", Ans[Ans.size() - 1] + 'a' - 1);
	}
}

int main(void) {
	freopen("in", "r", stdin);
	int kase; scanf("%d", &kase); while (kase--)
	Solve::solve();
	return 0;
}

