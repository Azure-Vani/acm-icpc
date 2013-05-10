#include <cstdio>
#include <algorithm>
#include <map>
#include <cstring>
#include <cassert>
#include <cctype>

using namespace std;

namespace Solve {
	const int MAXN = 300010;
	const int MOD = 1200007;
	const int base = 13331;
	const int B = 39989;
	
	typedef unsigned long long Int64;

	Int64 pow[MAXN];

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	inline int ScanChr(void) {
		int c; while (!islower(c = getchar()));
		return c;
	}

	struct Seg {
		int l, r, s; Seg *ch[2];
		Seg():l(0), r(0), s(0){ch[0] = ch[1] = NULL;}
	}*root[MAXN];

	inline Seg* Build(int l, int r) {
		Seg *ret = new Seg();
		ret->l = l, ret->r = r;
		if (l == r) return ret;
		int mid = (l + r) >> 1;
		ret->ch[0] = Build(l, mid);
		ret->ch[1] = Build(mid + 1, r);
		return ret;
	}

	inline Seg* Insert(Seg *now, int h) {
		Seg *ret = new Seg(); *ret = *now; ret->s++;
		if (ret->l == ret->r) return ret;
		int mid = (now->l + now->r) >> 1, d = (h > mid);
		ret->ch[d] = Insert(now->ch[d], h);
		ret->ch[!d] = now->ch[!d];
		return ret;
	}

	inline int Cal(Seg *now, int l, int r) {
		if (l > r) return 0;
		if (l <= now->l && now->r <= r) return now->s;
		int mid = (now->l + now->r) >> 1;
		return Cal(now->ch[0], l, min(r, mid)) + Cal(now->ch[1], max(l, mid + 1), r);
	}

	inline int getH(int x, int y) {
		return ((long long)x * B + y) % MOD;
	}

	struct Query {
		int type, x, y, c;
	}Q[MAXN];

	int m, S_cnt = 1;
	inline void Input(void) {
		m = ScanInt();
		for (int i = 1; i <= m; i++) {
			Q[i].type = ScanInt(), Q[i].x = ScanInt();
			if (Q[i].type == 1) {Q[i].c = ScanChr() - 'a'; continue;}
			Q[i].y = ScanInt();
			if (Q[i].type == 2) Q[i].c = ScanChr() - 'a';
		}
	}

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*a[MAXN], *e[MAXN << 1];

	struct edge {
		int l, r, index; edge *next;
		edge(int l, int r, int index, edge *next):l(l), r(r), index(index), next(next){}
	}*h[MOD];
	inline void ins(int l, int r, int index) {
		int tmp = getH(l, r);
		h[tmp] = new edge(l, r, index, h[tmp]);
	}
	inline int get(int l, int r) {
		int tmp = getH(l, r);
		for (edge *p = h[tmp]; p; p = p->next) if (p->l == l && p->r == r) return p->index;
		return -1;
	}

	int n = 1, ch[MAXN], father[MAXN], depth[MAXN], d[MAXN], end[MAXN];
	int f[20][MAXN], log2[MAXN];

	map<int, int> fim[MAXN];

	inline int up(int u, int h) {
		while (h) u = f[log2[h & -h]][u], h -= h & -h;
		return u;
	}

	Int64 s_hash[MAXN];

	inline void Make_S_Trie(void) {
		end[1] = 1; ch[1] = -1;
		for (int i = 1; i <= m; i++) if (Q[i].type == 1) {
			int w = end[Q[i].x], c = Q[i].c;
			if (!fim[w].count(c)) {
				fim[w][c] = ++n, ch[n] = c;
				a[w] = new Edge(n, a[w]);
				father[n] = w;
				depth[n] = depth[w] + 1;
			}
			end[++S_cnt] = fim[w][c];
		}
		int head = 1, tail = 1; d[1] = 1;
		while (head <= tail) {
			int now = d[head++];
			f[0][now] = father[now];
			for (int i = 1; (1 << i) <= depth[now]; i++) f[i][now] = f[i - 1][f[i - 1][now]];
			for (Edge *p = a[now]; p; p = p->next) {
				d[++tail] = p->y;
				s_hash[p->y] = s_hash[now] * base + ch[p->y] + 1;
			}
		}
	}

