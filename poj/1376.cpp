#include <cstdio>
#include <set>
#include <cstring>
#include <queue>
#include <algorithm>
#define REP(i, l, r) for(int i = l; i <= r; i++)
#define mp make_pair
#define X first
#define Y second

using namespace std;

typedef pair<int, int> PII;
const int MAXN = 55;

int dx[] = {1, 0, -1, 0};
int dy[] = {0, 1, 0, -1};
int n, m; int a[55][55];

char ch[10];

PII vs, vt;
queue<pair<PII, PII> > Q;
set<pair<int, PII> > S;

inline bool OK(int x, int y) {
	return x >= 1 && x <= n && y >= 1 && y <= m && !a[x][y];
}

inline bool Check(int x, int y) {
	return OK(x, y) && OK(x + 1, y + 1) && OK(x + 1, y) && OK(x, y + 1);
}

int main(void) {
	freopen("in", "r", stdin);
	while (scanf("%d%d", &n, &m), n || m) {
		REP(i, 0, n + 1) a[i][0] = a[i][m + 1] = true;
		REP(i, 0, m + 1) a[0][i] = a[n + 1][i] = true;
		REP(i, 1, n) REP(j, 1, m) scanf("%d", &a[i][j]);
		while (!Q.empty()) Q.pop();
		S.clear();
		scanf("%d%d%d%d%s", &vs.X, &vs.Y, &vt.X, &vt.Y, ch);
		int dir = 0;
		if (strcmp(ch, "north") == 0) dir = 2;
		if (strcmp(ch, "west") == 0) dir = 3;
		if (strcmp(ch, "east") == 0) dir = 1;
		Q.push(mp(mp(0, dir), vs));
		bool find = false;
		while (!Q.empty()) {
			pair<PII, PII> now = Q.front(), tmp; 
			Q.pop();
			if (now.Y.X == vt.X && now.Y.Y == vt.Y) {
				find = true;
				printf("%d\n", now.X.X);
				break;
			}
			REP(k, 1, 3) {
				int nx = now.Y.X + dx[now.X.Y] * k;
				int ny = now.Y.Y + dy[now.X.Y] * k;
				if (!Check(nx, ny)) break;
				tmp = mp(mp(now.X.X + 1, now.X.Y), mp(nx, ny));
				if (S.find(mp(now.X.Y, mp(nx, ny))) == S.end()) {
					S.insert(mp(now.X.Y, mp(nx, ny)));
					Q.push(tmp);
				}
			}
			REP(k, -1, 1) if (k) {
				int nd = (now.X.Y + k) % 4; if (nd < 0) nd += 4;
				tmp = mp(mp(now.X.X + 1, nd), mp(now.Y.X, now.Y.Y));
				if (S.find(mp(nd, mp(now.Y.X, now.Y.Y))) == S.end()) {
					S.insert(mp(nd, mp(now.Y.X, now.Y.Y)));
					Q.push(tmp);
				}
			}
		}
		if (!find) {puts("-1");}
	}
}

