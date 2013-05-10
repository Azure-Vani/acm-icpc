#include <cstdio>
#include <cstdlib>
const int MAXN = 4500;
int n, P;
int f[2][MAXN];
int main(int argc, char** argv) {
	scanf("%d %d", &n, &P);--n; if (!n) {printf("%d\n", 1 % P); exit(0);}
	bool now = 0, old = 1;
	f[now][1] = 1;
	for (int i = 2; i <= n; i++) {
		now ^= 1, old ^= 1;
		f[now][0] = 0;
		for (int j = 1; j <= n; j++) {
			f[now][j] = f[now][j - 1];
			if (i > j) {
				f[now][j] += f[old][i - j];
				if (f[now][j] > P) f[now][j] -= P;
			}
		}
	}
	int Ans = 0;
	for (int i = 1; i <= n; i++)
		Ans += f[now][i], Ans %= P;
	printf("%d\n", (Ans << 1) % P);
	return 0;
}
