#include <cstdio>
#include <algorithm>
const int MAXN = 100050;
int a[MAXN], n;
int main(int argc, char** argv) {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	std::sort(a + 1, a + n + 1);
	int l = 1;
	long long Ans = 0;
	for (int i = 2; i <= n; i++) {
		while (l != i && double(a[l]) < 0.9 * double(a[i])) l++;
		Ans += i - l;
	}
	printf("%lld\n", Ans);
	return 0;
}
