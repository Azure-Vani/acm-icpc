//#define Debug
#include <vector>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
namespace Solve {
	const int MAXN = 315;

	int n;
	struct pair {int x, y; inline friend bool operator ==(const pair& a, const pair& b) {return a.x == b.x && a.y == b.y;}};
	inline pair Set(int x, int y) {pair ret; ret.x = x, ret.y = y; return ret;}
	bool map[MAXN][MAXN];
	pair vs, vt;

	void Input(void) {
		scanf("%d\n", &n);
		memset(map, 0, sizeof map);
		for (int i = 1; i <= n; i++, scanf("\n"))
			for (int j = 1; j <= n; j++) {
				int c = getchar();
				if (c != '#') map[i][j] = true;
				if (c == 'A') vs = Set(i, j);
				if (c == 'B') vt = Set(i, j);
			}
	}

	int fim[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	inline void Bfs(pair vs, int level[MAXN][MAXN]) {
		std::queue<pair> Q;
		Q.push(vs);
		level[vs.x][vs.y] = 0;

		while (Q.size()) {
			pair now = Q.front(); Q.pop();
			for (int i = 0; i < 4; i++) {
				int lx = now.x + fim[i][0], ly = now.y + fim[i][1];
				if (!map[lx][ly] || level[lx][ly] != -1) continue;
				level[lx][ly] = level[now.x][now.y] + 1;
				Q.push(Set(lx, ly));
			}
		}
	}

	int D;
	struct Edge {
		pair y; Edge* next; int t;
		Edge(pair y, Edge* next):y(y), next(next){}
	};
	class List {public:
		Edge *a[MAXN * MAXN];
		int index[MAXN][MAXN], num[MAXN * MAXN];
		int level[MAXN][MAXN];
		void clear(void) {
			memset(index, 0, sizeof index);
			memset(level, -1, sizeof level);
			memset(num, 0, sizeof num);
			memset(a, 0, sizeof a);
		}
		void Build(void) {
			for (int i = 1; i <= n; i++)
				for (int j = 1; j <= n; j++) if (level[i][j] != -1) {
					int t = level[i][j];
					a[t] = new Edge(Set(i, j), a[t]);
					index[i][j] = ++num[t];
					a[t]->t = index[i][j];
				}
		}
		inline int Index(int x, int y) {return index[x][y];}
		inline int Dis(int x, int y) {return level[x][y];}
	};

	List listA, listB;
	
	void Prepare(void) {
		listA.clear(); listB.clear();
		Bfs(vs, listA.level);
		Bfs(vt, listB.level);
		D = listA.Dis(vt.x, vt.y);
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (listA.level[i][j] + listB.level[i][j] != D)
					listA.level[i][j] = listB.level[i][j] = -1;
		listA.Build();
		listB.Build();
		D >>= 1;
	}

	bool f[2][MAXN << 1][MAXN << 1];
	void Dp(void) {
		int now = 0, last = 1;
		memset(f, 0, sizeof f);
		for (Edge *p = listA.a[D]; p; p = p->next)
			for (Edge *q = listB.a[D]; q; q = q->next) {
				if (p->y == q->y)
					f[now][p->t][q->t] = false;
				else
					f[now][p->t][q->t] = true;
			}
		for (int step = D - 1; step >= 0; step--) {
			now ^= 1, last ^= 1;
			for (Edge *p = listA.a[step]; p; p = p->next)
				for (Edge *q = listB.a[step]; q; q = q->next) {
					pair pa = p->y, pb = q->y;
					f[now][p->t][q->t] = false;
					for (int _ = 0; _ < 4; _++) {
						int lx = pa.x + fim[_][0], ly = pa.y + fim[_][1];
						if (listA.Dis(lx, ly) != step + 1) continue;
						bool check = true;
						for (int __ = 0; __ < 4; __++) {
							int nx = pb.x + fim[__][0], ny = pb.y + fim[__][1];
							if (listB.Dis(nx, ny) != step + 1) continue;
							int IDA = listA.Index(lx, ly), IDB = listB.Index(nx, ny);
							if (!f[last][IDA][IDB]) {
								check = false;
								break;
							}
						}
						if (check) {
							f[now][p->t][q->t] = true;
							break;
						}
					}
				}
		}
		puts(f[now][1][1] ? "A" : "B");
	}
	void solve(void) {
		Input();
		Prepare();
		Dp();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	int _; scanf("%d", &_);
	while (_--)
		Solve::solve();
	return 0;
}
