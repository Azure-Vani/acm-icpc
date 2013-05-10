#include <cstdio>
const int MAXN = 202;
bool a[MAXN][MAXN];
int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= m; i++) scanf("%d%d", &x, &y),
	a[x][y] = a[y][x] = true;
	int Ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			for (int k = j + 1; k <= n; k++)
				if (!(a[i][j]||a[j][k]||a[k][i]))
					Ans++;
	printf("%d\n", Ans);
}