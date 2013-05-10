#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <iostream>
#include <vector>
#include <queue>
namespace Solve {
	typedef std::map<std::string, int> MII;
	typedef std::vector<int> VII;
	const int MAXS = 8;
	const int MAXN = 31;
	
	int n, m, c[MAXN][MAXN];
	MII fim;
	VII M[MAXN];

	inline void Input(void) {
		memset(c, 60, sizeof c);
		std::string a, b; std::cin >>n>>m;
		for (int i = 1; i <= n; i++) 
			std::cin >> a, fim[a] = i;
		while (m--) {
			int z;
			std::cin >>a>>b>>z;
			int s = fim[a], t = fim[b];
			c[s][t] = c[t][s] = std::min(c[s][t], z);
		}
		for (int i = 0; i < 8; i++) {
			std::cin >>a;
			M[fim[a]].push_back(i);
		}
	}

	class Status {public:
		int ID, now;
		Status(){}
		Status(int ID, int now):ID(ID), now(now){}
		inline Status Move(int go) {
			Status ret; ret.now = now;
			for (int i = 0; i < M[go].size(); i++)
				ret.now |= (1 << M[go][i]);
			ret.ID = go;
			return ret;
		}
		inline bool OK(void) {
			return now + 1 == (1 << 8);
		}
		inline int hash(void) const {
			return (ID << 8) + now;
		}
		inline bool match(void) {
			for (int i = 0; i < 8; i += 2) {
				int t = (now >> i) & 3;
				if (t != 0 && t != 3) return false;
			}
			return  true;
		}
	};
	
	std::queue<Status> Q;
	
	int dis[MAXN << 8], inf, Ans;
	bool vis[MAXN << 8];
	inline int& Dis(const Status& a) {return dis[a.hash()];}
	inline bool& Vis(const Status& a) {return vis[a.hash()];}

	inline void Work(void) {
		memset(dis, 60, sizeof dis); Ans = inf = dis[0];
		for (int i = 1; i <= n; i++) {
			Status now = Status(0,0).Move(i);
			Vis(now) = true;
			Dis(now) = 0;
			Q.push(now);
		}
		while (!Q.empty()) {
			Status now = Q.front(); Q.pop();
			int lab = now.ID, d = Dis(now);
			if (now.OK()) 
				Ans = std::min(Ans, d);
			bool free = now.match();
			for (int i = 1; i <= n; i++) if (c[lab][i] != inf) {
				int w = free?0:c[lab][i];
				Status next = now.Move(i);
				if (Dis(next) > d + w) {
					Dis(next) = d + w;
					if (!Vis(next)) {
						Q.push(next);
						Vis(next) = true;
					}
				}
			}
			Status tmp;
			for (int i = 0; i < (1 << 8); i++) if (Dis(tmp = Status(lab, i)) != inf) {
				Status next(lab, now.now | i);
				if (Dis(next) > d + Dis(tmp)) {
					Dis(next) = d + Dis(tmp);
					if (!Vis(next)) {
						Q.push(next);
						Vis(next) = true;
					}
				}
			}
			Vis(now) = false;
		}
		std::cout <<Ans<<std::endl;
	}

	inline void solve(void) {
		Input();
		Work();
	}
}
int main(int argc, char** argv) {
	Solve::solve();
	return 0;
}
