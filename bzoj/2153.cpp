//#define Debug
#define STDIO
#define INPUT "2153.in"
#define OUTPUT "2153.out"

#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 40010;

	int n, m;
	Int64 R[MAXN], s[MAXN], T[MAXN], f[MAXN];
	std::pair<Int64, Int64> Q[MAXN];

	inline void Input(FILE *fin) {
		fscanf(fin, "%d%d", &n, &m);
		Int64 tmp; int cnt = 0;
		for (int i = 1; i <= n; i++) fscanf(fin, "%lld%lld", &Q[i].first, &Q[i].second);
		std::sort(Q + 1, Q + n + 1); Q[n + 1].first = -1;
		for (int i = 1; i <= n; i++) if (Q[i].first != Q[i + 1].first) {
			cnt++;
			tmp = Q[i].second, R[cnt] = Q[i].first;
			s[cnt] = tmp + s[cnt - 1];
			T[cnt] = (Int64) T[cnt - 1] + tmp * R[cnt];
		} else Q[i + 1].second += Q[i].second;
		n = cnt;
	}

	struct Node {
		Int64 x, y; int pos;
		Node(Int64 x, Int64 y, int pos):x(x),y(y),pos(pos){}
		Node(){}
	}d[MAXN];

	inline Int64 Cal(int l, int r) {
		return (T[r] - T[l]) - R[l] * (s[r] - s[l]);
	}

	inline Int64 Check_DP(void) {
		Int64 Ans = Cal(0, n);
		for (int i = 1; i <= n; i++) {
			f[i] = (~0ULL) >> 1;
			for (int j = 0; j < i; j++)
				f[i] = std::min(f[i], f[j] + Cal(j, i - 1) + m);
			Ans = std::min(Ans, f[i] + Cal(i, n));
		}
		return Ans;
	}

	inline Int64 Work(void) {
		int head = 1, tail = 1;
		for (int i = 1; i <= n; i++) {
			while (head < tail && d[head + 1].y - d[head].y < s[i - 1] * (d[head + 1].x - d[head].x))
				head++;
			f[i] = f[d[head].pos] + Cal(d[head].pos, i - 1) + m;
			Int64 X = R[i], Y = f[i] + R[i] * s[i] - T[i];
			while (head < tail && (d[tail].y - d[tail - 1].y) * (X - d[tail].x) > 
					(d[tail].x - d[tail - 1].x) * (Y - d[tail].y))
				tail--;
			d[++tail] = Node(X, Y, i);
		}
		Int64 Ans = Cal(0, n);
		for (int i = 1; i <= n; i++)
			Ans = std::min(Ans, f[i] + Cal(i, n));
		return Ans;
	}

	inline void solve(FILE *fin, FILE *fout) {
		Input(fin);
#ifdef Debug
		Int64 C_Ans = Check_DP();
		fprintf(fout, "%lld\n", C_Ans);
#else
		Int64 Ans = Work();
		fprintf(fout, "%lld\n", Ans);
#endif
	}
}
int main(int argc, char* argv[]) {
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
	     *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, fout);
	fclose(fin);
	fclose(fout);
	return 0;
#endif
}
