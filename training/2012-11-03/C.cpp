#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {
	const int MAXN = 88;

	int m, n;
	string a[MAXN], dic[MAXN];
	int fim[26], P[MAXN], len[MAXN], uni_Len[MAXN], dlen[MAXN], duni_Len[MAXN];
	int link[MAXN], final_link[MAXN];

	inline int F(string s) {
		sort(s.begin(), s.end());
		s.erase(unique(s.begin(), s.end()), s.end());
		return s.length();
	}

	inline bool cmp(int a, int b) {
		return uni_Len[b] < uni_Len[a];
	}

	inline void Input(void) {
		memset(fim, -1, sizeof fim);
		REP(i, 1, m) cin >>dic[i], dlen[i] = dic[i].length(), duni_Len[i] = F(dic[i]);
		while (cin >>a[++n] && a[n][a[n].length() - 1] != '.'); a[n].erase(a[n].length() - 1, 1);
		REP(i, 1, n) P[i] = i, len[i] = a[i].length(), uni_Len[i] = F(a[i]);
		sort(P + 1, P + n + 1, cmp);
	}

	inline bool Connect(int x, int y) {
		if (fim[x] == -1 && fim[y] == -1) return true;
		if (fim[x] == y && fim[y] == x) return true;
		return false;
	}

	int cnt = 0;
	inline void Dfs(int now) {
		if (now > n) {
			++cnt;
			REP(i, 1, n) final_link[i] = link[i];
			return;
		}
		if (cnt >= 2) return;
		int u = P[now], b_fim[26] = {0};
		REP(i, 1, m) if (dlen[i] == len[u] && duni_Len[i] == uni_Len[u]) {
			memcpy(b_fim, fim, sizeof fim);
			int L = len[u]; bool ok = true;
			link[u] = i;
			for (int j = 0; j < L; j++) {
				if (!Connect(dic[i][j] - 'A', a[u][j] - 'A')) {
					ok = false;
					break;
				} else {
					fim[dic[i][j] - 'A'] = a[u][j] - 'A';
					fim[a[u][j] - 'A'] = dic[i][j] - 'A';
				}
			}
			if (ok) {
				Dfs(now + 1);
			}
			memcpy(fim, b_fim, sizeof fim);
			link[u] = 0;
		}
	}

	inline void solve(void) {
		while (true) {
			scanf("%d", &m); n = 0;
			memset(fim, 0, sizeof fim); cnt = 0;
			if (m == 0) return;
			Input();
			Dfs(1);
			if (cnt >= 2) {
				puts("-.");
			} else {
				if (cnt == 1) {REP(i, 1, n - 1) cout <<dic[final_link[i]]<<' '; cout <<dic[final_link[n]]<<'.'<<endl;}
				else {
					puts("orz DYF!");
				}
			}
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}

