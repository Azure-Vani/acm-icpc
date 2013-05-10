//#define Debug
#include <cstdio>
#include <cstring>
#include <algorithm>
namespace Solve {
	#define LL "%lld"
	const int MAXN = 20;
	typedef long long Int64;

	int nRow, nCol, cRow, cCol;
	Int64 a[MAXN][MAXN];
	void Input(void) {
		scanf("%d %d %d %d", &nRow, &nCol, &cRow, &cCol);
		for (int i = 1; i <= nRow; i++) for (int j = 1; j <= nCol; j++) {
			scanf(LL , &a[i][j]);
			a[i][j] += a[i - 1][j] + a[i][j - 1] - a[i - 1][j - 1];
		}
	}

	#define Sum(x1, y1, x2, y2) (a[x2][y2] - a[(x1) - 1][y2] - a[x2][(y1) - 1] + a[(x1) - 1][(y1) - 1])
	Int64 Now;
	int Cut[MAXN];bool Status;
	
	void Doit(void) {
		int N = cCol + 1, last = 1, Tim = 0; Cut[N] = nCol;
		for (int level = 1; level <= nRow; level++) {
			for (int i = 1; i <= N; i++)
				if (Sum(level, Cut[i - 1] + 1, level, Cut[i]) > Now)
					return;
		}
		for (int level = 1; level < nRow; level++) {
			bool cut = false;
			for (int i = 1; i <= N; i++) {
				if (Sum(last, Cut[i - 1] + 1, level + 1, Cut[i]) > Now) {
					cut = true;
					break;
				}
			}
			if (cut) {Tim++; last = level + 1;}
		}
		if (Tim <= cRow) Status = true;
		return;
	}

	void Dfs(int N, int Col) {
		if (Status) return;
		if (N == cCol + 1) {
			Doit();
			return;
		}
		for (int i = Col; i < nCol && nCol - Col - 1 >= cCol - N; i++) {
			Cut[N] = i;
			Dfs(N + 1, i + 1);
		}
	}
	inline bool Check(Int64 _) {
		Now = _; Status = false; memset(Cut, 0, sizeof Cut);
		Dfs(1, 1);
		return Status;
	}
	void Work(void) {
		Int64 l = 0, r = a[nRow][nCol];
		while (l <= r) {
			Int64 mid = (l + r) >> 1;
			if (Check(mid))
				r = mid - 1;
			else 
				l = mid + 1;
		}
		printf(LL "\n", l);
	}
	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		//freopen("1.out", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
