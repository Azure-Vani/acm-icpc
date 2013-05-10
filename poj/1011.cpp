#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#include <set>
#define REP(i,l,r) for(int i = l; i <= r; i++)

using namespace std;

const int MAXN = 69;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

int n, a[MAXN], s[MAXN], f[66 * 55], L, next[MAXN], prev[MAXN];
set<pair<unsigned long long, int> > T;

#pragma GCC optimize ("O3") //evil >_<

inline bool Dfs(int pos, int res, unsigned long long S) {
	if (pos == n + 1) {
		return res == L;
	}
	if (T.count(make_pair(S, res))) return false;
	T.insert(make_pair(S, res));
	bool ret = false; int last = -1;
	for (int i = next[0]; !ret && i <= n && a[i] <= res; i = next[i]) if (a[i] != last) {
		last = a[i];
		next[prev[i]] = next[i]; prev[next[i]] = prev[i];
		ret = Dfs(pos + 1, (res - a[i] == 0 ? L : res - a[i]), S | (1ull << (i - 1)));
		next[prev[i]] = i; prev[next[i]] = i;
	}
	return ret;
}

int main(void) {
	freopen("in", "r", stdin);
	while (scanf("%d", &n), n) {
		memset(f, 0, sizeof f); memset(next, 0, sizeof next); memset(prev, 0, sizeof prev);
		REP(i, 1, n) a[i] = ScanInt(); sort(a + 1, a + n + 1); reverse(a + 1, a + n + 1);
		REP(i, 1, n) s[i] = s[i - 1] + a[i];
		f[0] = true; REP(i, 1, n) for (int j = s[n]; j >= a[i]; j--) f[j] |= f[j - a[i]];
		REP(i, 1, n) next[i] = i + 1, prev[i] = i - 1; next[0] = 1;
		REP(i, 1, s[n]) if (f[i] && s[n] % i == 0) {
			L = i;
			T.clear();
			if (Dfs(1, L, 0)) {printf("%d\n", i); break; }
		}
	}
	return 0;
}

