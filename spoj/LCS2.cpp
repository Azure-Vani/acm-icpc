#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>

using namespace std;

namespace Solve {
	const int MAXN = 200010;

	struct Node {
		int val, num;
		Node *next[26], *par;
		Node(int val = 0):val(val), par(par){}
	}*root, *last, L[MAXN]; int pid = 0;

	char buf[1000020], *pos = buf;
	inline bool Gets(char *ch) {
		register int l = 0;
		while (!(*pos >= 'a' && *pos <= 'z') && *pos != '\0') pos++;
		if (*pos == '\0') return false;
		ch[l++] = *pos++;
		while (*pos >= 'a' && *pos <= 'z') ch[l++] = *pos++; ch[l] = '\0';
		return true;
	}

	inline void Add(int x) {
		register Node *p = last, *np = L + (++pid); np->val = p->val + 1, np->num = pid;
		while (p && p->next[x] == 0)
			p->next[x] = np, p = p->par;
		if (p == 0) np->par = root;
		else {
			Node *q = p->next[x];
			if (p->val + 1 == q->val) {
				np->par = q;
			}else {
				Node *nq = L + (++pid); nq->val = p->val + 1, nq->num =pid;
				memcpy(nq->next, q->next, sizeof q->next);
				nq->par = q->par;
				np->par = q->par = nq;
				while (p && p->next[x] == q) 
					p->next[x] = nq, p = p->par;
			}
		}
		last = np;
	}

	inline int Min(int a, int b) {return a < b ? a: b;}
	inline int Max(int a, int b) {return a > b ? a: b;}
	inline bool cmp(const int &x, const int &y) {return L[x].val < L[y].val;}

	char ch[MAXN]; int m, n, match[MAXN], min_match[MAXN], d[MAXN], ws[MAXN];

	inline void solve(void) {
		fread(buf, 1, 1000000000, stdin);
		Gets(ch);
		n = strlen(ch); 
		root = L + (++pid), last = root; root->num = pid;
		for (register int i = 0; i < n; i++) Add(ch[i] - 'a');
		for (register int i = 1; i <= pid; i++) min_match[i] = L[i].val, ws[L[i].val]++;
		for (register int i = 1; i <= n; i++) ws[i] += ws[i - 1];
		for (register int i = 1; i <= pid; i++) d[ws[L[i].val]--] = i;
		m = 1;
		while (Gets(ch)) {
			++m; Node *p = root; int l = strlen(ch), len = 0;
			for (register int i = 0; i < l; i++) {
				register int x = ch[i] - 'a';
				while (p && p->next[x] == 0) p = p->par;
				if (!p) p = root, len = 0; else {
					len = Min(len, p->val), p = p->next[x];
					match[p->num] = max(match[p->num], ++len);
				}
			}
			for (register int _ = pid; _ >= 2; _--) {
				register int i = d[_], f = L[i].par->num; 
				min_match[i] = Min(min_match[i], match[i]);
				match[f] = Max(Min(match[f], L[f].val), match[i]);
			}
			memset(match, 0, sizeof(match[0]) * (pid + 1));
		}
		int Ans = 0;
		for (register int i = 1; i <= pid; i++) Ans = Max(Ans, min_match[i]);
		if (m == 1) puts("1"); else printf("%d\n", Ans);
	}
}

int main(void) {
	Solve::solve();
	return 0;
}

