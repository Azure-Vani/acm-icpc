//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <queue>
#define mp std::make_pair
namespace Solve {
	const int MAXV = 200020;
	const int MAXK = 22;
	
	struct Edge {
		int y, z; Edge *next;
		Edge(int y, int z, Edge *next):y(y), z(z),next(next){}
	}*a[MAXV];

	inline int ScanInt(void) {
		int r = 0, c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}

	int n, m, k, base[MAXK];
	inline void Input(void) {
		n = ScanInt(), m = ScanInt(), k = ScanInt();
		for (int i = 1; i <= m; i++) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			a[x] = new Edge(y, z, a[x]);
			a[y] = new Edge(x, z, a[y]);
		}
		int nLimit = ScanInt();
		for (int i = 1; i <= nLimit; i++) {
			int x = ScanInt(), y = ScanInt();
			base[y - 1] |= (1 << (x - 2));
		}
	}

	inline void Dijkstra(int dis[], int vs) {
		memset(dis, 60, sizeof (int) * MAXV);
		std::priority_queue< std::pair<int, int> > Q;
		dis[vs] = 0;
		Q.push(mp(-dis[vs], vs));
		for (int i = 1; i < n; i++) {
			while (!Q.empty() && -Q.top().first > dis[Q.top().second]) Q.pop();
			if (Q.empty()) break;
			int now = Q.top().second; dis[now] = -Q.top().first; Q.pop();
			for (Edge *p = a[now]; p; p = p->next)
				if (dis[p->y] > dis[now] + p->z) 
					Q.push(mp(-(dis[p->y] = dis[now] + p->z), p->y));
		}
	}

	int dis[MAXK][MAXV];
	int f[MAXK][(1 << 20) - 1];
	int state[MAXK][(1 << 20) - 1], C[MAXK];

	#define Lowbit(x) ((x) & (-(x)))
	void Work(void) {
		for (int i = 0; i <= k; i++)
			Dijkstra(dis[i + 1], i + 1);
		if (k == 0) {
			printf("%d\n", dis[1][n]);
			return;
		}
		for (int i = 0; i < (1 << k); i++) {
			int t = i, l = 0;
			while (t)
				l++, t -= Lowbit(t);
			state[l][++C[l]] = i;
		}
		memset(f, 60, sizeof f);
		int inf = f[0][0];
		
		for (int i = 1; i <= k; i++)
			if (base[i] == 0)
				f[i][1 << (i - 1)] = dis[1][i + 1];

		for (int i = 1; i < k; i++) {
			int cnt = C[i];
			for (int j = 1; j <= cnt; j++) {
				int S = state[i][j];
				for (int now = 1; now <= k; now++) {
					int v = f[now][S];
					if (v < inf) {
						for (int next = 1; next <= k; next++)
							if (((S >> (next - 1)) & 1) == 0 && (base[next] & S) == base[next]) {
								int ns = (S | (1 << (next - 1)));
								f[next][ns] = std::min(f[next][ns], v + dis[now + 1][next + 1]);
							}
					}
				}
			}
		}
		
		int Ans = 0x7fffffff;
		for (int i = 1; i <= k; i++)
			Ans = std::min(Ans, dis[i + 1][n] + f[i][(1 << k) - 1]);
		printf("%d\n", Ans);
	}

	void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
