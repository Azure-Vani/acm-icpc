/*
  Hint: aj <= ai + p - sqrt(|i - j|)
	aj + sqrt(|i - j|) - ai <= p
	So it's necessary to find the maximum aj+sqrt(|i-j|) for i.
	Prove the monotonicity: 
	Assume j < k < i and a[k] + sqrt(i - k) >= a[j] + sqrt(i - j),
	a[k] - a[j] >= sqrt(i - j) - sqrt(i - k), 
	i - j >= i - k, 
	a[k] - a[j] >= sqrt((i + 1) - j) - sqrt((i + 1) - k).
	So we can use a monotonic stack to improve the algorithm, O(nlgn).
*/

//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cmath>
namespace Solve {
	const int MAXN = 500050;

	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n, a[MAXN];
	void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) a[i] = ScanInt();
	}

	struct Interval {
		int l, r, where;
	}stack[MAXN];
	
	inline double Sum(int l, int r) {
		return a[l] + (sqrt(r - l));
	}

	inline int BinarySearch(int now, int L) {
		int l = std::max(stack[L].l, now), r = stack[L].r;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (Sum(stack[L].where, mid) < Sum(now, mid))
				r = mid - 1;
			else
				l = mid + 1;
		}
		return l;
	}

	inline void Gao(int ret[]) {
		memset(stack, 0, sizeof stack);
		int top = 1;
		stack[top].l = 1, stack[top].r = n, stack[top].where = 1;
		for (int i = 1; i <= n; i++) {
			int Base = 0;
			for (int j = top; Base = stack[j].where, stack[j].l > i; j--) {}
			ret[i] = std::max(a[Base] + (int)ceil(sqrt(i - Base)), a[i]);
			while (top > 0 && stack[top].l >= i && Sum(stack[top].where, stack[top].l) < Sum(i, stack[top].l)) top--;
			int t = BinarySearch(i, top);
			if (t > n) continue;
			if (t == stack[top].l) top--;
			else stack[top].r = t - 1;
			stack[++top].l = t, stack[top].r = n, stack[top].where = i;
		}
	}

	int L[MAXN], R[MAXN];
	void solve(void) {
		Input();
		Gao(L);
		std::reverse(a + 1, a + n + 1);
		Gao(R);
		std::reverse(R + 1, R + n + 1);
		for (int i = 1; i <= n; i++)
			printf("%d\n", std::max(L[i], R[i]) - a[n - i + 1]);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("pio.in", "r", stdin);
		freopen("pio.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
