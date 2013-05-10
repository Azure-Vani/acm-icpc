//#define Debug
#include <cstdio>
#include <cstring>
#include <cctype>
#include <algorithm>
namespace Solve {
	const int MAXN = 100050;
	const int INF = 0x6eeeeeee;
	
	#define Lowbit(x) ((x)&(-(x)))
	class TreeArray {
		public:
		int a[MAXN], n;
		
		inline void Add(int k, int u) {
			for (int i = k; i <= n; i += Lowbit(i)) 
				a[i] += u;
		}
		
		inline int Sum(int k) {
			int ret = 0;
			for (int i = k; i > 0; i -= Lowbit(i)) ret += a[i];
			return ret;
		}
		
		inline int Cal(int l, int r) {
			return Sum(r) - Sum(l - 1);
		}
	};
	
	inline int ScanInt(void) {
		int r = 0; int c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	
	struct pair {
		int x, y, P, L;
	}S[MAXN];
	inline bool cmp(const pair& a, const pair& b) {
		return a.x == b.x ? a.y < b.y : a.x < b.x;
	}
	inline bool cmpII(const pair& a, const pair& b) {
		return a.y == b.y ? a.x < b.x : a.y < b.y;
	}
	
	int nRow, nLine, nTree, K;
	int Set[MAXN];
	
	void Input(void) {
		nRow = ScanInt(), nLine = ScanInt(), nTree = ScanInt();
		for (int i = 1; i <= nTree; i++)
			S[i].x = ScanInt(), Set[i] = S[i].y = ScanInt();
		K = ScanInt();
	}
	
	inline int Where(int u) {
		int l = 1, r = nTree;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (u < Set[mid])
				r = mid - 1;
			else
				l = mid + 1;
		}
		return r;
	}
	
	int Sup[MAXN], C[11][MAXN], Sum[MAXN];
	int sumRow[MAXN], sumLeft[MAXN];
	TreeArray T;
	
	void Prepare(void) {
		C[0][0] = 1;
		for (int i = 1; i <= nTree; i++) {
			C[0][i] = 1;
			for (int j = 1; j <= K; j++)
				C[j][i] = C[j][i - 1] + C[j - 1][i - 1];
		}
		
		std::sort(Set + 1, Set + 1 + nTree);
		std::sort(S + 1, S + 1 + nTree, cmpII);
		S[0].x = S[0].y = -INF;
		S[nTree + 1].x = S[nTree + 1].y = INF;
		
		for (int i = 1; i <= nTree; i++) {
			int t = S[i].P = Where(S[i].y);
			sumRow[t]++;
			S[i].L = S[i].y == S[i - 1].y ? S[i - 1].L + 1 : 1;
		}
			
		std::sort(S + 1, S + 1 + nTree, cmp);
		int last = 0;
		for (int i = 1; i <= nTree; i++) {
			if (S[i].x == S[i - 1].x) Sup[i] = Sup[i - 1] + 1;
			else {Sup[i] = 1; if (last) std::reverse(Sup + last, Sup + i); last = i;}
		}
		std::reverse(Sup + last, Sup + nTree + 1);
		T.n = nTree;
	}
	
	void Make(int& ret, int l, int r, int N, int total) {
		if (l > r) return;
		int Up , Down, Row;
		Up = C[K][Sup[N + 1]];
		Down = C[K][total];
		Row = Solve::T.Cal(l, r);
		ret += (Up * Down * Row);
	}
	
	int delta[MAXN] = {0};
	int MainWork(void) {
		int ret = 0, nowtotal = 0;
		for (int i = 1; i <= nTree; i++) {
			int  t = S[i].P;
			if (S[i].x == S[i + 1].x)
				Make(ret, t + 1, S[i + 1].P - 1, i, ++nowtotal);
			else nowtotal = 0;
			int lsum = C[K][S[i].L], rsum = C[K][sumRow[t] - S[i].L];
			T.Add(t, lsum * rsum - delta[t]);
			delta[t] = lsum * rsum;
		}
		return ret;
	}
	
	void solve(void) {
		Input();
		Prepare();
		int A = MainWork();
		if (A < 0) A += 0x7fffffffll + 1ll;
		printf("%d\n", A);
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
