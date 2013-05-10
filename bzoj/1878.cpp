#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 50050;
	const int MAXM = 200050;
	const int MAXS = 1000001;
	
	class TreeArray {
		public:
		int a[MAXN], n;
		#define Lowbit(x) ((x)&(-(x)))
		void Add(int k, int u) {
			for (int i = k; i <= n; i += Lowbit(i)) a[i] += u;
		}
		int Sum(int k) {
			int r = 0;
			for (int i = k; i > 0; i -= Lowbit(i)) r += a[i];
			return r;
		}
		int Get(int l, int r) {
			return Sum(r) - Sum(l - 1);
		}
	}T;
	
	int ScanInt(void) {
		int r = 0; int c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	struct pair {
		int l, r, i;
	}Q[MAXM];
	inline bool cmp(const pair& a, const pair& b) {
		return a.l == b.l ? a.r < b.r : a.l < b.l;
	}
	
	int n, m, c[MAXN];
	int last[MAXS], next[MAXN];
	
	void Input(void) {
		T.n = n = ScanInt();
		for (int i = 1; i <= n; i++) {
			c[i] = ScanInt();
			if (!last[c[i]]) T.Add(i, 1);
			next[ last[c[i]] ] = i;
			last[c[i]] = i;
		}
		
		m = ScanInt();
		for (int i = 1; i <= m; i++)
			Q[i].l = ScanInt(), Q[i].r = ScanInt(), Q[i].i = i;
		std::sort(Q + 1, Q + 1 + m, cmp);
	}
	
	int Ans[MAXM];
	void Work(void) {
		
		for (int i = 1; i <= m; i++) {
			int t = Q[i].i;
			Ans[t] = T.Get(Q[i].l, Q[i].r);
			
			if (Q[i].l != Q[i + 1].l) {
				for (int j = Q[i].l; j < Q[i + 1].l; j++)
					if (next[j]) T.Add(next[j], 1);
			}
		}
		for (int i = 1; i <= m; i++) printf("%d\n", Ans[i]);
	}
	
	void solve(void) {
		Input();
		Work();
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
