#include <cstdio>
#include <cctype>
#include <algorithm>
#include <vector>
namespace Solve {
	const int MAXN = 300005;
	const int MAXC = 10005;

	inline int ScanInt(void) {
		int c, r;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	int n, m, Q;
	struct pair {
		int value, index;
		inline friend bool operator <(const pair &a, const pair &b) {return a.value < b.value;}
	}a[MAXN];
	struct Node {
		int value, sum;
	}f[20][MAXN];

	void Build(int h, int l, int r) {
		if (l == r) return;
		int mid = (l + r) >> 1, L = 0;
		for (int i = l; i <= r; i++)
			if (f[h][i].value <= mid) 
				f[h + 1][l + L++].value = f[h][i].value, f[h][i].sum = L;
			else
				f[h + 1][mid + (i - l - L) + 1].value = f[h][i].value, f[h][i].sum = L;
		Build(h + 1, l, mid); Build(h + 1, mid + 1, r);
	}
	inline int Ask(int l, int r, int k) {
		int L = 1, R = n, h = 0;
		while (l != r) {
			int mid = (L + R) >> 1;
			int lsum = 0, rsum = 0;
			if (l > L) lsum = f[h][l - 1].sum;
			rsum = f[h][r].sum;
			if (rsum - lsum >= k) h++, R = mid, l = L + lsum, r = L + rsum - 1;
			else h++, k -= rsum - lsum, l = mid + (l - L + 1) - lsum, r = mid + (r - L + 1) - rsum, L = mid + 1;
		}
		return a[f[h][l].value].value;
	}

	std::vector<int> T[MAXC];

	void Input(void) {
		n = ScanInt(), m = ScanInt();
		for (int i = 1; i <= n; i++) a[i].value = ScanInt(), a[i].index = i, T[a[i].value].push_back(i);
		std::sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) f[0][a[i].index].value = i;
		Build(0, 1, n);
	}

	inline int Cal(int t, int l, int r) {
		return std::distance(std::lower_bound(T[t].begin(), T[t].end(), l), std::lower_bound(T[t].begin(), T[t].end(), r + 1));
	}
	void solve(void) {
		Input();
		Q = ScanInt();
		for (int i = 1; i <= Q; i++) {
			int l = ScanInt(), r = ScanInt();
			int t = Ask(l, r, (r - l + 2) >> 1);
			int Tim = Cal(t, l, r);
			if (Tim > (double(r - l + 1) / 2.0)) printf("yes %d\n", t); else puts("no");
		}
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
