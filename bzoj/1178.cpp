//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <set>
#include <vector>
#include <map>
#include <cassert>

#define rep(i,l,r) for(int i = l; i <= r; i++)

namespace Solve {
	const int MAXN = 400020;
	const int inf = 400010;

	int ScanInt(void) {
		int c, r = 0, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0';
		while ( isdigit(d = getchar())) r = r * 10 + d - '0';
		return c=='-'?-r:r;
	}

	struct Interval {
		int l, r, index;
	}a[MAXN], c[MAXN]; int n, Limit, fim[MAXN], N;

	inline bool cmp(const Interval& a, const Interval& b) {
		if (a.r == b.r) return a.l > b.l;
		return a.r < b.r;
	}

	std::set<int> Vol; std::map<int, int> M;
	int Ans;

	void Input(void) {
		n = ScanInt();
		rep(i,1,n) Vol.insert(a[i].l = ScanInt()), Vol.insert(a[i].r = ScanInt()), a[i].index = i;
		for (std::set<int>::iterator it(Vol.begin()); it != Vol.end(); it++)
			M[*it] = ++Limit;
		rep(i,1,n) a[i].l = M[a[i].l], a[i].r = M[a[i].r];
		std::sort(a + 1, a + n + 1, cmp);
		int tmp = 0;
		rep(i,1,n) {
			fim[a[i].index] = i;
			if (a[i].l > tmp) {
				tmp = a[i].l;
				c[++N] = a[i];
			}
		}
	}

	int f[20][MAXN], pre[MAXN << 1], pow;
	inline void Prepare(void) {
		f[0][0] = 1, f[0][N + 1] = N + 1;
		c[N + 1].l = c[N + 1].r = Limit + 1;
		rep(i,1,N) {
			register int tmp = f[0][i - 1];
			while (tmp <= N && c[tmp].l <= c[i].r) tmp++;
			f[0][i] = tmp;
		}
		for (int k = 1; (1 << k) <= N; pow = k, k++) rep(i,0,N+1) f[k][i] = f[k - 1][f[k - 1][i]];
		pre[0] = 1;
		rep(i,1,Limit) {
			register int tmp = pre[i - 1];
			while (tmp <= n + 1 && c[tmp].l <= i) tmp++;
			pre[i] = tmp;
		}
	}

	int next[MAXN << 1];
	std::set<int> T;
	std::vector<int> ret;

	inline int Cal(int l, int r) {
		l = pre[l];
		int ret = (c[l].r < r);
		for (int k = pow; k >= 0; k--) {
			if (c[f[k][l]].r < r) {
				ret += (1 << k);
				l = f[k][l];
			}
		}
		return ret;
	}

	inline void Work(void) {
		next[0] = Limit + 1;
		T.insert(0); T.insert(Limit + 1);
		rep(o,1,n) {
			register int i = fim[o];
			std::set<int>::iterator it = T.lower_bound(a[i].l);
			it--;
			register int L = *it, R = next[L];
			if (a[i].l <= L || a[i].r >= R) continue;
			register int d = Cal(L, R), d1 = Cal(L, a[i].l), d2 = Cal(a[i].r, R);
			if (d == d1 + d2 + 1) {
				ret.push_back(o);
				next[L] = a[i].l;
				next[a[i].r] = R;
				T.insert(a[i].r);
			}
		}
	}

	void solve(void) {
		Input();
		int maxR = 0;
		rep(i,1,N) if (c[i].l > maxR) maxR = c[i].r, Ans++;
		Prepare();
		Work();
		printf("%d\n",Ans);
		assert(Ans == (int)ret.size());
		for (int i = 0; i < (int)ret.size() - 1; i++) printf("%d ",ret[i]); if (Ans) printf("%d\n",ret[ret.size() - 1]);
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
