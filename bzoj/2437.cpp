
#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>
#include <vector>

#define rep(i,l,r) for(int i = (l); i <= (r); i++)
#define In(a, b, c) (((a) >= (b)) && ((a) <= (c)))
#define ok(x,y) (((x)&1) ^ ((y)&1))
#define check(x,y) (((abs(x - px) + abs(y - py)) & 1) == (a[x][y] == target))

namespace Solve {
	const int MAXN = 45;
	const int MAXM = MAXN * MAXN;

	int ScanInt(void) {
		int c, r = 0, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0';
		while ( isdigit(d = getchar())) r = r * 10 + d - '0';
		return c=='-'?-r:r;
	}

	struct Edge {
		int y; Edge *next;
		Edge(int y, Edge *next):y(y), next(next){}
	}*e[MAXM];
	inline void AddEdge(int x, int y) {
		e[x] = new Edge(y, e[x]);
	}

	int n, m, a[MAXN][MAXN], px, py, cnt, lab[MAXN][MAXN];
	int dx[] = {0,1,0,-1}, dy[] = {1,0,-1,0};

	inline void Input(void) {
		scanf("%d%d\n",&n, &m);
		cnt = n * m;
		for (int i = 1; i <= n; i++, scanf("\n")) {
			for (int j = 1; j <= m; j++) {
				int t = getchar();
				if (t == 'O') a[i][j] = 1;
				if (t == 'X') a[i][j] = 2;
				if (t == '.') a[i][j] = 2, px = i, py = j;
				lab[i][j] = (i - 1) * m + j;
			}
		}
	}

	int hash[MAXM], link[MAXM], cur;

	inline bool Dfs(int u, bool flag = true) {
		for (Edge *p = e[u]; p; p = p->next) {
			if (hash[p->y] != cur) {
				hash[p->y] = cur;
				if (!link[p->y] || Dfs(link[p->y], flag)) {
					if (flag) link[p->y] = u;
					return true;
				}
			}
		}
		return false;
	}

	inline void Prepare(int target) {
		memset(e, 0, sizeof e);
		a[px][py] = (3 ^ target);
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= m; j++) if (check(i,j)) {
				for (int k = 0; k <= 3; k++) {
					int x = i + dx[k], y = j + dy[k];
					if (In(x, 1, n) && In(y, 1, m) && ((a[x][y] ^ a[i][j]) == 3) && check(x,y)){
						AddEdge(lab[i][j], lab[x][y]);
					}
				}
			}
		a[px][py] = 3;
	}

	inline bool get(int target) {
		Prepare(target);
		memset(link, 0, sizeof link);
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= m; j++) if (ok(i, j)) {
				cur++;
				Dfs(lab[i][j]);
			}
		for (int i = 1; i <= n; i++) 
			for (int j = 1; j <= m; j++) if (!ok(i,j))
				link[link[lab[i][j]]] = lab[i][j];
		int u = lab[px][py];
		if (!link[u]) return false;
		cur++;
		hash[u] = cur;
		bool ret = !Dfs(link[u], false);
		return ret;
	}

	std::vector<int> ret;

	inline void Work(void) {
		bool last = get(1);
		int k = ScanInt();
		for (int i = 1; i <= (k << 1); i++) {
			int nx = ScanInt(), ny = ScanInt();
			std::swap(a[px][py], a[nx][ny]);
			px = nx, py = ny;
			bool now = get((i&1) ? 2 : 1);
			if (i&1) now ^= 1;
			if ((i&1) && last && !now)
				ret.push_back(i);
			last = now;
		}
		printf("%ld\n",ret.size());
		for (std::vector<int>::iterator it = ret.begin(); it != ret.end(); ++it)
			printf("%d\n",(*it + 1) >> 1);
	}

	void solve(void) {
		Input();
		Work();
	}
}

int main(int argc, char* argv[]) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
