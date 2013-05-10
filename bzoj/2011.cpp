//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	const int MAXN = 100020;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	inline int ScanChr(void) {
		int c;
		while (c = getchar(), c != '+' && c != '-') {}
		return c == '+' ? 1 : -1;
	}

	struct Query {
		int index, d, t;
		inline friend bool operator <(const Query& a, const Query& b) {
			return a.t < b.t;
		}
	}a[MAXN];

	int n, vmax, v2;
	inline void Input(void) {
		n = ScanInt(), vmax = ScanInt(), v2 = ScanInt();ScanChr();
		int last = ScanInt();n--;
		for (int i = 1; i <= n; i++) {
			int d = ScanChr(), t = ScanInt();
			a[i].index = i, a[i].t = t - last, a[i].d = d;
			last = t;
		}
		std::sort(a + 1, a + n + 1);
	}

	struct Node {
		Node* ch[2]; int l, r, sum, bmax, bmin, cmax, cmin;
		inline int Get(int t) {
			if (t >= bmax) return cmax;
			else if (t <= bmin) return cmin;
			else return t + sum;
		}
		inline void Updata(void) {
			sum = ch[0]->sum + ch[1]->sum;
			if (ch[1]->bmin >= ch[0]->cmax) bmin = vmax;
			else if (ch[1]->bmin <= ch[0]->cmin) bmin = ch[0]->bmin;
			else bmin = ch[1]->bmin - ch[0]->sum;
			if (ch[1]->bmax <= ch[0]->cmin) bmax = 0;
			else if (ch[1]->bmax >= ch[0]->cmax) bmax = ch[0]->bmax;
			else bmax = ch[1]->bmax - ch[0]->sum;
			cmax = ch[1]->Get(ch[0]->cmax);
			cmin = ch[1]->Get(ch[0]->cmin);
		}
		inline void Build(int L, int R) {
			l = L, r = R;
			sum = 0; bmax = vmax, bmin = 0, cmax = vmax, cmin = 0;
			if (l == r) return;
			int mid = (l + r) >> 1;
			(ch[0] = new Node)->Build(l, mid);
			(ch[1] = new Node)->Build(mid + 1, r);
		}
		inline void Insert(int h, int d) {
			if (l == r) {
				sum = d; if (d == 1) {
					bmax = vmax - 1;cmin = 1;
				}
				if (d == -1) {
					bmin = 1; cmax = vmax - 1;
				}
				return;
			}
			int mid = (l + r) >> 1;
			if (h <= mid) ch[0]->Insert(h, d); else ch[1]->Insert(h, d);
			Updata();
		}
	}*root;

	void Work(void) {
		(root = new Node)->Build(1, n);
		int T = 0, k = v2;
		for (int i = 1; i <= n;) {
			int t = i;
			for (;t <= n && a[i].t == a[t].t; t++)
				root->Insert(a[t].index, a[t].d);
			if (root->cmin <= v2 && v2 <= root->cmax) {
				T = a[t].t - 1;
				if (v2 == root->cmin) k = root->bmin;
				else if (v2 == root->cmax) k = vmax; else k = v2 - root->sum;
			}
			i = t;
		}
		if (T < 0) printf("infinity\n"); else printf("%d %d\n", T, k);
	}
	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	//	freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
