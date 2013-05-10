#define FILEIO

#define INPUT "in"
#define OUTPUT "out"

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <set>
#include <map>

#define mp make_pair
#define pb push_back
#define foreach(i,T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

namespace Solve {
	const int MAXN = 200010;
	const int MAXM = 1000010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}

	typedef pair<int, int> PII;
	map<PII, int> M;
	
	struct Pair{
		int type, x, y, z;
	}Q[MAXN], E[MAXM];

	inline bool cmp(const Pair& x, const Pair& y) {
		return x->z < y->z;
	}
	int f[MAXN];
	int get(int x) {return f[x] == x ? x : f[x] = get(f[x]);}

	inline void cut(int x, int y) {
		Evert(x); Access(y); fim[y]->p = fim[x]->ch[1] = null;
	}

	inline void link(int x, int y, bool check = false) {
		Evert(x); Evert(y);
		fim[y]->p = fim[x];
	}

	inline Node* getPath(int x, int y) {
		Evert(fim[x]); Access(fim[y]);
		return fim[y];
	}

	inline void solve(void) {
		int n = ScanInt(), m = ScanInt(), q = ScanInt(), N = n;
		rep(i,m) {
			int x = ScanInt(), y = ScanInt(), z = ScanInt();
			if (x > y) swap(x, y);
			M[mp(x,y)] = z;
		}
		rep(i,q) {
			int k = ScanInt(), x = ScanInt(), y = ScanInt();
			if (x > y) swap(x, y);
			Q[i].type = k; Q[i].x = x, Q[i].y = y;
			if (k == 2) {
				Q[i].z = M[mp(x,y)];
				M.erase(mp(x, y));
			}
		}
		int cnt = 0;
		foreach(it, M) E[++cnt].x = it->first.first, E[cnt].y = it->first.second, E[cnt].z = it->second;
		sort(E + 1, E + cnt + 1, cmp);
		rep(i,n) f[i] = i;
		rep(i,cnt) {
			int x = E[i].x, y = E[i].y;
			if (get(x) == get(y)) continue;
			f[x] = y;
			if (!fim[x]) fim[x] = new Node;
			if (!fim[y]) fim[y] = new Node;
			fim[++N] = new Node(E[i].z);
			Evert(fim[x]); Evert(fim[y]); fim[x]->p = fim[y]->p = fim[N];
		}
		for (int i = q; i >= 1; i--) {
			Evert(fim[Q[i].x]);
			Access(fim[Q[i].y]);
			if (Q[i].type == 1) {
				printf("%d\n", fim[Q[i].y]->Max);
			}else
			if (Q[i].type == 2) {
				Node* u = fim[Q[i].y]->wMax;
				if (u->v < Q[i].z) {
				}
			}
		}
	}
}

int main(void) {
	#ifdef FILEIO
		freopen(INPUT, "r", stdin);
		freopen(OUTPUT, "w", stdout);
	#endif
	Solve::solve();
	return 0;
}
