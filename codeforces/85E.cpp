#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

#pragma GCC optimize("O2")

const int MAXN = 5001, mod = 1000000007;

struct Point {
	int x, y;
	inline int operator -(const Point& oth) const {
		return abs(x - oth.x) + abs(y - oth.y);
	}
}a[5010];

int n;
vector<pair<int, int> > stack[10001];

int f[MAXN], d[MAXN];

inline int get(int x) {
	if (x == f[x]) return x;
	else {
		int ret = get(f[x]);
		d[x] ^= d[f[x]];
		return f[x] = ret;
	}
}

int cur = n;

inline bool Add(int x, int y) {
	int X = get(x), Y = get(y);
	if (X != Y) {
		cur--;
		f[X] = y; d[X] = d[x] ^ 1;
		return true;
	} else {
		return (d[x] ^ d[y]) == 1;
	}
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d", &n); for (int i = 1; i <= n; i++) scanf("%d%d", &a[i].x, &a[i].y), f[i] = i;
	for (int i = 1; i <= n; i++)
		for (int j = i + 1; j <= n; j++) stack[a[i] - a[j]].push_back(make_pair(i, j));
	int l = 0, t = 1; cur = n;
	for (int i = 10000; i >= 1; i--) {
		bool flag = true;
		for (register vector<pair<int, int> >::iterator it = stack[i].begin(); flag && it != stack[i].end(); ++it) {
			flag &= Add(it->first, it->second);
		}
		if (!flag) {l = i;break;}
		t = cur;
	}
	int ret = 1;
	for (int i = 1; i <= t; i++) {
		ret = (long long) ret * 2ll % mod;
	}
	printf("%d\n%d\n", l, ret);
	return 0;
}

