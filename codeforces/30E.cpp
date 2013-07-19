#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100010, inf = 1000000000;

char ch[MAXN];

int n;

struct Node {
	Node *p, *go[26]; int val, id, left;
	Node(int _val = 0):p(NULL), val(_val){left = inf; memset(go, 0, sizeof go);}
}*root, *last, POOL[MAXN << 1], *data = POOL;

inline Node* get(int id) {return POOL+ id;}

inline void Add(int x, int id) {
	Node *p = last;
	Node *np = data++; np->val = p->val + 1, np->id = id;
	while (p && !p->go[x]) p->go[x] = np, p = p->p;
	if (p == 0) {
		np->p = root;
	} else {
		Node *q = p->go[x];
		if (q->val == p->val + 1) {
			np->p = q;
		} else {
			Node *nq = data++; nq->val = p->val + 1;
			memcpy(nq->go, q->go, sizeof q->go);
			nq->p = q->p;
			q->p = np->p = nq;
			while (p && p->go[x] == q) p->go[x] = nq, p = p->p;
		}
	}
	last = np;
}

inline void Manacher(char a[], int n, int ret[]) {
	int MaxR = -1, where = 0;
	for (int i = 1; i <= n; i++) {
		int &it = ret[i]; it = 0;
		if (i <= MaxR) it = min(ret[where * 2 - i], MaxR - i);
		while (i - it - 1 >= 1 && i + it + 1 <= n && a[i - it - 1] == a[i + it + 1]) it++;
		if (it + i > MaxR) MaxR = it + i, where = i;
	}
}

struct Edge {
    int y; Edge *next;
    Edge(int y, Edge *next):y(y), next(next){}
}*a[MAXN << 1];

void Dfs(int u) {
    Node *now = get(u);
    if (now->id !=0) now->left = now->id; else now->left = inf;
    for (Edge *p = a[u]; p; p = p->next) {
        Dfs(p->y);
        now->left = min(now->left, get(p->y)->left);
    }
}

int ret[MAXN];
pair<int, int> f[MAXN];

int main(void) {
	freopen("in", "r", stdin);
	scanf("%s", ch + 1); n = strlen(ch + 1); if (n == 1) {printf("1\n1 1\n"); return 0;}
	root = data++; last = root;
	for (int i = 1; i <= n; i++) Add(ch[i] - 'a', i);
	Node *tmp = root;
	for (Node *p = POOL + 1; p != data; ++p) {
        a[p->p - POOL] = new Edge(p - POOL, a[p->p - POOL]);
    }
    Dfs(0);
	for (int i = n, L = 1; i >= 1; i--, L++) {
		if (tmp->go[ch[i] - 'a']) tmp = tmp->go[ch[i] - 'a']; else break;
		f[tmp->left] = make_pair(L, tmp->left);
	}
	for (int i = 1; i <= n; i++) f[i] = max(f[i], f[i - 1]);
	Manacher(ch, n, ret);
	int Ans = 0; pair<int, int> a1, a2, a3;
	for (int i = n; i >= 1; i--) {
		int len = f[i - ret[i] - 1].first;
		if (i + ret[i] + len > n) len = n - i - ret[i];
		if (Ans < 2 * ret[i] + 1 + len * 2) {
			Ans = 2 * ret[i] + 1 + len * 2;
			a1.first = f[i - ret[i] - 1].second - f[i-ret[i]-1] .first + 1;
			a1.second = len;
			a2.first = i - ret[i];
			a2.second = ret[i] * 2 + 1;
			a3.first = n - len + 1;
			a3.second = len;
		}
		if (tmp->go[ch[i] - 'a']) tmp = tmp->go[ch[i] - 'a'];
	}
//	printf("%d\n", Ans);
	if (a1.second != 0) {
		printf("3\n");
		printf("%d %d\n%d %d\n%d %d\n", a1.first, a1.second, a2.first, a2.second, a3.first, a3.second);
	} else {
		printf("1\n");
		printf("%d %d\n", a2.first, a2.second);
	}
	return 0;
}

