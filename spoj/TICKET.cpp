#include <cstdio>
#include <cstring>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <queue>
#include <algorithm>

using namespace std;

namespace Solve {
	const int MAXN = 100;
	const int MAXM = 50000;
	int inf;

	map<string, int> M;
	vector<int> go[MAXN];
	int n, m, c[MAXN][MAXN];

	inline void Input(void) {
		for (int i = 1; i <= n; i++) {string st; cin >>st; M[st] = i;}
		for (int i = 1, t; i <= m; i++) {
			string st, ss; cin >>st>>ss>>t;
			c[M[st]][M[ss]] = min(c[M[st]][M[ss]], t);
			c[M[ss]][M[st]] = c[M[st]][M[ss]];
		}
		for (int i = 0; i < 8; i++) {
			string st; cin >>st; go[M[st]].push_back(1 << i);
		}
	}

	struct Node {
		int pos, s;
		Node(int pos = 0, int s = 0):pos(pos), s(s){}
		inline Node Set(int u) {
			Node ret(u, s);
			for (int i = 0; i < (int)go[u].size(); i++) ret.s |= go[u][i];
			return ret;
		}
		inline int match(void) {
			for (int i = 0; i < 8; i += 2) {
				int tmp = (s >> i) & 3;
				if (tmp != 0 && tmp != 3) return 1;
			}
			return 0;
		}
		inline int hash(void) {
			return (pos << 8) + s;
		}
	};

	queue<Node> Q;
	bool _vis[MAXM]; int _dis[MAXM];
	inline bool& vis(Node& now) {return _vis[now.hash()];}
	inline int& dis(Node& now) {return _dis[now.hash()];}

	inline void Work(void) {
		for (int i = 1; i <= n; i++) {
			Node ret = Node(0,0).Set(i);
			dis(ret) = 0;
			vis(ret) = true;
			Q.push(ret);
		}
		int Ans = inf;
		while (!Q.empty()) {
			Node now = Q.front(), next; Q.pop();
			if (now.s + 1 == (1 << 8)) Ans = min(Ans, dis(now));
			int d = now.match();
			for (int i = 1; i <= n; i++) if (c[i][now.pos] != inf) {
				next = now.Set(i);
				if (dis(next) > dis(now) + d * c[i][now.pos]) {
					dis(next) = dis(now) + d * c[i][now.pos];
					if (!vis(next)) {
						vis(next) = true;
						Q.push(next);
					}
				}
			}
			for (int i = 0; i < (1 << 8); i++) if (dis(next = Node(now.pos, i)) != inf) {
				Node tmp = Node(now.pos, now.s | i);
				if (dis(tmp) > dis(next) + dis(now)) {
					dis(tmp) = dis(next) + dis(now);
					if (!vis(tmp)) {
						vis(tmp) = true;
						Q.push(tmp);
					}
				}
			}
			vis(now) = false;
		}
		printf("%d\n", Ans);
	}

	inline void solve(void) {
		while (scanf("%d%d", &n, &m), n || m) {
			memset(_dis, 55, sizeof _dis); inf = _dis[0]; 
			M.clear();for (int i = 1; i <= n; i++) go[i].resize(0);
			for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) if (i != j) c[i][j] = inf;
			Input();
			Work();
		}
	}
}

int main(void) {
	Solve::solve();
	return 0;
}

