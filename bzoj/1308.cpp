//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
namespace Solve {
	const int MAXN = 109;
	
	inline int Div(const int a[], int b[], int d) {
		int last = 0;
		for (int i = a[0]; i >= 1; i--)
			b[i] = (last * 10 + a[i]) / d, last = (last * 10 + a[i]) % d;
		b[0] = a[0];
		while (b[0] > 1 && !b[b[0]]) b[0]--;
		return last;
	}

	int mod2[] = {6, 2, 4, 8};
	int mod5[] = {1, 1, 2, 6, 4, 1, 6, 2, 6, 4};

	inline int Cal(const int a[]) {
		if (a[0] <= 1 && a[1] == 0) return 1;
		int b[MAXN] = {0};
		Div(a, b, 5);
		int tmp = Cal(b);
		int rest = (b[0] <= 1 && b[1] == 0) ? 1 : mod2[(b[2] * 10 + b[1]) & 3];
		return rest * tmp * mod5[a[1]] % 10;
	}

	int a[MAXN]; char ch[MAXN];

	void solve(void) {
		while (true) {
			if (scanf("%s\n", ch) == EOF) return;
			a[0] = strlen(ch);
			for (int i = 0; i < a[0]; i++) a[i + 1] = ch[i] - '0';
			std::reverse(a + 1, a + a[0] + 1);
			printf("%d\n", Cal(a));
		}
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
