#include <cstdio>
#include <vector>
#include <algorithm>
#define rep(i,n) for(int i = 1; i <= n; i++)
#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)

using namespace std;

const int MAXN = 40010;

int n, m, d1[MAXN], d2[MAXN], d[MAXN]; vector<int> a[MAXN];

inline void Bfs(int u, int dis[]) {
	int head = 1, tail = 1; d[1] = u; dis[u] = 1;
	while(head <= tail) {
		int now = d[head++];
		foreach(it, a[now]) if (!dis[*it]) dis[d[++tail] = *it] = dis[now] + 1;
	}
}

int A, B, C, D, E;

int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d%d", &n, &m);
	rep(i,m) { int x, y; scanf("%d%d", &x, &y);
		a[x].push_back(y);
		a[y].push_back(x);
	}
	Bfs(1, d1); Bfs(2, d2);
	rep(i,n) {
		if (d1[i] == 2) A++;
		if (d1[i] == 3) B++;
		if (d2[i] == 2) C++;
		if (d2[i] == 3) D++;
	} E = n - A - B - C - D - 2;
	int Ans = n * (n - 1) / 2 - m - (n - 1 - A) - A * (C + D + 1) - B * (C + 1) - D - E - min(A, C) * E;
	printf("%d\n", Ans);
	return 0;
}

