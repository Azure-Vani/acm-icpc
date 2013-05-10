//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	const int MAXN = 2000000;

	struct Node {
		Node *p, *next[3]; int val; 
		Node(int _val = 0):p(NULL), val(_val){
			next[0] = next[1] = next[2] = NULL;
		}
	}*root, *last;


	inline void Add(int x) {
		Node *p = last;
		Node *np = new Node(p->val + 1);
		while (p && !p->next[x]) 
			p->next[x] = np, p = p->p;
		if (p == 0) {
			np->p = root;
		} else {
			Node *q = p->next[x];
			if (q->val == p->val + 1) {
				np->p = q;
			} else {
				Node *nq = new Node(p->val + 1);
				memcpy(nq->next, q->next, sizeof q->next);
				nq->p = q->p;
				q->p = np->p = nq;
				while (p && p->next[x] == q) 
					p->next[x] = nq, p = p->p;
			}
		}
		last = np;
	}

	int n, m; char ch[MAXN]; int g[MAXN];
	int f[MAXN];
	pair<int, int> d[MAXN];

	inline int Cal(int L, int n) {/*
		for (int i = 1; i <= n; i++) {
			f[i] = f[i - 1];
			for (int j = i - g[i]; j <= i - L; j++) {
				f[i] = max(f[i], f[j] - j + i);
			}
		}*/
		d[1] = mp(0, 0);
		int head = 1, tail = 1, pos = 1; for (int i = 1; i <= L; i++) f[i] = 0;
		for (int i = L; i <= n; i++, pos++) {
			while (head <= tail && d[head].first < i - g[i]) head++;
			if (head > tail) f[i] = max(f[i - 1], 0); else f[i] = max(f[i - 1], d[head].second + i);
			while (head <= tail && f[pos] - pos >= d[tail].second) tail--;
			d[++tail] = mp(pos, f[pos] - pos);
		}
		return f[n];
	}

	inline void solve(void) {
		root = new Node; last = root;
		scanf("%d%d\n", &n, &m);
		for (int i = 1; i <= m; i++) {
			if (i != 1) Add(2);
			scanf("%s\n", ch);
			for (char *p = ch; *p; ++p) {
				Add(*p - '0');
			}
		}
		for (int i = 1; i <= n; i++) {
			scanf("%s\n", ch); int L = strlen(ch);
			Node *tmp = root;
			for (char *p = ch; *p; ++p) {
				while (tmp->next[*p - '0'] == 0)
					tmp = tmp->p;
				g[p - ch  + 1] = min(g[p - ch], tmp->val) + 1;
				tmp = tmp->next[*p - '0'];
			}
	//		for (int i = 1; i <= L; i++) printf("%d ", g[i]); printf("\n");
			int l = 0, r = L;
			while (l <= r) {
				int mid = (l + r) >> 1;
				int res = Cal(mid, L);
				if (res < L * 0.9 - 1e-6)
					r = mid - 1;
				else
					l = mid + 1;
			}
			printf("%d\n", r);
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
