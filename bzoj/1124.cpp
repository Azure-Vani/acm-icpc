//#define Debug
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
namespace Solve {
	const int MAXN = 1000020;

	int p[MAXN], inp[MAXN], n;
	
	void Input(void) {
		scanf("%d", &n);
		for (int i = 1; i <= n; i++) scanf("%d", p + i), inp[p[i]]++;
	}
	
	int delta = 0; bool vis[MAXN] = {0};
	int Dfs(int u) {vis[u] = true;int ret = 1;if (!vis[p[u]]) ret += Dfs(p[u]);return ret;}
	int aM, AI;

	void MakeMax(void) {
		int ret = 0;
		for (int i = 1; i <= n; i++) if (!vis[i] && inp[i] == 0)
			Dfs(i), ret++;
		for (int i = 1; i <= n; i++) if (!vis[i] && p[i] != i)
			Dfs(i), ret++;
		aM = n - ret;
	}

	void DFs(int u, int deep) {
		vis[u] = true;
		if (deep & 1) delta++;
		if (!vis[p[u]]) {
			inp[p[u]]--;
			if (inp[p[u]] == 0 || deep == 0)
				DFs(p[u], deep ^ 1);
		}
	}
	void MakeMin(void) {
		memset(vis, 0, sizeof vis);
		for (int i = 1; i <= n; i++) if (!vis[i] && inp[i] == 0)
			DFs(i, 0);
		for (int i = 1; i <= n; i++) if (!vis[i])
			delta += ((Dfs(i) + 1) >> 1);
		AI = delta;
	}

	void solve(void) {
		Input();
		MakeMax();
		MakeMin();
		printf("%d %d\n", AI, aM);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}
