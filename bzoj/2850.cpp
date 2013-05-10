#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cmath>
#include <vector>

#define X first
#define Y second
#define rep(i,n) for(int i = 1; i <= n; i++)
#define REP(i,l,r) for(int i = l; i <= r; i++)
#define foreach(i, t) for(__typeof(t.begin()) i = t.begin(); i != t.end(); ++i)
#define mp make_pair

using namespace std;

const int MAXN = 50010;
const int inf = ~0U>>1;

inline int ScanInt(void) {
	int r = 0, c, d;
	while (!isdigit(c = getchar()) && c != '-');
	if (c != '-') r = c - '0'; d = c;
	while ( isdigit(c = getchar())) r = r * 10 + c - '0';
	return d=='-'?-r:r;
}

struct Point {
	int x, y, h;
}a[MAXN];
struct Line {
	int x, y, z, pos;
}b[MAXN];

int n, m, c, pos[MAXN];
vector<pair<long double, pair<int, int> > > B;
vector<pair<long double, int> > V;
long double _x, _y;

const int eps = 1e-8;
inline bool cmp(const Point& a, const Point& b) {
	long double x1 = a.x - _x, y1 = a.y - _y, x2 = b.x - _x, y2 = b.y - _y;
	return x1*y2-x2*y1<-eps;
}

inline bool check(const Point& a, const Line& b) {
	return (long long)a.x * b.x + (long long)a.y * b.y < b.z;
}

inline bool comp_low(const Point& a, const pair<long double, int>& B) {
	int pos = B.Y; long double dx, dy; if (b[pos].y == 0) dx = 0, dy = 1; else dx = 100, dy = (b[pos].z - (B.X + dx) * b[pos].x) / b[pos].y;
	return (a.x - B.X) * dy - (a.y - c) * dx < -eps;
}
inline bool comp_upp(const pair<long double, int>& B, const Point& a) {
	int pos = B.Y; long double dx, dy; if (b[pos].y == 0) dx = 0, dy = 1; else dx = 100, dy = (b[pos].z - (B.X + dx) * b[pos].x) / b[pos].y;
	return (a.x - B.X) * dy - (a.y - c) * dx > eps;
}

long long sum[MAXN], Ans[MAXN];

inline void solve(int l, int r) {
	c = inf; long double t = ~0ULL>>1, tmp; V.resize(0); int N = r - l + 1;
	REP(i,l,r) c = min(c, a[i].y), pos[i] = i; c -= 10000;
	for (int i = l; i <= r; i++)
		for (int j = i + 1; j <= r; j++) {
			long double x = (long double)((long long)(a[i].y - c) * a[j].x - (long long)(a[j].y - c) * a[i].x) / (a[i].y - a[j].y);
			B.push_back(mp(x, mp(i,j)));
			t = min(t, x);
		}
	rep(i,m) {tmp = (long double)(b[i].z - (long long)b[i].y * c) / b[i].x; t = min(t, tmp); V.push_back(mp(tmp, i));}
	sort(B.begin(), B.end());
	sort(V.begin(), V.end());
	_x = t, _y = c;
	sort(a + l, a + r + 1, cmp); sum[l - 1] = 0;
	REP(i, l, r) sum[i] = sum[i - 1] + a[i].h;
	int p = 0, q = 0;
	while (p < (int)B.size() || q < (int)V.size()) {
		if (p < (int)B.size() && (q == (int)V.size() || B[p].X < V[q].X)) {
			swap(a[pos[B[p].Y.X]], a[pos[B[p].Y.Y]]);
			swap(pos[B[p].Y.X], pos[B[p].Y.Y]);
			p++;
		} else {
			int _l = lower_bound(a + l, a + l + N, V[q], comp_low) - a, _r = upper_bound(a + l, a + l + N, V[q], comp_upp) - a - 1;
			long long L = sum[_l - 1], M = sum[_r] -  sum[_l - 1], R = sum[r] - L - M, vl = l, vr = r;
			if (L == 0) swap(L, R), swap(vl, vr);
			if (check(a[vl], b[V[q].Y])) Ans[b[V[q].Y].pos] += L; else Ans[V[q].Y] += R;
			q++;
		}
	}
}

int main(void) {
	freopen("in", "r", stdin);
	n = ScanInt(); m = ScanInt();
	rep(i,n) a[i].x = ScanInt(), a[i].y = ScanInt(), a[i].h = ScanInt();
	rep(i,m) b[i].x = ScanInt(), b[i].y = ScanInt(), b[i].z = ScanInt(), b[i].pos = i;
	int T = (int)sqrt(n);
	for (int i = 1; i <= n; i += T) {
		solve(i, min(i + T - 1, n));
	}
	rep(i,m) printf("%lld\n", Ans[i]);
	return 0;
}

