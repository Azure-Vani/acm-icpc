//#define Debug
#include <vector>
#include <set>
#include <cstdio>
#include <algorithm>
#include <map>
#include <cctype>
#include <cstring>
namespace Solve {
	typedef unsigned long long Int64;
	typedef std::map<Int64, int> II;
	const int MAXN = 1005;
	const int MAXM = 100010;
	const int Base = 31;
	const int MAXL = 103;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	inline int ScanChr(void) {
		int c;
		while (c = getchar(), !islower(c)) {}
		return c - 'a';
	}

	int n, l, m, cnt = 0;
	int a[MAXN][MAXL];
	II T;
	
	struct Query {
		int l1, p1, l2, p2;
	}List[MAXM];
	Int64 hash[MAXN], pow[MAXL];

	inline void Input(void) {
		n = ScanInt(), l = ScanInt(), m = ScanInt();
		int tmp[MAXN][MAXL] = {0};
		scanf("\n");pow[0] = 1;
		for (int i = 1; i <= l; i++) pow[i] = pow[i - 1] * Base;
		for (int i = 1; i <= n; i++) {
			Int64 &h = hash[i];
			for (int j = 1; j <= l; j++) {
				a[i][j] = tmp[i][j] = ScanChr();
				h = h * Base + a[i][j];
			}
			if (T[h] == 0) T[h] = ++cnt;
		}
		Int64 H[MAXN]; memcpy(H, hash, sizeof hash);
		for (int i = 1; i <= m; i++) {
			int l1 = ScanInt(), p1 = ScanInt(), l2 = ScanInt(), p2 = ScanInt();
			Int64 delta1 = (Int64) (tmp[l1][p1] - tmp[l2][p2]) * pow[l - p2], 
			      delta2 = (Int64) (tmp[l2][p2] - tmp[l1][p1]) * pow[l - p1];
			std::swap(tmp[l1][p1], tmp[l2][p2]);
			H[l1] += delta2, H[l2] += delta1;
			if (T[H[l1]] == 0) T[H[l1]] = ++cnt;
			if (T[H[l2]] == 0) T[H[l2]] = ++cnt;
			List[i].l1 = l1, List[i].l2 = l2, List[i].p1 = p1, List[i].p2 = p2;
		}
	}

	int Ans[MAXN];
	
	struct pair {
		int index, F;
		pair(int i, int f):index(i), F(f){}
		inline friend bool operator <(const pair& a, const pair& b) {
			if (a.F != b.F)
			return a.F < b.F; else return a.index < b.index;
		}
	};
	typedef std::set<pair> SII;
	typedef std::vector<pair> VII;
	SII L[(MAXM << 1) + MAXN];

	inline void Updata(int t) {
		int N = L[t].size();
		VII tmp;
		for (SII::iterator it = L[t].begin(); it != L[t].end() && it->F < N;) {
			tmp.push_back(*it);
			L[t].erase(it++);
		}
		for (VII::iterator it = tmp.begin(); it != tmp.end(); it++) {
			Ans[it->index] = it->F = N;
			L[t].insert(*it);
		}
	}

	inline void Work(void) {
		for (int i = 1; i <= n; i++) {
			int t = T[hash[i]];
			L[t].insert(pair(i, 0));
		}
		for (int i = 1; i <= n; i++) Updata(T[hash[i]]);
		for (int i = 1; i <= m; i++) {
			int l1 = List[i].l1, l2 = List[i].l2, p1 = List[i].p1, p2 = List[i].p2;
			Int64 delta1 = (Int64) (a[l1][p1] - a[l2][p2]) * pow[l - p2], 
			      delta2 = (Int64) (a[l2][p2] - a[l1][p1]) * pow[l - p1];
			std::swap(a[l1][p1], a[l2][p2]);
			int t1 = T[hash[l1]], t2 = T[hash[l2]];
			L[t1].erase(pair(l1, Ans[l1])); L[t2].erase(pair(l2, Ans[l2]));
			hash[l1] += delta2, hash[l2] += delta1;
			int t3 = T[hash[l1]], t4 = T[hash[l2]];
			L[t3].insert(pair(l1, Ans[l1])); L[t4].insert(pair(l2, Ans[l2]));
			Updata(t3); Updata(t4);
		}
		for (int i = 1; i <= n; i++) {
			int t = T[hash[i]];
			Updata(t);
		}
		for (int i = 1; i <= n; i++) printf("%d\n", Ans[i]);
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
