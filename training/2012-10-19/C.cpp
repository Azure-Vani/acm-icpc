#include <cstdio>
#include <cctype>
#include <algorithm>
#include <map>
#define REP(i,l,r) for(int i = l; i <= r; i++)
using namespace std;

const int MAXN = 1000010;

int n, m, c[MAXN], a[MAXN], log[MAXN];
map<int, int> T;
pair<int, int> f[21][MAXN];

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

inline pair<int, int> Ask(int l, int r) {
	int u = log[r - l + 1];
	return max(f[u][l], f[u][r - (1 << u) + 1]);
}

int main(void) {
	freopen("in", "r", stdin);
	for (int i = 2; i <= 1000000; i++) log[i] = log[i >> 1] + 1;
	while(scanf("%d%d", &n, &m), n || m) {
		T.clear();
		REP(i, 1, n) scanf("%d", a + i);
		for (int i = 1; i <= n; i++) {
			int &t = T[a[i]];
			c[i] = t; t = i; f[0][i] = make_pair(c[i], i);
		}
		for (int j = 1; (1 << j) <= n; j++)
			for (int i = 1; i <= n; i++) if (i + (1 << j) - 1 <= n) {
				f[j][i] = max(f[j - 1][i], f[j - 1][i + (1 << (j - 1))]);
			}
		REP(i, 1, m) {
			int l = ScanInt(), r = ScanInt();
			pair<int, int> ret = Ask(l, r);
			if (ret.first >= l) {
				printf("%d\n", a[ret.second]);
			} else puts("OK");
		}
	}
	return 0;
}

