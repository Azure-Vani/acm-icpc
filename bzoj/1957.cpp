#include <cstdio>
#include <algorithm>
namespace Solve {
	const int MAXN = 505;

	int X, Y, n, nRow, nCol;
	struct pair {int now, l, r;}Row[MAXN], Col[MAXN];

	void Input(void) {
		scanf("%d%d%d", &X, &Y, &n);
		for (int i = 1, x1, x2, y1, y2; i <= n; i++) {
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if (x1 == x2) {
				Col[nCol].now = x1;
				Col[nCol].l = std::min(y1, y2);
				Col[nCol++].r = std::max(y1, y2);
			}else {
				Row[nRow].now = y1;
				Row[nRow].l = std::min(x1, x2);
				Row[nRow++].r = std::max(x1, x2);
			}
		}
	}

	bool Check(int S) {
		int Left = -S, Right = S, Up = S, Down = -S;
		while (true) {
			bool extend = false;
			for (int i = 0; i < nRow; i++) {
				if (Row[i].now >= Down && Row[i].now <= Up) {
					int R = Right, L = Left;
					if (Row[i].l <= Right) Right = std::max(Right, Row[i].r);
					if (Row[i].r >= Left ) Left  = std::min(Left,  Row[i].l);
					extend |= (R != Right) || (L != Left);
				}
			}
			for (int i = 0; i < nCol; i++) {
				if (Col[i].now >= Left && Col[i].now <= Right) {
					int U = Up, D = Down;
					if (Col[i].l <= Up) Up = std::max(Up, Col[i].r);
					if (Col[i].r >= Down) Down = std::min(Down, Col[i].l);
					extend |= (U != Up) || (D != Down);
				}
			}
			if (!extend) break;
		}
		if (X >= Left && X <= Right && Y >= Down && Y <= Up) return false;
		else return true;
	}

	void solve(void) {
		Input();
		int l = 0, r = 1 << 20;
		while (l <= r) {
			int mid = (l + r) >> 1;
			if (Check(mid))
				l = mid + 1;
			else 
				r = mid - 1;
		}
		printf("%d\n", l);
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