	inline Int64 treeHash(int x, int h) {
		int y = up(x, h);
		return s_hash[x] - s_hash[y] * pow[h];
	}

	struct Node {
		Node* go[26], *par; int val;
		Node(int _val = 0){val = _val; memset(go, 0, sizeof go);}
	}POOL[MAXN << 1], *data = POOL + 1;

	Node* last[MAXN << 1];

	inline Node* Add(Node *last, int x) {
		Node *p = last, *np = data++; np->val = p->val + 1;
		while (p && !p->go[x]) p->go[x] = np, p = p->par;
		if (!p) np->par = Solve::last[1];
		else {
			Node *q = p->go[x];
			if (p->val + 1 == q->val) {
				np->par = q;
			}else {
				Node *nq = data++; nq->val = p->val + 1;
				memcpy(nq->go, q->go, sizeof q->go);
				nq->par = q->par;
				q->par = np->par = nq;
				while (p && p->go[x] == q) p->go[x] = nq, p = p->par;
			}
		}
		return np;
	}

	int List[MAXN << 1], pos = 0; pair<int, int> interval[MAXN << 1];
	map<int, int> trans[MAXN << 1];
	int ter[MAXN << 1], Rcnt, position[MAXN << 1];

	inline void Dfs(int u) {
		interval[u].first = pos + 1;
		List[++pos] = u;
		for (int i = 0; i < 26; i++) if (trans[u].count(i)) Dfs(trans[u][i]);
		interval[u].second = pos;
	}

	int t_list[MAXN << 1];
	inline bool cmp(int x, int y) {
		return POOL[x].val < POOL[y].val;
	}

	inline void Make_S_SAM(void) {
		last[1] = data++;
		for (int i = 1; i <= n; i++) {
			for (Edge *p = a[d[i]]; p; p = p->next)
				last[p->y] = Add(last[d[i]], ch[p->y]);
		}
		Rcnt = data - POOL - 1;
		for (int i = 1; i <= n; i++) ter[last[i] - POOL] = i;
		for (int i = 2; i <= Rcnt; i++) {
			e[POOL[i].par - POOL] = new Edge(i, e[POOL[i].par - POOL]);
		}
		for (int i = 1; i <= Rcnt; i++) t_list[i] = i;
		sort(t_list + 1, t_list + Rcnt + 1, cmp);
		for (int i = Rcnt; i >= 1; i--) {
			if (ter[t_list[i]]) position[t_list[i]] = ter[t_list[i]];
			else {
				for (Edge *p = e[t_list[i]]; p; p = p->next) if (position[p->y]) {position[t_list[i]] = position[p->y]; break;}
			}
			assert(position[t_list[i]] != 0);
		}
		for (int i = 1; i <= Rcnt; i++) {
			for (Edge *p = e[i]; p; p = p->next) {
				int w = position[p->y];
				int c = up(w, POOL[i].val);
				trans[i][ch[c]] = p->y;
			}
		}
		Dfs(1);
		root[1] = Build(1, pos);
		assert(pos == Rcnt);
		for (int i = 1; i <= n; i++) {
			for (Edge *p = a[d[i]]; p; p = p->next)
				root[p->y] = Insert(root[d[i]], interval[last[p->y] - POOL].first);
		}
		for (int i = 1; i <= Rcnt; i++) {
			ins(interval[i].first, interval[i].second, i);
		}
	}

	struct String {
		Int64 hash; int len, sta;
	}T[MAXN];

	int N = 1;

	inline int cmp1(int x, int y) {return x <= y;}
	inline int cmp2(int x, int y) {return x < y;}

