//#define Debug
#include <cstdio>
#include <algorithm>
#include <iostream>
namespace Solve {
	const int MAXN = 500050;

	int n, a[MAXN];
	void Input(void) {
		scanf("%d\n", &n);
		for (int i = 1; i <= n; i++) a[i] = (getchar() - '0' == 1) ? 2 : 0;
	}

	void Extend(int a[], int ret[]) {
		int where = 0, MaxR = 0;
		for (int i = 1; i < n; i++) {
			int it = 0;
			if (i <= MaxR) {
				it = std::min(ret[where * 2 - i], MaxR - i);
			}
			while (i + it < n && i - it >= 1 && a[i + it + 1] == 2 - a[i - it]) 
				it++;
			ret[i] = it;
			if (i + it - 1 > MaxR) {
				MaxR = i + it - 1;
				where = i;
			}
		}
	}

	int Ex[MAXN];
	void Work(void) {
		unsigned long long Ans = 0;
		for (int i = 1; i < n; i++) Ans += Ex[i];
		std::cout <<Ans<<std::endl;
	}

	void solve(void) {
		Input();
		Extend(a, Ex);
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
