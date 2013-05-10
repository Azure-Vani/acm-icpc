//#define Debug
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <set>
namespace Solve {
	typedef int Int64;
	const int MAXN = 1006;

	inline int ScanInt(void) {
		int c, r = 0;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	struct Node {
		Int64 a[2];
		inline friend bool operator ==(const Node& a, const Node& b) {
			return a.a[1] == b.a[1] && a.a[0] == b.a[0];
		}
		inline friend Node operator *(const Node& a, const Node& b) {
			Node c;
			c.a[0] = a.a[0] * b.a[0];
			c.a[1] = a.a[1] * b.a[1];
			return c;
		}
		inline void operator =(const Node& c) {
			a[0] = c.a[0], a[1] = c.a[1];
		}
		inline Node operator *(int c) {
			Node r;
			r.a[0] = a[0] * c, r.a[1] = a[1] * c;
			return r;
		}
		inline void operator =(const int c) {
			a[0] = a[1] = c;
		}
		inline friend Node operator -(const Node& a, const Node& b) {
			Node r;
			r.a[0] = a.a[0] - b.a[0];
			r.a[1] = a.a[1] - b.a[1];
			return r;
		}
		inline friend Node operator +(const Node& a, const Node& b) {
			Node r;
			r.a[0] = a.a[0] + b.a[0];
			r.a[1] = a.a[1] + b.a[1];
			return r;
		}
	}base;

	int n, m, n1, m1;
	int a[MAXN][MAXN];
	Node hash[MAXN][MAXN];

	char ch[MAXN][MAXN];
	void Input(void) {
		scanf("%d%d%d%d\n", &n, &m, &n1, &m1);
		for (int i = 1; i <= n; i++) {
			scanf("%s\n", ch[i] + 1);
			for (int j = 1; j <= m; j++)
				a[i][j] = ch[i][j] - '0';
		}
	}

	Node tmp[MAXN][MAXN], sum[MAXN][MAXN];

	inline void MakeHash(void) {
		base.a[0] = 17, base.a[1] = 31;
		Node s; s = 1;
		for (int j = 1; j <= m; j++) s = s * base;
		for (int i = 1; i <= n; i++) {
			for (int j = 1; j <= m; j++) {
				if (i == 1 && j == 1) hash[i][j] = 1;
				else if (j == 1) hash[i][j] = hash[i - 1][j] * s;
				else hash[i][j] = hash[i][j - 1] * base;
			}
		}

		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= m; j++) {
				sum[i][j] = hash[i][j] * a[i][j];
				sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + sum[i][j];
				if (i >= n1 && j >= m1)
					tmp[i][j] = sum[i][j] - sum[i - n1][j] - sum[i][j - m1] + sum[i - n1][j - m1];
			}
	}

	Node S;
	char cs[MAXN][MAXN];

	void Work(void) {
		int Q;scanf("%d\n", &Q);
		for (int k = 1; k <= Q; k++) {
			S = 0;
			for (int i = 1; i <= n1; i++) {
				scanf("%s\n", cs[i] + 1);
				for (int j = 1; j <= m1; j++)
					S = S + hash[i][j] * (cs[i][j] - '0');
			}
			bool flag = false;
			for (int i = n1; i <= n && !flag; i++) for (int j = m1; j <= m; j++)
				if (tmp[i][j] == S * hash[i - n1 + 1][j - m1 + 1]) {
					flag = true;
					for (int i1 = 1; i1 <= n1 && flag; i1++)
						for (int j1 = 1; j1 <= m1; j1++)
							if (cs[i1][j1] != ch[i - n1 + i1][j - m1 + j1]) {
								flag = false;
								break;
							}
					if (flag) break;
				}
			puts(flag?"1":"0");
		}
	}

	void solve(void) {
		Input();
		MakeHash();
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
