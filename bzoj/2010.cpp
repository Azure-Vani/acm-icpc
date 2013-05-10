//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
namespace Solve {
	typedef long long Int64;
	const int MAXN = 200020;
	const Int64 inf = 1000000000000000001ll;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct pair {
		Int64 value, num;
		inline friend bool operator <(const pair& a, const pair& b) {
			return a.value > b.value;
		}
	}R[MAXN], C[MAXN];
	int n, m; Int64 Sum = 0;

	inline void Input(void) {
		n = ScanInt();
		for (int i = 1; i <= n; i++) 
			R[i].value = ScanInt(), R[i].num = ScanInt();
		m = ScanInt();
		for (int j = 1; j <= m; j++)
			C[j].value = ScanInt(), Sum += (C[j].num = ScanInt());
		std::sort(R + 1, R + n + 1);
		std::sort(C + 1, C + m + 1);
	}
	
	struct Point {
		Int64 x, y;
	}f[MAXN], g[MAXN];

	inline void MakeGraph(void) {
		for (int i = 1; i <= n; i++) {
			f[i].x = f[i - 1].x + R[i].num;
			f[i].y = f[i - 1].y + (Int64) R[i].num * R[i].value;
		}
		Int64 tmp = 0, cnt = 0; int l = 0;
		for (int i = m; i >= 1; i--) {
			if (C[i].value != C[i + 1].value) {
				g[++l].x = C[i].value;
				g[l].y = tmp + (Sum - cnt) * C[i].value;
			}
			cnt += C[i].num, tmp += C[i].num * C[i].value;
		}m = l;
	//	std::reverse(g + 1, g + m + 1);
		f[n + 1].x = inf, f[n + 1].y = f[n].y;
		g[m + 1].x = inf, g[m + 1].y = g[m].y;
	}

	int p1 = 0, p2 = 0;
	inline bool Gao(void) {
		while (true) {
			if (p1 + 1 > n && p2 + 1 > m) return true;
			if (f[p1 + 1].x == g[p2 + 1].x) {p1++, p2++;
				if (f[p1].y > g[p2].y) 
					return false;
				continue;
			}else
			if (f[p1 + 1].x > g[p2 + 1].x) {p2++;
			/*	if (f[p1 + 1].x >= g[p2].x) {*/
					Int64 Y = (f[p1 + 1].y - f[p1].y) / (f[p1 + 1].x - f[p1].x) * (g[p2].x - f[p1].x) + f[p1].y;
					if (Y > g[p2].y) return false;
			/*	}
				p1++;*/
			}else {p1++;
			/*	if (g[p2 + 1].x >= f[p1].x) {*/
					Int64 Y = (g[p2 + 1].y - g[p2].y) / (g[p2 + 1].x - g[p2].x) * (f[p1].x - g[p2].x) + g[p2].y;
					if (Y < f[p1].y) return false;
			/*	}
				p2++;*/
			}
		}
	}

	void solve(void) {
		Input();
		MakeGraph();
		printf("%d\n", (int) Gao());
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
