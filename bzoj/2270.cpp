#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <cstring>
namespace Solve {
	const int MAXN = 22;
	const int MAXM = 1 << 22;

	int n, m, g[MAXN];

	inline void Input(void) {
		if (scanf("%d%d", &n, &m) , n==0 && m == 0) exit(0);
		while (m--) {
			int a, b;
			scanf("%d%d", &a, &b);
			g[a] |= (1 << b);
			g[b] |= (1 << a);
		}
	}

	int f[MAXM], prev[MAXM], Lab[MAXM], Ans[MAXN];
	
	void clear(void) {
		memset(g, 0, sizeof (int) * n);
	}

	inline void Work(void) {
		std::queue<int> Q;
		int inf = f[0], o = -1;
		Q.push((1 << n) - 1); f[(1 << n) - 1] = 0;
		while (!Q.empty()) {
			int Status = Q.front(); Q.pop();
			if (Status == 0) {o = 0; break;}
			int Base = 0;
			for (int i = 0; i < n; i++)
				if ((Status & (1 << i)))
					Base |= g[i];
			for (int i = 0; i < n; i++) {
				int next = Base & (~(1 << i));
				if (f[next] > f[Status] + 1) {
					f[next] = f[Status] + 1;
					Q.push(next);
					prev[next] = Status;
					Lab[next] = i;
				}
			}
		}
		if (o == -1) 
			puts("Impossible");
		else {
			printf("%d: ", f[0]);
			int cnt = 0, now = 0;
			while (now + 1 != (1 << n)) 
				Ans[++cnt] = Lab[now], now = prev[now];
			for (int i = cnt; i > 1; i--) printf("%d ", Ans[i]); printf("%d\n", Ans[1]);
		}
	}

	void solve(void) {
		clear();
		Input();
		memset(f, 60, sizeof (int) * (1 << n));
		Work();
	}
}
int main(int argc, char** argv) {
	while(true)
	Solve::solve();
	return 0;
}
