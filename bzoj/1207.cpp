#include <cstdio>
#define abs(x) ((x)<0?(-(x)):(x))
#define max(a, b) ((a)>(b)?(a):(b))
int n, m, T[10050], X[10050], Y[10050], f[10050];
int main(int argc, char** argv) {
	scanf("%d%d", &n, &m);
	int Ans = 1;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d", T + i, X + i, Y + i);
		f[i] = 1;
		for (int j = i - 1; j >= 1; j--)
			if (abs(X[i] - X[j]) + abs(Y[i] - Y[j]) <= T[i] - T[j])
			f[i] = max(f[i], f[j] + 1);
		Ans = max(Ans, f[i]);
	}
	printf("%d\n", Ans);
	return 0;
}
