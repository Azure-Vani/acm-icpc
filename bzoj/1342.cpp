//#define Debug
#include <cstdio>
#include <algorithm>
#include <list>
namespace Solve {
	const int MAXN = 1000050;

	int n, m, k, a[MAXN];
	void Input(void) {
		scanf("%d%d%d", &n, &m, &k);
		for (int i = 1; i <= n; i++)
			scanf("%d", a + i);
	}
	
	struct pair {
		int d, index;
		pair(int d, int index):d(d), index(index){}
	};

	void solve(void) {
		Input();
		std::list<pair> Max;
		std::list<pair> Min;
		bool fuck = false;
		for (int i = 1; i <= n; i++) {
			while (!Max.empty() && a[i] >= Max.back().d) Max.pop_back();
			while (!Min.empty() && a[i] <= Min.back().d) Min.pop_back();
			Max.push_back(pair(a[i], i));
			Min.push_back(pair(a[i], i));
			if (i - Max.front().index + 1 > m) Max.pop_front();
			if (i - Min.front().index + 1 > m) Min.pop_front();
			if (i >= m && Max.front().d - Min.front().d <= k)
				printf("%d\n", i - m + 1), fuck = true;
		}
		if (!fuck) puts("NONE");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
