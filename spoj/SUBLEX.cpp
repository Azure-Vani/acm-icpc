#include <cstdio>
#include <cstring>
#include <algorithm>

#pragma GCC optimize("O2")

using namespace std;

namespace Solve {
	const int MAXN = 400000;

	char ch[MAXN], BUFFER[1000000], *pos = BUFFER; int n;
	inline bool ScanStr(char *ch) {
		int l = 0; while (!(*pos >= 'a' && *pos <= 'z') && *pos != '\0') pos++;
		if (*pos == '\0') return false;
		ch[l++] = *pos++;
		while (*pos >= 'a' && *pos <= 'z') ch[l++] = *pos++; ch[l] = '\0';
		return true;
	}
	inline int ScanInt(void) {
		int r = 0;
		while (!(*pos >= '0' && *pos <= '9')) pos++;
		r = *pos++ - '0';
		while ( *pos >= '0' && *pos <= '9') r = r * 10 + *pos++ - '0';
		return r;
	}

	struct Node {
		int val, c; Node *next[26], *par;
		Node(int val = 0):val(val),par(0){}
	}*root, *last, L[MAXN]; int pid = 0;
	
	inline void Add(int x) {
		Node *p = last, *np = L + (++pid); np->val = p->val + 1;
		while (p && !p->next[x]) p->next[x] = np, p = p->par;
		if (!p) np->par = root; 
		else {
			Node *q = p->next[x];
			if (p->val + 1 == q->val) {
				np->par = q;
			}else {
				Node *nq = L + (++pid); nq->val = p->val + 1;
				memcpy(nq->next, q->next, sizeof nq->next);
				nq->par = q->par;
				q->par = np->par = nq;
				while (p && p->next[x] == q) p->next[x] = nq, p = p->par;
			}
		}
		last = np;
	}

	inline void Add(long long &a, long long b) {
		a += b; if (a > 2147483648ll) a = 2147483648ll;
	}

	int d[MAXN], ws[MAXN];long long f[MAXN];
	bool vis[MAXN];

	char buf[90000 * 521];int tt = 0;

	void solve(void) {
		fread(BUFFER, 1, 1000000000, stdin);
		ScanStr(ch); n = strlen(ch); root = L + (++pid), last = root;
		for (int i = 0; i < n; i++) Add(ch[i] - 'a');
		for (int i = 1; i <= pid; i++) ws[L[i].val]++;
		for (int i = 1; i <= n; i++) ws[i] += ws[i - 1];
		for (int i = 1; i <= pid; i++) d[ws[L[i].val]--] = i;
		for (int i = pid; i >= 1; i--) {
			long long tmp = 0; int cnt = 0;
			Node *t = L + d[i];
			for (int j = 0; j < 26; j++) if (t->next[j]) { 
				Add(tmp, f[t->next[j] - L]); 
				t->next[cnt] = t->next[j];
				t->next[cnt++]->c = j;
			}
			t->next[cnt] = 0;
			Add(f[d[i]], tmp + 1);
		}
		int q = ScanInt(); 
		while (q--) {
			int k = ScanInt();
			Node *now = root;
			while (k) {
				for (int j = 0; now->next[j]; j++) if (k - f[now->next[j] - L] <= 0) {
					now = now->next[j];
					buf[tt++] = 'a' + now->c;
					k--;
					break;
				} else k -= f[now->next[j] - L];
			}
			buf[tt++] = '\n';
		}
		buf[tt] = '\0';
		fwrite(buf, 1, tt, stdout);
	}
}

int main(void) {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	Solve::solve();
	return 0;
}

