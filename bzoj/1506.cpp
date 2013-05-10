#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdlib>
namespace Solve {
	const int inf = 0x6eeeeeee;
	const int MAXN = 105;

	int nRow, nCol, nLimit;
	bool ColDir[MAXN], RowDir[MAXN];
	int ColCost[MAXN], RowCost[MAXN];
	
	struct Edge {
		int l; bool dir; Edge* next;
		Edge(int l, bool dir, Edge* next):l(l), dir(dir), next(next){}
	}*Interval[MAXN];
	inline void AddLimit(int l, int r, bool dir) {
		if (l > r) std::swap(l, r);
		Interval[r] = new Edge(l, dir, Interval[r]);
	}
	
	struct PairPoint {
		int x1, y1, x2, y2;
		PairPoint(int x1, int y1, int x2, int y2):x1(x1), x2(x2) ,y1(y1), y2(y2){}
	};
	std::vector<PairPoint> Limit;

	void Input(void) {
		scanf("%d%d\n", &nRow, &nCol);
		for (int i = 1; i <= nRow; i++) RowDir[i] = getchar() == 'E';getchar();
		for (int i = 1; i <= nCol; i++) ColDir[i] = getchar() == 'N';
		for (int i = 1; i <= nRow; i++) scanf("%d", RowCost + i);
		for (int i = 1; i <= nCol; i++) scanf("%d", ColCost + i);
		int Temp; scanf("%d", &Temp);
		for (int i = 1; i <= Temp; i++) {
			int x1, y1, x2, y2;
			scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
			if (x1 == x2 && y1 == y2) continue;
			Limit.push_back(PairPoint(y1, x1, y2, x2));
		}
	}

	int GetCost(int S) {
		for (int i = 0; i < Limit.size(); i++) if (Limit[i].y1 == Limit[i].y2)
			if ((bool)(S & (1 << Limit[i].y1)) != (Limit[i].x2 > Limit[i].x1))
				return -1;
		int ret = 0;
		for (int i = 1; i <= nRow; i++) if ((bool)(S & (1 << i)) != RowDir[i])
			ret += RowCost[i];
		return ret;
	}

	inline bool Check(int S, int l, int r, bool dir) {
		if (l > r) std::swap(l, r);
		for (int i = l; i <= r; i++)
			if ((bool)(S & (1 << i)) == dir) return true;
		return false;
	}

	bool MakeLimit(int S) {
		for (int i = 0; i < Limit.size(); i++) if (Limit[i].y1 != Limit[i].y2) {
			int x1 = Limit[i].x1, y1 = Limit[i].y1, x2 = Limit[i].x2, y2 = Limit[i].y2;
			if (x1 == x2) {
				AddLimit(x1, x2, y2 < y1);
				continue;
			}
			bool dirx = (x1 < x2), diry = (y2 < y1), dirS1 = (S & (1 << y1)), dirS2 = (S & (1 << y2));

			if (dirS1 == dirx && dirS2 == dirx) {AddLimit(x1, x2, diry);} else
			if (dirS1 == dirx && dirS2 != dirx) {AddLimit(x2, x2, diry);} else
			if (dirS1 != dirx && dirS2 == dirx) {AddLimit(x1, x1, diry);} else {
				if (!Check(S, y1, y2, dirx)) return false;
				AddLimit(x1, x1, diry);
				AddLimit(x2, x2, diry);
			}
		}
		return true;
	}

	struct Node {
		int now, last; bool dir;
		Node(int now, int last, bool dir):now(now), last(last), dir(dir){}
	};

	#define Cost(i, dir) (((dir) != ColDir[i]) * ColCost[i])
	int Dp(void) {
		int f[MAXN][MAXN][2]; bool Inqueue[MAXN][MAXN][2] = {0};
		memset(f, 101, sizeof f);
		std::queue<Node> Q; f[0][1][0] = 0;
		Q.push(Node(0, 1, 0)); Inqueue[0][1][0] = true;
		
		while (Q.size()) {
			Node now = Q.front(); Q.pop();
			int i = now.now, j = now.last;bool k = now.dir;
			Inqueue[i][j][k] = false; bool OK = true;
			for (Edge *p = Interval[i]; p; p = p->next)
				if (! (k == p->dir || j >= p->l)) {OK = false; break;}
			if (!OK) {f[i][j][k] = inf; continue;}
			if (i == nCol) continue;

			//(i + 1)'s direction is k.
			if (f[i + 1][j][k] > f[i][j][k] + Cost(i + 1, k)) {
				f[i + 1][j][k] = f[i][j][k] + Cost(i + 1, k);
				Q.push(Node(i + 1, j, k));
				Inqueue[i + 1][j][k] = true;
			}
			
			//(i + 1)'s direction is opposite to k.
			if (f[i + 1][i][!k] > f[i][j][k] + Cost(i + 1, !k)) {
				f[i + 1][i][!k] = f[i][j][k] + Cost(i + 1, !k);
				Q.push(Node(i + 1, i, !k));
				Inqueue[i + 1][i][!k] = true;
			}
		}

		int ret = f[0][0][1];
		for (int i = 1; i <= nCol; i++)
			ret = std::min(std::min(f[nCol][i][0], f[nCol][i][1]), ret);
		if (ret != f[0][0][1]) return ret; else return -1;
	}

	void Work(void) {
		int Ans = inf;
		for (int S = 0; S < 1 << nRow + 1; S += 2, memset(Interval, 0, sizeof Interval)) {
			int cost = GetCost(S);
			if (cost == -1) continue;
			if (!MakeLimit(S)) continue;
			int ret = Dp();
			if (ret != -1)
				Ans = std::min(ret + cost, Ans);
		}
		if (Ans == inf) puts("impossible"); else printf("possible\n%d\n", Ans);
	}
	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("manhattan.in", "r", stdin);
		freopen("manhattan.ans", "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
