#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define No struct Node

#define MAXN 1205
#define MOD 1200007

typedef unsigned long long hash_t;
int row_base = 13331, col_base = 10007;
int kase, n, m, T_T, N, M, i, j, a[MAXN][MAXN], b[MAXN][MAXN], Ans;
hash_t hash[MAXN][MAXN], row[MAXN], col[MAXN];

int get(void) {int c; while (c = getchar(), c != '0' && c != '*') ; return c == '*';}

hash_t getH(int x1, int y1, int x2, int y2) {
	hash_t ret = 0;
	ret = hash[x2][y2] - (hash[x1 - 1][y2] * col[x2 - x1 + 1]);
	ret -= hash[x2][y1 - 1] * row[y2 - y1 + 1];
	ret += hash[x1 - 1][y1 - 1] * col[x2 - x1 + 1] * row[y2 - y1 + 1];
	return ret;
}

hash_t Make(int (*a)[MAXN], int n, int m) {
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			hash[i][j] = hash[i][j - 1] * row_base + a[i][j];
	for (i = 1; i <= n; i++)
		for (j = 1; j <= m; j++)
			hash[i][j] += hash[i - 1][j] * col_base;
	return hash[n][m];
}

struct Node{
	hash_t y; No *next;
}*e[MOD], DATA[MAXN * MAXN], *pid = DATA;

void ins(hash_t h) {
	int t = h % MOD;
	No *tmp = pid++; 
	tmp->y = h;
	tmp->next = e[t]; e[t] = tmp;
}

int Cal(hash_t h) {
	int t = h % MOD;
	No *p; for (p = e[t]; p; p = p->next) if (p->y == h) return 1;
	return 0;
}

int main(void) {
	freopen("in", "r", stdin);
	int kase = 0;
	row[0] = col[0] = 1;
	for (i = 1; i <= 1000; i++) row[i] = row[i - 1] * row_base, col[i] = col[i - 1] * col_base;
	while (scanf("%d%d%d%d%d\n", &n, &m, &T_T, &N, &M), n || m || T_T || N || M) {
		for (i = 1; i <= n; i++)
			for (j = 1; j <= m; j++) a[i][j] = get();
		Make(a, n, m);
		pid = DATA; memset(DATA, 0, sizeof DATA); memset(e, 0, sizeof e);
		for (i = N; i <= n; i++)
			for (j = M; j <= m; j++) {
				hash_t tmp = getH(i - N + 1, j - M + 1, i, j);
				ins(tmp);
			}
		Ans = 0;
		while (T_T--) {
			for (i = 1; i <= N; i++)
				for (j = 1; j <= M; j++)
					b[i][j] = get();
			hash_t tmp = Make(b, N, M);
			Ans += Cal(tmp);
		}
		printf("Case %d: %d\n", ++kase, Ans);
	}
	return 0;
}

