#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <map>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define REP(i,l,r) for(int i = l; i <= r; i++)

#pragma GCC optimize("O3")

using namespace std;

namespace Solve {
	const int MAXN = 100010;
	const int MAXV = 8008;
	const int MAXC = 105;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	typedef pair<int, int> PII;
	typedef vector<pair<int, PII> > VP;
	typedef vector<int> VII;
	PII E[MAXN];
	
	int n, m, c, t; VII own[MAXV][MAXC];
	map<PII, PII> M;


	inline void Erase(vector<int> &T, int x) {
		vector<int>::iterator it = find(T.begin(), T.end(), x);
		T.erase(it);
	}

	inline void Input(void) {
		REP(i, 1, m) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt(); if (x > y) swap(x, y);
			own[x][z].pb(i); own[y][z].pb(i);
			E[i].first = x, E[i].second = y;
			M[mp(x, y)] = mp(i, z);
		}
	}

	inline void Work(void) {
		REP(i, 1, t) {
			int x = ScanInt(), y = ScanInt(), k = ScanInt(); if (x > y) swap(x, y);
			if (!M.count(mp(x, y))) {
				puts("No such cable.");
			} else {
				PII &tmp = M[mp(x, y)];
				if (tmp.second == k) puts("Already owned."); else {
					if (own[x][k].size() >= 2 || own[y][k].size() >= 2) puts("Forbidden: monopoly."); else {
						int t = y, pos; bool OK = true;
						if (own[y][k].size() && own[x][k].size()) {
							while (true) {
								if (t == x) {OK = false; break;}
								if (t == y) {
									pos = own[y][k][0];
									t = E[pos].first + E[pos].second - t;
								} else {
									if (own[t][k].size() == 1) break;
									pos = own[t][k][0] + own[t][k][1] - pos;
									t = E[pos].first + E[pos].second - t;
								}
							}
						}
						if (!OK) {
							puts("Forbidden: redundant.");
						} else {
							puts("Sold.");
							own[x][k].pb(tmp.first); own[y][k].pb(tmp.first);
							Erase(own[x][tmp.second], tmp.first); Erase(own[y][tmp.second], tmp.first);
							tmp.second = k;
						}
					}
				}
			}
		}
	}

	inline void clear(void) {
		REP(i, 1, n) REP(j, 1, c) own[i][j].clear();
		M.clear();
	}

	inline void solve(void) {
		while (scanf("%d%d%d%d", &n, &m, &c, &t), n||m||c||t) {
			clear();
			Input();
			Work();
		}
	}
}

int main(void) {
	#ifdef FILEIO
//		freopen(INPUT, "r", stdin);
	//	freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}

