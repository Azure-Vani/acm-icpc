//#define Debug
#include <queue>
#include <cstdio>
#include <algorithm>
#include <cstring>
#define mp std::make_pair
namespace Solve {
	const int MAXN = 710;
	
	bool map[MAXN][MAXN]; char ch[MAXN];
	int n, m, vs[2][2], vt[2];

	void Input(void) {
		scanf("%d%d\n", &n, &m);
		for (int i = 1; i <= n; i++) {
			gets(ch + 1);
			for (int j = 1; j <= m; j++) {
				map[i][j] = (ch[j] != 'I');
				if (ch[j] == 'Y') vs[0][0] = i, vs[0][1] = j;else
				if (ch[j] == 'V') vs[1][0] = i, vs[1][1] = j;else
				if (ch[j] == 'T') vt[0] = i, vt[1] = j;
			}
		}
	}

	int row_belong[MAXN][MAXN], col_belong[MAXN][MAXN], l;

	inline void Extend(bool a[], int n, int f[]) {
		memset(f, 0, sizeof(int) * MAXN);
		for (int i = 1; i <= n; i++) if (a[i])
			f[i] = a[i - 1] ? f[i - 1] : ++l;
	}

	void Cut(void) {
		bool seg[MAXN] = {0};
		int ret[MAXN] = {0};
		for (int i = 1; i <= n; i++) {
			Extend(map[i], m, row_belong[i]);
		}
		l = 0;
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++)
				seg[j] = map[j][i];
			Extend(seg, n, ret);
			for (int j = 1; j <= n; j++)
				col_belong[j][i] = ret[j];
		}
	}

	int fim[4][2] = {{0,1},{1,0},{-1,0},{0,-1}};

	int level[MAXN][MAXN], row_tim[MAXN * MAXN], col_tim[MAXN * MAXN];
	void Bfs(int x, int y) {
		memset(row_tim, 60, sizeof row_tim);
		memset(col_tim, 60, sizeof col_tim);
		std::queue< std::pair<int, int> > Q ;
		Q.push(mp(x, y));
		level[x][y] = 1;
		while (!Q.empty()) {
			int X = Q.front().first, Y = Q.front().second, t = level[X][Y]; Q.pop();
			row_tim[row_belong[X][Y]] = std::min(row_tim[row_belong[X][Y]], t);
			col_tim[col_belong[X][Y]] = std::min(col_tim[col_belong[X][Y]], t);
			for (int i = 0; i < 4; i++) {
				int lx = X + fim[i][0], ly = Y + fim[i][1];
				if (map[lx][ly] && level[lx][ly] == 0) {
					Q.push(mp(lx, ly));
					level[lx][ly] = t + 1;
				}
			}
		}
	}

	int tim[MAXN][MAXN];
	void Work(int x, int y) {
		std::queue< std::pair<int, int> > Q ;
		Q.push(mp(x, y));
		tim[x][y] = 1;
		while (!Q.empty()) {
			int X = Q.front().first, Y = Q.front().second, t = tim[X][Y]; Q.pop();
			for (int i = 0; i < 4; i++) {
				int lx = X + fim[i][0], ly = Y + fim[i][1];
				int T = std::min(col_tim[col_belong[lx][ly]], row_tim[row_belong[lx][ly]]);
				if (map[lx][ly] && tim[lx][ly] == 0 && t + 1 < T) {
					Q.push(mp(lx, ly));
					tim[lx][ly] = t + 1;
				}
			}
		}
	}

	void solve(void) {
		Input();
		Cut();
		Bfs(vs[1][0], vs[1][1]);
		Work(vs[0][0], vs[0][1]);
		int t1 = tim[vt[0]][vt[1]];
		puts(t1?"YES":"NO");
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
