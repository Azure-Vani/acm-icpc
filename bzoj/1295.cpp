//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cmath>
namespace Solve {
	const long MAXN = 35;
	const long Len = 90000;
	long n, m, G[MAXN][MAXN] = {0}, T;double A = 0;
	long delta[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
	struct queue {
		long x, y;
		inline void Push(long _x, long _y) {x = _x, y = _y;}
	};
	void Input(void) {
		scanf("%ld %ld %ld", &n, &m, &T);
		for (long i = 1; i <= n; i++) {
			scanf("\n");
			for (long j = 1; j <= m; j++)
				G[i][j] = getchar() - '0';
		}
	}
	#define sqr(x) ((x) * (x))
	inline double Dis(long x1, long y1, long x2, long y2) {
		return sqrt(sqr(x1 - x2) + sqr(y1 - y2));
	}
	void Spfa(long d, long x, long y) {
		queue Q[Len];
		long head = 1, tail = 1; bool hash[MAXN][MAXN] = {0};
		long dis[MAXN][MAXN] = {0};
		Q[1].Push(x, y); hash[x][y] = true;
		memset(dis, 101, sizeof dis);
		dis[x][y] = d;
		while (head <= tail) {
			long lx = Q[head].x, ly = Q[head++].y;
			for (long i = 0; i < 4; i++) {
				long rx = lx + delta[i][0], ry = ly + delta[i][1];
				if (rx > 0 && rx <= n & ry > 0 && ry <= m) 
					if (dis[rx][ry] > dis[lx][ly] + G[rx][ry]) {
						dis[rx][ry] = dis[lx][ly] + G[rx][ry];
						if (dis[rx][ry] <= T)
							A = std::max(A, Dis(x, y, rx, ry));
						if (!hash[rx][ry])
							hash[rx][ry] = true, Q[++tail].Push(rx, ry);
					}
			}
			hash[lx][ly] = false;
		}
	}
	void Work(void) {
		Input();
		for (long i = 1; i <= n; i++)
			for (long j = 1; j <= m; j++)
					Spfa(G[i][j], i, j);
		printf("%.6lf\n", A);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::Work();
	return 0;
}
