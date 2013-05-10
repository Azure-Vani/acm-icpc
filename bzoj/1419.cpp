#include <cstdio>
const int MAXN = 5002;
double f[2][MAXN] = {0};
#define max(a, b) ((a)>(b)?(a):(b))
int main(int argc, char** argv) {
	int B, R;
	scanf("%d%d", &R, &B);
	bool bef = 0, now = 1;
	for (int i = 1; i <= R; i++) {
		bef ^= 1, now ^= 1;
		f[now][0] = i;
		for (int j = 1; j <= B; j++)
			f[now][j] = max(( (f[bef][j] + 1) * i + (f[now][j - 1] - 1) * j) / (i + j), 0);
	}
	double T = f[now][B];
	int A = T;
	printf("%d.", A); T -= A; T *= 10;
	for (int i = 1; i <= 6; i++) {
		A = T; printf("%d", A); T -= A, T *= 10;
	}
	puts("");
	return 0;
}
