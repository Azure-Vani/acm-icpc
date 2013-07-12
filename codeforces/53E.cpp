#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <map>

using namespace std;

const int MAXN = 10;

#pragma GCC optimize("O2")

struct State {
    int num, s;
    State():num(0), s(0){}
    inline int Count(void) const {
        return __builtin_popcount((unsigned int)s);
    }
    inline bool use(int t) {return num & (1 << t);}
    inline bool operator <(const State& oth) const {
        if (num != oth.num) return num < oth.num; else return s < oth.s;
    }
}null;

typedef State PII;

map<State, long long> hash;

queue<PII> Q;

int a[MAXN][MAXN], n, m, k;

inline void Add(long long &ret, long long x) {
    ret += x;
}

int main(void) {
    freopen("in", "r", stdin);
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; i++) {
        int x, y; scanf("%d%d", &x, &y); x--, y--;
        a[x][y] = a[y][x] = 1;
    }

    State begin;
    begin.num = 1; begin.s = 1; Q.push(begin); hash[begin] = 1;
    long long Ans = 0;

    while (!Q.empty()) {
	   State now = Q.front(); long long cnt = hash[now];
	   if (now.Count() == k && now.num == (1 << n) - 1) 
		   Add(Ans, cnt);
	   for (int i = 0; i < n; i++) {
		   for (int j = 0; j < n; j++) if (a[i][j] && i != j && now.use(i) && !now.use(j)) {
				State next = now;
				next.num |= 1 << j;
				next.s |= 1 << j;
				if (now.num != 1) next.s &= ~(1 << i);
				if (next.s & (~((1 << (j + 1)) - 1))) continue;
				if (!hash.count(next)) Q.push(next);
				hash[next] += cnt;
		   }
	   }
	   Q.pop();
    }
    cout <<Ans<<endl;
    return 0;
}

