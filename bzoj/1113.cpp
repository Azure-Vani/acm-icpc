//#define Debug
#include <cstdio>
#include <algorithm>
#include <stack>
namespace Solve {
	const int MAXN = 250020;

	int n, cnt, a[MAXN];
	void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) {
			scanf("%*d%d", &a[i]);
		}
	}

	void solve(void) {
		Input();
		std::stack<int> T;
		int Ans = 0;
		for (int i = 1; i <= n; i++) {
			Ans++;
			while (T.size() && T.top() > a[i]) T.pop();
			if (T.size() && T.top() == a[i]) Ans--;
			T.push(a[i]);
		}
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
