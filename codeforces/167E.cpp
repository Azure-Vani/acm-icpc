#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>

#define foreach(it, T) for(__typeof(T.begin()) it = T.begin(); it != T.end(); ++it)

using namespace std;

const int MAXN = 603;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

int n, m, mod;

int f[MAXN][MAXN], inp[MAXN], oup[MAXN], a[MAXN][MAXN];
vector<int> E[MAXN];

inline int Inv(int k) {
	int ret = 1, tmp = mod - 2;
	while (tmp) {
		if (tmp & 1) ret = (long long) ret * k % mod;
		k = (long long) k * k % mod;
		tmp >>= 1;
	}
	return ret;
}

inline void Add(int &x, int y) {
	x += y; if (x >= mod) x -= mod;
}

inline int det(void) {
	int d = 1;
	for (int i = 1; i <= n; i++) {
		int t = 0;
		for (int j = i; j <= n; j++) if (a[j][i] != 0) {t = j; break;}
		if (!t) continue;
		if (t != i) {
			for (int j = 1; j <= n; j++) swap(a[i][j], a[t][j]);
			d *= -1;
		}
		for (int j = i + 1; j <= n; j++) if (a[j][i]) {
			int g = (long long) (mod - a[j][i]) * Inv(a[i][i]) % mod;
			for (int k = i; k <= n; k++) {
				Add(a[j][k], (long long) g * a[i][k] % mod);
			}
		}
	}
	int ret = 1;
	for (int i = 1; i <= n; i++) ret = (long long) ret * a[i][i] % mod;
	if (d == -1 && ret) ret = mod - ret;
	return ret;
}

int d[MAXN], in[MAXN], out[MAXN];

int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d%d%d", &n, &m, &mod);
	while (m--) {
		int x = ScanInt(), y = ScanInt();
		inp[y]++, oup[x]++; E[x].push_back(y);
	}
	int t1 = 0, t2 = 0, head = 1, tail = 0;
	for (int i = 1; i <= n; i++) {
		f[i][i]++;
		if (inp[i] == 0) in[i] = ++t1, d[++tail] = i, inp[i] = -1;
		if (oup[i] == 0) out[i] = ++t2;
	}
	while (head <= tail) {
		int now = d[head++];
		foreach(it, E[now]) {
			if (!--inp[*it]) d[++tail] = *it, inp[*it] = -1;
			for (int i = 1; i <= n; i++) Add(f[i][*it], (long long)f[i][now] % mod);
		}
	}
	for (int i = 1; i <= n; i++) 
		for (int j = 1; j <= n; j++) if (in[i] && out[j])
			a[in[i]][out[j]] = f[i][j];
	n = t1;
	printf("%d\n", det());
	return 0;
}