	inline int Binary(int x, int y, int (*cmp)(int, int)) {
		int L = 1, R = pos, X = position[T[x].sta], Y = position[T[y].sta];
		while (L <= R) {
			int mid = (L + R) >> 1;
			int w = position[List[mid]];
			int l = 0, r = min(POOL[List[mid]].val, T[x].len + T[y].len);
			while (l <= r) {
				int m = (l + r) >> 1;
				Int64 h1 = 0, h2 = 0;
				if (m <= T[y].len) {
					h1 = treeHash(Y, m);
				} else {
					h1 = treeHash(X, m - T[y].len) * pow[T[y].len] + T[y].hash;
				}
				h2 = treeHash(w, m);
				if (h1 == h2) 
					l = m + 1;
				else
					r = m - 1;
			}
			int w2 = up(w, l - 1), w1 = 0;
			if (l <= T[y].len) 
				w1 = up(Y, l - 1);
			else
				w1 = up(X, l - T[y].len - 1);
			int tx = ch[w1], ty = ch[w2];
			if (l > T[x].len + T[y].len) tx = -1;
			if (l > POOL[List[mid]].val) ty = -1;
			if (tx == -1) tx = ty;
			if (cmp(tx, ty))
				R = mid - 1;
			else
				L = mid + 1;
		}
		return L;
	}

	inline void Process(void) {
		T[1].sta = 1; 
		for (int i = 1; i <= m; i++) if (Q[i].type != 1) {
			//printf("%d\n", i);
			if (Q[i].type == 2) {
				int w = Q[i].y, c = Q[i].c;
				++N;
				if (T[w].sta == 0) continue;
				T[N].len = T[w].len + 1;
				if (Q[i].x == 0) {
					T[N].hash = pow[T[w].len] * (c + 1) + T[w].hash;
					if (T[N].len <= POOL[T[w].sta].val) {
						int tmp = up(position[T[w].sta], T[w].len);
						if (ch[tmp] == c) T[N].sta = T[w].sta;
					}
					else if (trans[T[w].sta].count(c)) T[N].sta = trans[T[w].sta][c];
				}
				if (Q[i].x == 1) {
					T[N].hash = T[w].hash * base + (c + 1);
					if (POOL[T[w].sta].go[c]) T[N].sta = POOL[T[w].sta].go[c] - POOL;
				}
			}
			if (Q[i].type == 4) {
				int x = Q[i].x, y = Q[i].y;
				if (T[x].sta <= 1) {
					puts("0");
					continue;
				}
				int l = interval[T[x].sta].first, r = interval[T[x].sta].second;
				int Ans = Cal(root[end[y]], l, r);
				printf("%d\n", Ans);
			}
			if (Q[i].type == 3) {
				N++; 
				int x = Q[i].x, y = Q[i].y;
				if (T[x].sta == 0 || T[y].sta == 0) continue;
				if (T[x].sta == 1) {
					T[N] = T[y];
					continue;
				}
				if (T[y].sta == 1) {
					T[N] = T[x];
					continue;
				}
				int l = Binary(x, y, cmp1);
				int r = Binary(x, y, cmp2) - 1;
				int w = get(l, r);
				if (w == -1) continue; else {
					T[N].sta = w;
					T[N].len = T[x].len + T[y].len;
					T[N].hash = T[x].hash * pow[T[y].len] + T[y].hash;
				}
			}
		}
	}

	inline void solve(void) {
		Input(); pow[0] = 1;
		for (int i = 1; i <= m; i++) pow[i] = pow[i - 1] * base;
		Make_S_Trie();
		for (int i = 2; i <= n; i <<= 1) log2[i] = log2[i >> 1] + 1;
		Make_S_SAM();
		//for (int i = 1; i <= pos; i++) printf("%d ", ter[List[i]]); puts("");
		Process();
	}
}

int main(void) {
//	freopen("in", "r", stdin);
//	freopen("out", "w", stdout);
	Solve::solve();
	return 0;
}

