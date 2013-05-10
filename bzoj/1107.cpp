//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <vector>
namespace Solve {
	typedef std::vector<int> VII;
	const int MAXN = 100010;
	const int inf = 1050000000;

	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n, L, p, k;
	VII left[MAXN], right[MAXN];

	inline void Input(void) {
		n = ScanInt(), L = ScanInt(), p = ScanInt(), k = ScanInt();
		for (int i = 1; i <= p; i++) {
			int index = ScanInt() + 1, value = ScanInt(), dir = ScanInt();
			if (dir == 0)
				right[n - index + 2].push_back(value);
			else
				left[index].push_back(value);
		}
	}

	int g[MAXN];

	inline int Binary(int x, int r) {
		int l = 1;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (x <= g[mid])
				l = mid + 1;
			else
				r = mid - 1;
		}
		return l;
	}

	inline void Gao(VII a[], int f[]) {
		memset(g, 0, sizeof g);
		int L = 0;
		for (int i = 1; i <= n; i++) {
			std::sort(a[i].begin(), a[i].end());
			f[i] = std::min(f[i - 1] + 1, i - 1);
			for (int j = 0; j < a[i].size(); j++) {
				int t = Binary(a[i][j], L);
				if (t > L) L = t;
				g[t] = a[i][j];
				f[i] = std::min(f[i], i - L - 1);
			}
		}
	}

	int f_to_left[MAXN], f_to_right[MAXN];
	inline void Prepare(void) {
		Gao(left, f_to_left);
		Gao(right, f_to_right);
		std::reverse(f_to_right + 1, f_to_right + n + 1);
	}

	inline bool Check(int L) {
		for (int i = 1; i + L - 1<= n; i++)
			if (f_to_right[i] + f_to_left[i + L - 1] <= k)
				return true;
		return false;
	}

	inline int Work(void) {
		int l = 1, r = n;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (Check(mid))
				l = mid + 1;
			else
				r = mid - 1;
		}
		for (int i = 1; i <= n; i++) 
			r-= (f_to_left[i] == 0 && f_to_right[i] == 0);
		return r;
	}

	inline void solve(void) {
		Input();
		Prepare();
		printf("%d\n", Work());
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
