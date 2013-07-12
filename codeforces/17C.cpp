#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 155, mod = 51123987;

int n, f[MAXN][55][55][55], next[MAXN][30]; char ch[MAXN];

inline void Add(int &ret, int x) {
	ret += x; if (ret >= mod) ret -= mod;
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d", &n); scanf("%s", ch + 1); int t = n / 3 + 3; f[0][0][0][0] = 1;
	for (int i = 0; i <= n; i++) {
		for (int j = 'a'; j <= 'c'; j++) {
			int t = i;
			while (ch[t] != j && t <= n) t++;
			next[i][j - 'a'] = t;
		}
	}
	int Ans = 0;
	for (int i = 0; i <= n; i++) {
		for (int a = 0; a <= t; a++)
			for (int b = 0; b <= t; b++)
				for (int c = 0; c <= t; c++) {
					if (!f[i][a][b][c]) continue;
					int tmp = f[i][a][b][c];
					if (a + b + c == n && abs(a - b) <= 1 && abs(a - c) <= 1 && abs(c - b) <= 1) {
						Add(Ans, tmp);
					}
					Add(f[next[i][0]][a+1][b][c], tmp);
					Add(f[next[i][1]][a][b+1][c], tmp);
					Add(f[next[i][2]][a][b][c+1], tmp);
				}
	}
	printf("%d\n", Ans);
	return 0;
}

