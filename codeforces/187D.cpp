#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

const int MAXN = 100010, inf = 2000000000;

inline int ScanInt(void) {
	int c, r = 0, d;
	while (!isdigit(c = getchar()) && c != '-') ;
	if (c != '-') r = c - 48;
	while ( isdigit(d = getchar())) r = r * 10 + d - 48;
	if (c != '-') return r; else return -r;
}

int n, g, r, a[MAXN];

long long f[MAXN], s[MAXN];

inline void Adjust(long long &x) {
	x %= (r + g);
	if (x < 0) x += (r + g);
}

struct Node {
	int l, r; Node *ch[2]; int Min;
}*root, Tnull, *null = &Tnull;

void Insert(Node *&now, int L, int R, int h, int w) {
	if (now == null) {
		now = new Node();
		now->l = L, now->r = R;
		now->ch[0] = now->ch[1] = null;
	}
	if (L == R) {
		now->Min = w;
		return;
	}
	int mid = (L + R) >> 1;
	if (h <= mid) Insert(now->ch[0], L, mid, h, w);
	if (h > mid) Insert(now->ch[1], mid + 1, R, h, w);
	now->Min = min(now->ch[0]->Min, now->ch[1]->Min);
}

int Cal(Node *&now, int L, int R) {
	if (now == null) return null->Min;
	if (L <= now->l && now->r <= R) {
		return now->Min;
	}
	int r1 = inf, r2 = inf;
	int mid = (now->l + now->r) >> 1;
	r1 = Cal(now->ch[0], L, min(mid, R));
	r2 = Cal(now->ch[1], max(mid + 1, L), R);
	return min(r1, r2);
}

inline int get(int d, int t = -1) {
	long long L = g + (t * d) % (r + g), R = L + r - 1; Adjust(L); Adjust(R);
	int ret;
	if (L < R) {
		ret = Cal(root, L, R);
	} else {
		int ret1 = Cal(root, L, r + g - 1);
		int ret2 = Cal(root, 0, R);
		ret = min(ret1, ret2);
	}
	return ret;
}

int main(void) {
	freopen("in", "r", stdin);
	//freopen("out", "w", stdout);
	scanf("%d%d%d", &n, &g, &r); root = null; null->Min = inf;
	for (int i = 1; i <= n + 1; i++) a[i] = ScanInt(), s[i] = s[i - 1] + a[i];
	f[n] = a[n + 1]; Insert(root, 0, r + g - 1, s[n] % (r + g), n);
	for (int i = n - 1; i >= 1; i--) {
		int ret = get(s[i], 1);
		if (ret!= inf) {
			f[i] = f[ret] + s[ret] - s[i] + r + g - (s[ret] - s[i]) % (r + g);
		} else {
			f[i] = s[n + 1] - s[i];
		}
		Insert(root, 0, r + g - 1, s[i] % (r + g), i);
	}
	int q; scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		int t = ScanInt(); int ret = get(t);
		if (ret== inf) {
			printf("%I64d\n", s[n + 1] + t);
		} else {
			printf("%I64d\n", f[ret] + s[ret] + (r + g - (s[ret] + t) % (r + g)) + t);
		}
	}
	return 0;
}

