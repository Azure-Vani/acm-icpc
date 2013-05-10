#include <cstdio>
#include <cassert>
#include <iostream>
#include <cmath>
#include <algorithm>
#define rep(i,n) for(int i = 1; i <= n; i++)
#define lg2(n) ((int)((log((double)(n)) / log(2.0)) + 0.5))
using namespace std;

int k, a[1000002], L, n = 0, lg = 62, begin;

typedef long long Int64;
Int64 b = 1ll << lg, *c;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

inline void go(int now) {
	while (now <= L || c[now] >= b) c[now + 1] += (c[now] >> lg), c[now] &= b - 1, now++;
	if (now > L) L = now;
}

inline void go_rev(int now) {
	while (c[now] < 0) c[now] += b, c[now + 1]--, now++;
	while (c[L] == 0 && L > 0) L--;
}

inline void get(int t, int s, int f) {
	if (t < 1000002) { if (f) a[t] += s; else a[t] = s;}
	else { if (f) c[t - 1000002] += s; else c[t - 1000002] = s;}
}

inline void get(int t) {
	if (t < 1000002) 	printf("%d", a[t]); else printf("%lld", c[t - 1000002]);
}

int main(void) {
	freopen("in", "r", stdin);
	freopen("out", "w", stdout);
	scanf("%d", &k); rep(i,k) a[i] = ScanInt(), n += a[i]; L = n / lg + (bool)n%lg; begin = a[1];
	c = new Int64[L + 10];
	if (k == 1 && a[1] == 1) {puts("1\n1"); return 0;}
	int t = k, v = k&1;
	rep(i,L) {
		int res = lg, s = 0; Int64 last = 0;
		while (res && t) {
			int cut = min(res, a[t]);
			if (v) last += ((1ll << cut) - 1) << s;
			a[t] -= cut; res -= cut; s += cut;
			if (!a[t]) t--, v ^= 1;
		}
		c[i] = last;
	}
	c[1] += k; go(1); // n + k
	rep(i,L) c[i - 1] |= (!(c[i] & 1) ? 0 : b >> 1), c[i] >>= 1; // (n + k) div 2
	if (begin == 1) {
		unsigned long long last = 0;
		rep(i,L) {
			unsigned long long t = (unsigned long long) c[i] * 3;
			c[i] = (t + last) & (b - 1); // (n + k) * (3 / 2)
			last = t >> lg;
		}
		if (last) c[++L] = last;
		c[1] -= k - 1; go_rev(1); // (n + k) * (3 / 2) - k + 1
		int w = (n - 2) / lg + 1, p = (n - 2) % lg;
		c[w] -= 1ll << p; go_rev(w); // (n + k) * (3 / 2) - k + 1 - 2 ^ (t - 2)
	} else {
		int w = (n - 1) / lg + 1, p = (n - 1) % lg;
		c[w] += 1ll << p; go(w); // (n + k) div 2 + 2 ^ (t - 1)
	}
	c[1] -= n; go_rev(1); // -t
	int top = 0, last = -1;
	rep(i, L) {
		int t = 0, w, s;
		while (c[i]) {
			w = c[i] & 1;
			if (w) s = lg2(((c[i] ^ (c[i] + 1)) >> 1) + 1);
			else s = lg2(((c[i] ^ (c[i] - 1)) >> 1) + 1);
			if (w == last) get(top, s, 1); else get(++top, s, 0); last = -1;
			t += s;
			c[i] >>= s;
		}
		if (t == lg || i == L) last = 1; else {
			if (last == 0) get(top, lg - t, 1);
			else last = 0, get(++top, lg - t, 0);
		}
	}
	printf("%d\n", top);
	for (int i = top; i > 1; i--)  get(i), putchar(' '); printf("%d\n", a[1]);
	return 0;
}
