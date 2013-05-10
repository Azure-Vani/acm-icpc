//#define Debug
#include <cstdio>
#include <algorithm>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef unsigned long long Int64;
	const int MAXN = 1000050;
	const int inf = 1050000000;
	
	int a[MAXN], n, stack[MAXN], top;
	
	void Input(void) {
		scanf("%d", &n);
		a[0] = a[n + 1] = inf;
		for (int i = 1; i <= n; i++) scanf("%d", a + i);
	}

	Int64 Ans = 0;
	void solve(void) {
		Input();
		stack[++top] = a[0], stack[++top] = a[1];
		for (int i = 2; i <= n + 1; i++) {
			while (!(i == n + 1 && top == 2) && top && a[i] >= stack[top]) Ans += (Int64) std::min(stack[top - 1], a[i]), top--;
			stack[++top] = a[i];
		}
		printf(LL "\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
