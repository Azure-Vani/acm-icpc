//#define Debug
#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 105;

	int m, n;

	class Pair {public:
		struct Limit{int l, r;}a[MAXN];
		int n;
		void Scan(void) {for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].l, &a[i].r);}
		bool Deal(int k) {
			bool ret = 0; unsigned int tmp = 1 << k - 1;
			for (int i = 1; i <= n; i++)
				ret |= (a[i].r >= tmp && a[i].l < (tmp << 1));
			return ret;
		}
		void Adjust(bool flag, int k) {
			unsigned int tmp = 1 << k - 1, limit = tmp << 1, max = 0, where = 0;
			bool Two = false;
			for (int i = 1; i <= n; i++) {
				if (a[i].l >= tmp) {
					Two = true;
				}
				if (a[i].l < tmp && a[i].r >= tmp && a[i].r > max)
					max = a[i].r, where = i;
			}

			for (int i = 1; i <= n; i++) {
				if (a[i].l >= tmp) a[i].l -= tmp, a[i].r -= tmp; else
				if (a[i].l < tmp && a[i].r >= tmp)
					a[i].l = a[i].r = tmp - 1;
			}
			if (where && flag && !Two) a[where].l = 0, a[where].r = max - tmp;
		}		
	}a[MAXN];

	void Input(void) {
		scanf("%d%d", &m, &n);
		for (int i = 1; i <= n; i++) scanf("%d", &a[i].n);
		for (int i = 1; i <= n; i++) a[i].Scan();
	}

	void solve(void) {
		Input();
		unsigned int Ans = 0;
		for (int i = 31; i >= 0; i--) {
			int OK = 1;
			for (int j = 1; j <= n; j++)
				OK &= a[j].Deal(i);
			for (int j = 1; j <= n; j++)
				a[j].Adjust(OK, i);
			Ans |= (OK << i - 1);
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
