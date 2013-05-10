#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cctype>
#include <queue>

#define REP(i,l,r) for(int i = l; i <= r; i++)
#define mp make_pair

using namespace std;

const int MAXN = 1010;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

struct Edge {
	int y, z; Edge *next; bool flag;
	Edge(int y, int z, Edge *next, bool flag = false):y(y), z(z), next(next), flag(flag){}
}*a[MAXN];

int n, m, dis[MAXN], s, t, k, cnt[MAXN];
priority_queue<pair<int, int> > Q;

int main(void) {
	freopen("in", "r", stdin);
	n = ScanInt(), m = ScanInt();
	REP(i,1,m) {
		int x = ScanInt(), y = ScanInt(), z = ScanInt();
		a[x] = new Edge(y, z, a[x], true);
		a[y] = new Edge(x, z, a[y]);
	}
	s = ScanInt(), t = ScanInt(), k = ScanInt(); if (s == t) ++k;
	memset(dis, 55, sizeof dis); dis[t] = 0; Q.push(mp(0, t));
	REP(i,1,n-1) {
		while (!Q.empty() && dis[Q.top().second] < -Q.top().first) Q.pop();
		if (Q.empty()) break; int now = Q.top().second; dis[now] = -Q.top().first; Q.pop();
		for (Edge *p = a[now]; p; p = p->next) if (!p->flag && dis[p->y] > dis[now] + p->z)
			Q.push(mp(-(dis[p->y] = dis[now] + p->z), p->y));
	}
	while (!Q.empty()) Q.pop(); Q.push(mp(-dis[s], s));
	while (!Q.empty()) {
		pair<int, int> now = Q.top(); Q.pop();
		if (++cnt[now.second] > k) continue;
		if (cnt[t] == k) {
			printf("%d\n", -now.first);
			return 0;
		}
		for (Edge *p = a[now.second]; p; p = p->next) if (p->flag)
			Q.push(mp(now.first - p->z + dis[now.second] - dis[p->y], p->y));
	}
	puts("-1");
	return 0;
}

