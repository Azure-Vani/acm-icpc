#include <cstdio>
#include <cctype>
#include <vector>
#include <cstring>
#include <algorithm>
#define REP(i, l, r) for(int i = l; i <= r; i++)
#define OK(s, i) (((s) >> (i)) & 1)
using namespace std;

namespace Solve {
	const int maxn = 55;
	const int inf = ~0U>>3;

	inline int Scanint(void) {
		int r = 0, c;
		while (!isdigit(c = getchar())) ;
		r = c - '0';
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return r;
	}

	int n, m, a[maxn][maxn], rev_dis[maxn][maxn], dis[maxn][maxn], h[maxn], cost[maxn], tmp_dis[maxn][maxn], tmp_dis_rev[maxn][maxn]; 
	vector<int> List[1001];

	inline void Input(void) {
		REP(i, 1, 1000) List[i].clear();
		REP(i, 2, n - 1) cost[i] = Scanint(), h[i] = Scanint(), List[h[i]].push_back(i);
		List[0].push_back(1); List[1000].push_back(n); h[n] = 1000;
		REP(i, 1, n) a[i][i] = 0, dis[i][i] = 0, rev_dis[i][i] = 0;
		REP(i, 1, m) {
			int x = Scanint(), y = Scanint(), z = Scanint();
			a[x][y] = z; 
			dis[x][y] = a[x][y] + cost[y];
			rev_dis[y][x] = a[x][y] + cost[x];
		}
	}

	inline void Init(void) {
		REP(k, 1, n) REP(i, 1, n) REP(j, 1, n) {
			if (h[i] <= h[k] && h[k] <= h[j]) dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			if (h[i] <= h[k] && h[k] <= h[j]) rev_dis[i][j] = min(rev_dis[i][j], rev_dis[i][k] + rev_dis[k][j]);
		}
	}

	int inp[maxn][maxn], out[maxn][maxn];

	inline void Work(void) {
		out[1][1] = 0;
		REP(height, 1, 1000) if (List[height].size()) {
			vector<int>& now = List[height]; int len = now.size();
			REP(i, 0, len - 1) REP(j, 0, len - 1) {
				int &tmp = inp[now[i]][now[j]];
				REP(l1, 1, n) if (h[l1] < height) REP(l2, 1, n) if (h[l2] < height && h[l1] == h[l2]) {
					tmp = min(tmp, out[l1][l2] + dis[l1][now[i]] - cost[now[i]] + rev_dis[l2][now[j]] - cost[now[j]]);
				}
			}
			REP(s, 0, (1 << len) - 1) {
				int pre = 0;
				REP(i, 0, len - 1) if (OK(s,i)) pre += cost[now[i]];
				REP(i, 0, len - 1) REP(j, 0, len - 1) tmp_dis[i][j] = tmp_dis_rev[i][j] = inf;
				REP(i, 0, len - 1) if (OK(s,i)) REP(j, 0, len - 1) if (OK(s, j)) 
					tmp_dis[i][j] = a[now[i]][now[j]], tmp_dis_rev[i][j] = a[now[j]][now[i]];
				REP(k, 0, len - 1) if (OK(s,k)) REP(i, 0, len - 1) if (OK(s,i)) REP(j, 0, len - 1) if (OK(s,j)) {
					tmp_dis[i][j] = min(tmp_dis[i][j], tmp_dis[i][k] + tmp_dis[k][j]);
					tmp_dis_rev[i][j] = min(tmp_dis_rev[i][j], tmp_dis_rev[i][k] + tmp_dis_rev[k][j]);
				}
				REP(i, 0, len - 1) if (OK(s,i)) REP(j, 0, len - 1) if (OK(s,j)) 
					REP(_i, 0, len - 1) if (OK(s,_i)) REP(_j, 0, len - 1) if (OK(s,_j))
					out[now[i]][now[j]] = min(out[now[i]][now[j]], pre + inp[now[_i]][now[_j]] + tmp_dis[_i][i] + tmp_dis_rev[_j][j]);
			}
		}
	}

	inline void solve(void) {
		while (n = Scanint(), m = Scanint(), n || m) {
			memset(cost, 0, sizeof cost);
			REP(i, 0, n) REP(j, 0, n) inp[i][j] = out[i][j] = dis[i][j] = a[i][j] = rev_dis[i][j] = inf;
			Input();
			Init();
			Work();
			if (out[n][n] == out[0][0]) {
				puts("-1");
			} else {
				printf("%d\n", out[n][n]);
			}
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	Solve::solve();
	return 0;
}

