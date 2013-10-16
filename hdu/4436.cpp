#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 120000;

struct Node {
	Node *next[11], *par; int val, end;
}POOL[MAXN << 1], *data, *root, *last;

inline void Add(int x) {
	Node *p = last, *np = data++;
	np->val = p->val + 1; np->end = true;
	while (p && !p->next[x]) 
		p->next[x] = np, p = p->par;
	if (p == 0) {
		np->par = root;
	} else {
		Node *q = p->next[x];
		if (q->val == p->val + 1) {
			np->par = q;
		} else {
			Node *nq = data++;
			nq->val = p->val + 1;
			memcpy(nq->next, q->next, sizeof q->next);
			nq->par = q->par;
			np->par = q->par = nq;
			while (p && p->next[x] == q)
				p->next[x] = nq, p = p->par;
		}
	}
	last = np;
}

int n, Len, f[MAXN << 1], S, g[MAXN << 1], inp[MAXN << 1];Node *d[MAXN << 1];
char ch[MAXN], *tmp;

inline void clear(void) {
	memset(POOL, 0, sizeof POOL);
	memset(ch, 0, sizeof ch);
	memset(f, 0, sizeof f);
	memset(g, 0, sizeof g);
	memset(inp, 0, sizeof inp);
	data = POOL;
	tmp = ch;
	Len = 0;
}

int main(void) {
//	freopen("in", "r", stdin);
	while (scanf("%d", &n) == 1) {
		clear();
		for (int i = 1; i <= n; i++) {
			scanf("%s", tmp); int t = strlen(tmp);
			tmp += t; Len += t + 1;
			*tmp++ = '9' + 1;
		}
		root = last = data++;
		for (int i = 0; i < Len; i++) Add(ch[i] - 48);
		for (Node *p = POOL; p != data; p++) {
			for (int j = 0; j <= 10; j++) if (p->next[j])
				inp[p->next[j] - POOL]++;
		}
		int head = 1, tail = 1; d[1] = root;
		int Ans = 0; g[0] = 1;
		while (head <= tail) {
			Node *now = d[head++];
			Ans = (Ans + f[now - POOL]) % 2012;
			for (int j = 0; j <= 10; ++j) if (now->next[j]) 
				if (!--inp[now->next[j] - POOL]) d[++tail] = now->next[j];
			for (int j = now == root; j <= 10; ++j) if (now->next[j]) {
				if (j < 10) f[now->next[j] - POOL] = (f[now->next[j] - POOL] + f[now - POOL] * 10 + g[now - POOL] * j) % 2012;
				if (j < 10) g[now->next[j] - POOL] = (g[now->next[j] - POOL] + g[now - POOL]) % 2012;
			}
		}
		printf("%d\n", Ans);
	}
	return 0;
}

