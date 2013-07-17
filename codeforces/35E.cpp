#include <cstdio>
#include <algorithm>
#include <set>
#include <map>

#define foreach(i, T) for(__typeof(T.begin()) i = T.begin(); i != T.end(); ++i)

using namespace std;

const int MAXN = 200010;
int n, m, Ans = 0;

struct line {
	int h, x, y;
}a[MAXN];

inline bool cmp(const line& x, const line& y) {
	return x.h < y.h;
}
int f[MAXN], L = 0, fim[MAXN], C[MAXN];
map<int, int> M; set<int> S;

inline int get(int x) {return (x == f[x]) ? x : (f[x] = get(f[x]));}
inline void color(int l, int r, int c) {
	while (r = get(r), r >= l) {
		C[r] = c;
		f[r] = get(r-1);
	}
}

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d%d%d", &a[i].h, &a[i].x, &a[i].y), S.insert(a[i].x), S.insert(a[i].y);
	foreach(it,S) M[*it] = ++L, fim[L] = *it;
	for (int i = 1; i <= L; i++) f[i] = i;
	for (int i = 1; i <= n; i++) a[i].x = M[a[i].x], a[i].y = M[a[i].y];
	sort(a + 1, a + n + 1, cmp);
	for (int i = n; i >= 1; i--) color(a[i].x + 1, a[i].y, a[i].h);
	for (int i = 2; i <= L; i++) Ans += (C[i] != C[i - 1]), Ans += (C[i] != C[i + 1]);
	printf("%d\n%d 0\n", Ans + 2, fim[1]);
	for (int i = 2; i <= L; i++) {
		if (C[i] != C[i - 1]) printf("%d %d\n", fim[i - 1], C[i]);
		if (C[i] != C[i + 1]) printf("%d %d\n", fim[i], C[i]);
	}
	printf("%d 0\n", fim[L]);
	return 0;
}

