#include <cstdio>
#include <cstring>
#include <vector>
#include <cctype>
#include <algorithm>
#include <set>
#include <map>
#define REP(i,l,r) for(int i = 1; i <= r;i++)

using namespace std;

namespace Solve {
	typedef long long Int64;
	const int MAXN = 250010;

	inline int ScanInt(void) {
		int r = 0, c, d;
		while (!isdigit(c = getchar()) && c != '-');
		if (c != '-') r = c - '0'; d = c;
		while ( isdigit(c = getchar())) r = r * 10 + c - '0';
		return d=='-'?-r:r;
	}
	inline int Get(void) {
		int c; while (!isupper(c = getchar())); return c;
	}

	int n, m, a[MAXN], c[MAXN], Len = 0, L[MAXN], b[MAXN], d[MAXN];

	struct Query {
		int type, l, r;
	}Q[MAXN];

	map<int, int> M; set<int> S; long long fim[MAXN];
	
	//0: Modify 1: Query
	inline void Input(void) {
		n = ScanInt();
		REP(i, 1, n) d[i] = c[i] = ScanInt(), S.insert(c[i]);
		m = ScanInt();
		REP(i, 1, m) {Q[i].type = (Get() == 'Q'), Q[i].l = ScanInt(), Q[i].r = ScanInt(); if (Q[i].type == 0) S.insert(Q[i].r);}
		for (set<int>::iterator it = S.begin(); it != S.end(); ++it) M[*it] = ++Len, fim[Len] = *it;
		REP(i, 1, n) b[i] = a[i] = M[c[i]]; REP(i, 1, m) if (Q[i].type == 0) Q[i].r = M[Q[i].r];
	}

	template<class T> inline T next(T it) {return ++it;}
	template<class T> inline T prev(T it) {return --it;}

	int vis[MAXN];
	set<int> V[MAXN];
	vector<int> C[MAXN];
	vector<long long> D[MAXN];
	int size[MAXN];

	inline void Init(void) {
		memset(vis, 0, sizeof vis);
		REP(i, 1, Len) V[i].clear(), V[i].insert(0), V[i].insert(n + 1);
		REP(i, 1, n) a[i] = b[i], c[i] = d[i];;
		REP(i, 1, n) L[i] = vis[a[i]], vis[a[i]] = i, V[a[i]].insert(i);
	}

	inline void Modify(int pos, int value) {
		for (;pos <= n; pos += pos & -pos) C[pos].push_back(value), D[pos].push_back(0);
	}

	inline void Add(int pos, int t, long long d, int flag) {
		if (pos == 0) return;
		if (flag == 0) {
			Modify(pos, t);
			return;
		}
		for (int i = pos; i <= n; i += i & -i) {
			int p = lower_bound(C[i].begin(), C[i].end(), t) - C[i].begin();
			for (int j = p + 1; j <= (int)C[i].size(); j += j & -j)
				D[i][j - 1] += d;
		}
	}

	inline long long Ask(int pos, int t) {
		long long ret = 0;
		for (int i = pos; i > 0; i -= i & -i) {
			int p = lower_bound(C[i].begin(), C[i].end(), t) - C[i].begin(); p--;
			for (int j = p + 1; j > 0; j -= j & -j)
				ret += D[i][j - 1];
		}
		return ret;
	}

	inline long long Cal(int l, int r) {
		long long Sr = Ask(r, l);
		long long Sl = Ask(l - 1, l);
		return Sr - Sl;
	}

	inline void Work(int _ = 0) {
		REP(i, 1, m) {
			int type = Q[i].type;
			if (type == 0) {
				int pos = Q[i].l, value = Q[i].r;

				//----a---a
				//....N...^
				set<int>::iterator it = V[a[pos]].find(pos);

				Add(*next(it), L[*next(it)], -c[*next(it)] , _);
				Add(*next(it), L[pos], c[*next(it)] , _);
				L[*next(it)] = L[pos];

				V[a[pos]].erase(pos);

				a[pos] = value;
				it = V[value].lower_bound(pos);
				int tmp = *prev(it);
				V[value].insert(pos);

				Add(*it, L[*it], -c[*it] , _);
				Add(*it, pos, c[*it] , _);
				L[*it] = pos;

				Add(pos, L[pos], -c[pos] , _);
				L[pos] = tmp;
				Add(pos, tmp, fim[value] , _);

				c[pos] = fim[value];
			}else if (_ == 1) {
				long long Ans = Cal(Q[i].l, Q[i].r);
				printf("%lld\n", Ans);
			}
		}
	}

	inline void solve(void) {
		Input();
		Init();
		Work(0);
		Init();
		REP(i, 1, n) {
			Modify(i, L[i]);
			sort(C[i].begin(), C[i].end());
			C[i].erase(unique(C[i].begin(), C[i].end()), C[i].end());
			D[i].resize(C[i].size());

		}		
		REP(i, 1, n) {
			Add(i, L[i], c[i], 1);
		}
		Work(1);
	}
}

int main(void) {
	freopen("in", "r", stdin);
	Solve::solve();
	return 0;
}

