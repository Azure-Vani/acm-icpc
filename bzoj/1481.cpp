#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#define Fail "Victory of Darkness" 
namespace Solve {
	const int MAXN = 1009;
	const int inf = 1050000000;
	typedef long long Int64;
	
	struct pair{Int64 x;int y, index, flag;}; inline pair make_pair(Int64 x, int y, int i, int f) {pair a; a.x = x, a.y = y, a.index = i, a.flag = f; return a;}
	template <class T>
	class Queue {public:
		T a[MAXN];int head, tail;
		Queue():head(1), tail(0){memset(a, 0, sizeof a);}
		inline void operator =(const Queue& b) { memcpy(a + b.head, b.a + b.head, sizeof(T) * (b.tail - b.head + 1)); head = b.head, tail = b.tail; }
		inline void push(T u) {a[++tail] = u;}
		inline void pop_back(void) {tail--;}
		inline void pop_front(void) {head++;}
		inline int size(void) {return tail - head + 1;}
		inline void clear(void) {memset(a, 0, sizeof a); head = 1, tail = 0;}
		inline T& operator [](const int &k) {if (k > 0) return a[head + k - 1]; else return a[tail + k];}
	};

	#define T_T(x) ((x) = (x) == '.' ? 'O' : '.')
	char ch[MAXN][MAXN]; int n, m, f[MAXN][2][MAXN];
	void Input(void) {
		scanf("%d%d\n", &n, &m); if (n <= 2) {puts(Fail); exit(0);}
		for (int i = n; i >= 1; i--) ch[i][0] = 'O', gets(ch[i] + 1);
		for (int i = 1; i <= m; i++) T_T(ch[1][i]), T_T(ch[n][i]);
		for (int i = 1; i <= m; i++) if (ch[1][i] == '.') f[1][0][i] = 0, f[1][1][i] = inf; else f[1][1][i] = inf, f[1][0][i] = inf;
	}

	#define CL(a) (memset(a, 0, sizeof a))
	int M[MAXN], S[MAXN];
	inline void Prepare(char a[]) {
		CL(M); CL(S);
		int s1 = 0, s2 = 0, b1 = 0, b2 = 0;
		for (int i = 1; i <= m; i++) {
			s1 += a[i] == 'S'; s2 += (a[i] == 'S') * i; b1 += a[i] == 'B'; b2 += (a[i] == 'B') * i;
			M[i] = s2 - b2; S[i] = s1 - b1;
		}
	}

	inline void Gao(char a[], int ret[2][MAXN], int f[2][MAXN]) {
		Prepare(a);
		Queue <pair> T[2];
		Int64 X, Y;
		for (int i = 1; i <= m; i++) {
			if (a[i] == 'O') {T[0].clear(), T[1].clear(), ret[0][i] = ret[1][i] = inf; continue;}
			for (int k = 0; k < 2; k++) {
				X = (Int64)(2 * f[k][i] + i * i - i - 2 * M[i] + 2 * i * S[i]);
				Y = i * 2;
				while (T[k].size() >= 2 && (Int64) ((X - T[k][0].x) * (T[k][0].y - T[k][-1].y)) <= (Int64) ((Y - T[k][0].y) * (T[k][0].x - T[k][-1].x)))
					T[k].pop_back();
				T[k].push(make_pair(X, Y, i, k));
				while (T[k].size() >= 2 && T[k][2].x - T[k][1].x <= (Int64) ((i + S[i]) * (T[k][2].y - T[k][1].y)))
					T[k].pop_front();
			}
			if (a[i] == 'F') std::swap(T[0], T[1]);
			for (int k = 0; k < 2; k++) {
				int t = T[k][1].index, flag = T[k][1].flag;
				ret[k][i] = (Int64)(f[flag][t] + (Int64)((i - t) * (i - t + 1) / 2) + (M[i] - M[t]) - t * (S[i] - S[t]));
			}
		}
	}

	int seg1[2][MAXN] = {0}, seg2[2][MAXN] = {0}, C[MAXN] = {0};
	#define Re(a) (std::reverse((a) + 1, (a) + m + 1))
	void solve(void) {
		Input();
		for (int i = 2; i <= n; i++, CL(seg1), CL(seg2)) {
			for (int j = 1; j <= m; j++) C[j] = ch[i][j] == 'O' ? inf : ch[i][j] == 'S' ? 2 : ch[i][j] == 'B' ? 0 : 1;
			Re(ch[i - 1]); Re(f[i - 1][0]); Re(f[i - 1][1]);
			Gao(ch[i - 1], seg2, f[i - 1]);
			Re(ch[i - 1]); Re(f[i - 1][0]); Re(f[i - 1][1]);
			Gao(ch[i - 1], seg1, f[i - 1]);
			Re(seg2[1]); Re(seg2[0]);
			for (int j = 1; j <= m; j++) for (int k = 0; k <= 1; k++)
				f[i][k][j] = std::min(seg1[k][j], seg2[k][j]) + C[j], f[i][k][j] = std::min(inf, f[i][k][j]);
		}
		int Ans = inf;
		for (int i = 1; i <= m; i++) Ans = std::min(Ans, f[n][1][i]);
		if (Ans >= inf) puts(Fail); else printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
