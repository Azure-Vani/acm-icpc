//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <map>
#include <set>

#define rep(i,l,r) for(int i = l; i <= r; i++)

namespace Solve {
	const int MAXN = 100010;
	
	std::map<int, int> M;
	std::set<int> S;

	int ScanInt(void) {
		int c, r = 0, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0';
		while ( isdigit(d = getchar())) r = r * 10 + d - '0';
		return c=='-'?-r:r;
	}

	struct Interval {
		int l, r;
	}a[MAXN];
	inline bool cmp(const Interval& a, const Interval& b) {
		return a.r < b.r;
	}

	int m, r, n;

	inline void Input(void) {
		S.clear(); M.clear();
		m = ScanInt(), r = ScanInt();
		rep(i,1,m) a[i].l = ScanInt(), a[i].r = ScanInt(), S.insert(a[i].l), S.insert(a[i].r);
		std::sort(a + 1, a + m + 1, cmp);
		n = 0;
		for (std::set<int>::iterator it(S.begin()); it != S.end(); it++)
			M[*it] = ++n;
	}
	
	struct SegMent {
		int l, r, max, d;
		SegMent *ch[2];
		SegMent(){ch[0] = ch[1] = NULL;}
		inline void Down(void) {
			if (ch[0]) {
				ch[0]->max += d; ch[1]->max += d;
				d = 0;
			}
		}
		inline void Build(int L, int R) {
			l = L, r = R, max = 0, d = 0;
			if (L == R) return;
			register int mid = (L + R) >> 1;
			if (!ch[0]) ch[0] = new SegMent;
			if (!ch[1]) ch[1] = new SegMent;
			ch[0]->Build(L, mid);
			ch[1]->Build(mid + 1, R);
		}
		inline void Cover(int L, int R) {
			if (R < L) return;
			if (L <= l && r <= R) {
				d++;
				max++;
				return;
			}
			//Down();
			register int mid = (l + r) >> 1;
			ch[0]->Cover(L, std::min(mid, R));
			ch[1]->Cover(std::max(mid + 1, L), R);
			//Down();
			max = std::max(ch[0]->max, ch[1]->max) + d;
		}
		inline int Cal(int L, int R) {
			if (L > R) return 0;
			if (L <= l && r <= R) return max;
			//Down();
			register int mid = (l + r) >> 1;
			return std::max(ch[0]->Cal(L, std::min(mid, R)), ch[1]->Cal(std::max(mid + 1, L), R)) + d;
		}
	}*root;

	inline void Work(void) {
		int Ans = 0;
		rep(i,1,m) {
			register int l = M[a[i].l], r = M[a[i].r];
			register int tmp = root->Cal(l, r);
			if (tmp < Solve::r) {
				Ans++;
				root->Cover(l, r);
			}
		}
		printf("%d\n",Ans);
	}

	void solve(void) {
		Input();
		root = new SegMent;
		root->Build(1, n);
		Work();
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	int tCase; scanf("%d", &tCase);
	while (tCase--)
	Solve::solve();
	return 0;
}
