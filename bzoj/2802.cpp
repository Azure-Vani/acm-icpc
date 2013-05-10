//#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

namespace Solve {
	typedef long long Int64;
	const int MAXN = 250010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}
	
	int n;
	Int64 sum[MAXN];

	struct Seg {
		int l, r; Seg *ch[2]; Int64 d, v;
		inline void Update(void) {
			v = min(ch[0]->v, ch[1]->v);
		}
		inline void Build(int L, int R) {
			int mid = (L + R) >> 1;
			l = L, r = R, d = 0;
			if (L == r) {
				v = sum[L];
				return;
			}
			ch[0] = new Seg(); ch[0]->Build(L, mid);
			ch[1] = new Seg(); ch[1]->Build(mid + 1, R);
			v = min(ch[0]->v, ch[1]->v);
			return;
		}
		inline void Down(void) {
			if (d) {
				if (ch[1]) ch[1]->v -= d, ch[1]->d += d;
				if (ch[0]) ch[0]->v -= d, ch[0]->d += d;
				d = 0;
			}
		}
		inline void Modify(int L, int R, Int64 t) {
			if (L > R) return;
			if (L <= l && r <= R) {
				d += t;
				v -= t;
				return;
			}
			this->Down();
			int mid = (l + r) >> 1;
			ch[0]->Modify(L, min(mid, R), t);
			ch[1]->Modify(max(mid + 1, L), R, t);
			Update();
		}
		inline Int64 Cal(int L, int R) {
			if (L > R) return 100000000000000000ll;
			this->Down();
			if (L <= l && r <= R) return v;
			int mid = (l + r) >> 1;
			return min(ch[0]->Cal(L, min(mid, R)),
			ch[1]->Cal(max(mid + 1, L), R));
		}
	}*root;

	pair<int, pair<int, int> > a[MAXN];

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) a[i].second.first = ScanInt(), a[i].second.second = i;
		for (int i = 1; i <= n; i++) a[i].first = ScanInt();
	}

	vector<int> Ans;
	inline void Work(void) {
		for (int i = 1; i <= n; i++) sum[i] = sum[i - 1] + a[i].second.first;
		root = new Seg(); root->Build(1, n);
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) {
//			fprintf(stderr, "%d\n", i);
			int pos = a[i].second.second;
			Int64 tmp = root->Cal(pos, n);
			if (tmp >= a[i].first) {
				root->Modify(pos, n, a[i].first);
				Ans.pb(pos);
			}
		}
		sort(Ans.begin(), Ans.end());
		printf("%d\n", Ans.size());
		foreach(it, Ans) printf("%d ", *it); puts("");
	}

	inline void solve(void) {
		Input();
		Work();
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
//		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}