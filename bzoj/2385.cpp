//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <map>
#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
namespace Solve {
	typedef long long Int64;
	const int MAXN = 500020;
	
	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	struct room {
		int p, c;
		room(int p, int c):p(p),c(c){}
		inline friend bool operator <(const room& a, const room& b) {
			if (a.p != b.p)
			return a.p < b.p; else return a.c < b.c;
		}
	};
	struct offer {
		int u, v;
	}c[MAXN];
	int n, m, k;

	std::map<room, int> T;

	inline void Input(void) {
		n = ScanInt(), m = ScanInt(), k = ScanInt();
		for (int i = 1; i <= n; i++) {int c = ScanInt(), p = ScanInt(); T[room(p, c)]++; }
		for (int i = 1; i <= m; i++) c[i].v = ScanInt(), c[i].u = ScanInt();
	}
	
	inline bool cmop(const offer& a, const offer& b) {
		if (a.v == b.v) return a.u < b.u; else return a.v > b.v;
	}
	
	int L[MAXN], cnt;

	inline void Prepare(void) {
		std::sort(c + 1, c + m + 1, cmop);
		for (int i = 1; i <= m; i++) {
			std::map<room, int>::iterator it = T.lower_bound(room(c[i].u, -1));
			if (it != T.end()) {
				L[++cnt] = c[i].v - it->first.c;
				if (it->second == 1) T.erase(it); else it->second--;
			}
		}
		std::sort(L + 1, L + cnt + 1);
	}

	void solve(void) {
		Input();
		Prepare();
		Int64 Ans = 0; k = std::min(cnt, k);
		for (int i = cnt; k-- && L[i] > 0; i--) Ans += L[i];
		printf(LL "\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
	//	freopen("1.out", "w", stdout);
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
