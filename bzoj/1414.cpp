#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#define Reverse(i, n) ((n) - (i) - 1)

namespace Solve {
	const int MAXN = 1000 + 10;

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n, m;
	int map[MAXN << 1][MAXN << 1];
	
	void Input(void) {
		memset(map, -1, sizeof map);

		n = ScanInt(), m = ScanInt();
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				map[i << 1][j << 1] = ScanInt();
		n = (n << 1) - 1;
		m = (m << 1) - 1;
	}
	
	void Extend(int M[], int ret[], int n) {
		int MaxR = -1, where;
		for (int i = 0; i < n; i++) {
			int it = 0;
			if (i <= MaxR) {
				it = ret[(where << 1) - i];
				if (i + it >= MaxR) {
					it = MaxR - i;
				}
			}
			while (i - it >= 0 && i + it < n && M[i - it] == M[i + it])
				it++;
			it--;
			ret[i] = it;
			if (i + it > MaxR) {
				MaxR = i + it;
				where = i;
			}
		}
	}

	int MaxExtendRow[MAXN << 1][MAXN << 1], MaxExtendLine[MAXN << 1][MAXN << 1];

	void Prepare(void) {
		int ret[MAXN << 1], reg[MAXN << 1];

		//Row
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++) 
				reg[j] = map[i][j];
			Extend(reg, ret, m);
			for (int j = 0; j < m; j++)
				MaxExtendRow[i][j] = ret[j];
		}
		
		//Line
		for (int j = 0; j < m; j++) {
			for (int i = 0; i < n; i++) 
				reg[i] = map[i][j];
			Extend(reg, ret, n);
			for (int i = 0; i < n; i++)
				MaxExtendLine[i][j] = ret[i];
		}
	}
	
	void Make(int M[], int ret[], int n) {
		long d[MAXN << 1], tail, head;

		tail = 0, head = 1;
		for (int i = 0; i < n; i++) {
			while (tail >= head && M[ d[tail] ] >= M[i])
				tail--;
			d[++tail] = i;

			int it = i ? i - 1 - ret[i - 1] : 0;
			while (true) {
				int L = i - it;
				if (L <= M[ d[head] ])
					break;
				it++;
				if (d[head] < it)
					head++;
			}
			ret[i] = i - it;
		}
	}

	int MaxSquare[MAXN << 1][MAXN << 1];
	const int INF = 0x6eeeeeee;
	typedef long long Int64;

	Int64 MainWork(void) {
		int reg[MAXN << 1], ret[MAXN << 1];
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				MaxSquare[i][j] = INF;

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < m; j++)
				reg[j] = MaxExtendLine[i][j];
			Make(reg, ret, m);
			for (int j = 0; j < m; j++)
				MaxSquare[i][j] = std::min(MaxSquare[i][j], ret[j]);

			std::reverse(reg, reg + m);
			Make(reg, ret, m);
			for (int j = 0; j < m; j++)
				MaxSquare[i][j] = std::min(MaxSquare[i][j], ret[Reverse(j, m)]);
		}

		for (int j = 0; j < m; j++) {
			for (int i = 0; i < n; i++)
				reg[i] = MaxExtendRow[i][j];
			Make(reg, ret, n);
			for (int i = 0; i < n; i++)
				MaxSquare[i][j] = std::min(MaxSquare[i][j], reg[i]);

			std::reverse(reg, reg + n);
			Make(reg, ret, n);
			for (int i = 0; i < n; i++)
				MaxSquare[i][j] = std::min(MaxSquare[i][j], ret[Reverse(i, n)]);
		}

		Int64 A = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++) {
				if (i & 1 && j & 1)
					A += (MaxSquare[i][j] + 1) >> 1;
				if (!(i & 1) && !(j & 1))
					A += (MaxSquare[i][j]) / 2 + 1;
			}

		return A;
	}

	void solve(void) {
		Input();
		Prepare();
		printf("%lld\n", MainWork());
	}
}

int main(int argc, char** argv) {
	#ifdef Debug
		freopen("in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
