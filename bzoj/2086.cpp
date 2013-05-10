//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 1000050;
	const long long inf = 100000000000000000ll;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int a[MAXN], n, k, last;
	void Input(void) {
		n = ScanInt(), k = ScanInt();
		for (int i = 1; i <= n; i++) a[i] = ScanInt();
	}

	long long sum[MAXN];

	struct Node {
		int index;long long value;
		Node(long long v, int i):value(v), index(i){};
		Node(){}
	}Min[MAXN], Max[MAXN];

	void Work(int t) {
		int n1 = 0, n2 = 0;long long min = inf, max = -inf;
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + (a[i] += t);
		for (int i = 0, j = n; i <= n; i++, j--) {
			if (sum[i] <= min) {
				Min[++n1] = Node(sum[i], i);
				min = sum[i];
			}
			if (sum[j] >= max) {
				Max[++n2] = Node(sum[j], j);
				max = sum[j];
			}
		}
		int ret = 0, another = 1;
		for (int i = n2; i >= 1; i--) {
			while (another <= n1 && Min[another].value > Max[i].value) another++;
			if (another > n1) break;
			ret = std::max(ret, Max[i].index - Min[another].index);
		}
		printf("%d ", ret);
	}

	void solve(void) {
		Input();
		int t;
		while (k--) Work(last - (t = ScanInt())), last = t;
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("klo.in", "r", stdin);
		freopen("klo.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
