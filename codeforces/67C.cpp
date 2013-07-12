#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 4010;

char s1[MAXN], s2[MAXN];

int t1, t2, t3, t4, n, m;
int f[MAXN][MAXN], S1[MAXN][26], S2[MAXN][26];

inline void Update(int &ret, int i, int j) {
	if (i > 0 && j > 0) ret = min(ret, f[i - 1][j - 1] + ((s1[i] != s2[j]) * t3));
	if (i > 0) ret = min(ret, f[i - 1][j] + t2);
	if (j > 0) ret = min(ret, f[i][j - 1] + t1);
}

inline int get(int S[][26], int t, int c) {
	return S[t][c - 'a'];
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d%d%d%d", &t1, &t2, &t3, &t4);
	scanf("%s", s1 + 1); scanf("%s", s2 + 1);
	n = strlen(s1 + 1), m = strlen(s2 + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 0; j < 26; j++) S1[i][j] = S1[i - 1][j];
		S1[i][s1[i] - 'a'] = i;
	}
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < 26; j++) S2[i][j] = S2[i - 1][j];
		S2[i][s2[i] - 'a'] = i;
	}
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) if (i || j) {
			int &ret = f[i][j]; ret = 1000000000;
			Update(ret, i, j);
			if (i > 1 && j > 1) {
				int p1 = get(S2, j - 1, s1[i]), p2 = get(S1, i - 1, s2[j]);
				if (p1 && p2) ret = min(ret, f[p2 - 1][p1 - 1] + t4 + t1 * (j - p1 - 1) + t2 * (i - p2 - 1));
			}
		}
	}
	printf("%d\n", f[n][m]);
	return 0;
}

