#define STDIO
#define INPUT "in"
#define OUTPUT "out"

#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
namespace Solve {
	typedef std::vector<int> VII;
	typedef std::queue<int> QII;
	const int MAXN = 3005;

	struct Edge {
		int y, z; Edge *next;
		Edge(int y, int z, Edge *next):y(y), z(z), next(next){}
	}*a[MAXN];

	int n, m, cnt[MAXN];
	VII c[MAXN];

	inline void Input(FILE *fin) {
		fscanf(fin, "%d%d", &n, &m);
		for (int i = 1; i <= m; i++) {
			int x, y, z;
			fscanf(fin, "%d%d%d", &x, &y, &z);
			a[x] = new Edge(y, z, a[x]);
		}
		for (int i = 1; i <= n; i++) {
			int &num = cnt[i], t;
			fscanf(fin, "%d", &num);
			for (int j = 1; j <= num; j++) {
				fscanf(fin, "%d", &t);
				c[t].push_back(i);
			}
		}
	}

	int dis[MAXN];
	bool update[MAXN] = {0,1};

	inline int Work(void) {
		memset(dis, 60, sizeof dis);
		dis[1] = 0;
		while (true){
			int now = 0, min = 0x7fffffff;
			for (int i = 1; i <= n; i++) if (!cnt[i] && update[i] && dis[i] < min)
				min = dis[i], now = i;
			if (!now) break;
			update[now] = false;
			for (Edge *p = a[now]; p; p = p->next) 
				if (dis[p->y] > dis[now] + p->z) {
					dis[p->y] = dis[now] + p->z;
					update[p->y] = true;
				}
			for (VII::iterator it = c[now].begin(); it != c[now].end(); it++) {
				cnt[*it]--;
				if (dis[*it] < dis[now]) {
					dis[*it] = dis[now];
					update[*it] = true;
				}
			}
		}
		return dis[n];
	}
	
	void solve(FILE *fin, FILE *fout) {
		Input(fin);
		int Ans = Work();
		fprintf(fout, "%d\n", Ans);
	}
}

int main(int argc, char* argv[]) {
#ifdef STDIO
	Solve::solve(stdin, stdout);
#else
	FILE *fin = fopen(INPUT, "r"),
	     *fout = fopen(OUTPUT, "w");
	Solve::solve(fin, fout);
	fclose(fin);
	fclose(fout);
#endif
	return 0;
}
