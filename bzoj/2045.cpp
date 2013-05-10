#include <cstdio>
#include <algorithm>
long long f[1000500];
int main(int argc, char** argv) {
	int n, m, d;
	scanf("%d%d%d", &n, &m, &d);
	if (n > m) std::swap(n, m);
	for (long long i = n; i >= d; i--) {
		f[i] = (n / i) * (m / i);
		for (int j = 2; j * i <= n; j++)
			f[i] -= f[j * i];
	}
	printf("%lld\n", f[d]);
	return 0;
}
