#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

int a[30], b[30];

char ch[100][100] = {".X.X.", "XX..X", ".XXX.", "...X.", ".X.XX"};

class EllysFigurines {public:
	int getMoves(vector<string> board, int R, int C) {
		int ret = 33, n = board.size(), m = board[0].size();
		for (int i = 0; i < (1 << n); ++i) {
			memset(a, 0, sizeof a); memset(b, 0, sizeof b);
			for (int j = 0; j < n; j++) if (i & (1 << j)) a[j] = 1;
			int r = 0, last = 0, c = 0;
			while (last < n) {
				while (!a[last] && last < n) last++;
				if (last < n) r++;
				last += R;
			}
			for (int l1 = 0; l1 < n; l1++)
				for (int l2 = 0; l2 < m; l2++) if (!a[l1] && board[l1][l2] == 'X') b[l2] = 1;
			last = 0;
			while (last < m) {
				while (!b[last] && last < m) last++;
				if (last < m) c++;
				last += C;
			}
			ret = min(ret, c + r);
		}
		return ret;
	}
};

int main(void) {
	EllysFigurines a;
	printf("%d\n", a.getMoves(vector<string>(10, "XX..XX."), 10, 10));
	return 0;
}

