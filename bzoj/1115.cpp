//#define Debug
#include <cstdio>
namespace Solve {
	int n, a[1005];
	void solve(void) {
		scanf("%d", &n);
		int sg = 0, P = (n & 1) ^ 1;
		for (int i = 1; i <= n; i++)
			scanf("%d", a + i);
		for (int i = 1; i <= n; i++)
			if ((i & 1) ^ P)
				sg ^= a[i] - a[i - 1];
		puts(sg?"TAK":"NIE");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	int __; scanf("%d", &__);
	while (__--)
		Solve::solve();
	return 0;
}
