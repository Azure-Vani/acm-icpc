//#define Debug
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <queue>
namespace Solve {
	const int MOD = 10007;
	const int MAXN = 105;
	const int SUM = 105 * 60;
	int n, m;
	char ch[MAXN];
	
	struct Node {
		int next[26], Fail; bool end;
	}S[SUM];int sid = 0;
	
	class Trie {public:
		void Insert(char seg[], int n) {
			int now = 0;
			for (int i = 0; i < n; i++) {
				int t = seg[i] - 'A';
				if (!S[now].next[t]) S[now].next[t] = ++sid;
				now = S[now].next[t];
			}
			S[now].end = true;
		}
		void Bfs(void) {
			std::queue <int> Q;
			S[0].Fail = -1;
			for (int i = 0; i < 26; i++) if (S[0].next[i]) Q.push(S[0].next[i]);
			while (Q.size()) {
				int now = Q.front(); Q.pop();
				for (int i = 0; i < 26; i++) if (S[now].next[i]) {
					int t = S[now].Fail;
					while (t && !S[t].next[i]) t = S[t].Fail;
					if (S[t].next[i]) t = S[t].next[i];
					S[S[now].next[i]].Fail = t;
					if (S[t].end) S[S[now].next[i]].end = true;
					Q.push(S[now].next[i]);
				}
			}

			for (int i = 0; i < 26; i++) if (S[0].next[i]) Q.push(S[0].next[i]);
			while (Q.size()) {
				int now = Q.front(); Q.pop();
				int sum = 0, t = S[now].Fail;
				for (int i = 0; i < 26; i++) if (S[now].next[i]) sum++, Q.push(S[now].next[i]);
				while (t != -1 && sum < 26) {
					for (int i = 0; i < 26; i++) if (S[t].next[i] && !S[now].next[i])
						S[now].next[i] = S[t].next[i], sum++;
					t = S[t].Fail;
				}
			}
		}
	}T;

	void Input(void) {
		scanf("%d%d\n", &n, &m);
		for (int i = 1; i <= n; i++) {
			gets(ch);
			T.Insert(ch, strlen(ch));
		}
	}

	int f[MAXN][SUM][2];
	void solve(void) {
		Input();
		T.Bfs();
		f[0][0][0] = 1;
		for (int i = 0; i < m; i++)
			for (int j = 0; j <= sid; j++) {
				for (int k = 0; k < 26; k++)
					if (S[S[j].next[k]].end) {
						f[i + 1][S[j].next[k]][1] = (f[i + 1][S[j].next[k]][1] + f[i][j][0] + f[i][j][1]) % MOD;
					}else {
						f[i + 1][S[j].next[k]][0] = (f[i + 1][S[j].next[k]][0] + f[i][j][0]) % MOD;
						f[i + 1][S[j].next[k]][1] = (f[i + 1][S[j].next[k]][1] + f[i][j][1]) % MOD;
					}
			}
		int Ans = 0;
		for (int i = 0; i <= sid; i++) Ans = (Ans + f[m][i][1]) % MOD;
		printf("%d\n", Ans);
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
	#endif
	Solve::solve();
	return 0;
}