#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <cctype>
#define X first
#define Y second
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define rep(i,n) for(int i = 1; i <= n; i++)

using namespace std;

const int MAXN = 600010;

int n, m, c[MAXN], w[MAXN], k, K, list[MAXN], Ans[MAXN];long long dw[MAXN];
int lstack[MAXN], rstack[MAXN], vis[MAXN], cur;

pair<int, int> q[MAXN], dq[MAXN];

void solve(int l, int r, int ml, int mr) {
	if (ml > mr) return;
	int mid = (l + r) >> 1, L = l * 2, R = (mid + 1) * 2, p1 = L, p2 = ml; 
	sort(q + L, q + R);
	long long S = 0;
	while (p1 < R || p2 <= mr) {
		if ((p1 < R && q[p1].X <= list[p2]) || p2 > mr) S += q[p1++].Y;
		else {
			if (dw[c[list[p2]]] <= w[c[list[p2]]]) dw[c[list[p2]]] += S;
			++p2;
		}
	}
	int ls = 0, rs = 0; cur++;
	REP(i,ml,mr) if (vis[c[list[i]]] != cur && w[c[list[i]]] <= dw[c[list[i]]]) lstack[++ls] = list[i]; else {
		rstack[++rs] = list[i];
		if (vis[c[list[i]]] != cur) vis[c[list[i]]] = cur, w[c[list[i]]] -= dw[c[list[i]]];
	}
	REP(i,L,R - 1) q[i] = dq[i];
	REP(i,ml,mr) dw[c[list[i]]] = 0;
	if (l == r) {rep(i,ls) Ans[c[lstack[i]]] = l; rep(i,rs) Ans[c[rstack[i]]] = l + 1; return;}
	rep(i,ls) list[ml + i - 1] = lstack[i];
	rep(i,rs) list[ml + ls + i - 1] = rstack[i];
	solve(l, mid, ml, ml + ls - 1);
	solve(mid + 1, r, ml + ls, mr);
}

int main(void) {
	scanf("%d%d", &n, &m); memset(Ans, -1, sizeof Ans);
	rep(i,m) scanf("%d", c + i), c[i + m] = c[i];
	rep(i,m*2) list[i] = i;
	rep(i,n) scanf("%d", w + i); scanf("%d", &k);
	rep(i,k) {
		int x, y, z;
		scanf("%d%d%d", &x, &y, &z);
		if (x > y) y += m;
		q[K].X = x, q[K].Y = z; dq[K] = q[K]; K++;
		q[K].X = y + 1, q[K].Y = -z; dq[K] = q[K];K++;
	}
	solve(0, k - 1, 1, m * 2);
	for (int i = 1; i <= n; i++) if (Ans[i] >= 0 && Ans[i] < k) printf("%d\n", Ans[i] + 1); else puts("NIE");
	return 0;
}
