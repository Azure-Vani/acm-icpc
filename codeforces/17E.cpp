#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXN = 4000010, mod = 51123987, inv_mod = 25561994;

int n, a[MAXN], R[MAXN]; char ch[MAXN];

int f[MAXN], g[MAXN];

inline void Manacher(int a[], int n, int ret[]) {
	int MaxR = -1, where = 0;
	for (int i = 1; i <= n; i++) {
		int &it = ret[i]; it = 0;
		if (i <= MaxR) it = min(ret[where * 2 - i], MaxR - i);
		while (i - it - 1 >= 1 && i + it + 1 <= n && a[i - it - 1] == a[i + it + 1]) it++;
		if (it + i > MaxR) MaxR = it + i, where = i;
	}
}

inline int get(int t) {return (t + 1) >> 1;}
inline void Add(int &a, int b) {a += b; if (a < 0) a += mod; if (a >= mod) a -= mod;}

inline void Gen(int R[], int s[]) {
	for (int i = 1; i <= n; i++) {
		int t = i; if (!(i & 1)) t++;
		int l = t, r = i + R[i]; if (!(r & 1)) r--;
		if (l > r) continue;
		s[get(l)]++, s[get(r) + 1]--;
	}
	for (int i = 1; i <= get(n); i++) Add(s[i], s[i - 1]);
	for (int i = 1; i <= get(n); i++) Add(s[i], s[i - 1]);
	for (int i = 1; i <= get(n); i++) Add(s[i], s[i - 1]);
}

inline int P(int a[], int t) {
	if (t < 0) return 0; else return a[t];
}

inline int gcd(int a, int b) {return !b?a:gcd(b, a % b);}

int main(void) {
//	freopen("in", "r", stdin);
	scanf("%d", &n); scanf("%s", ch);
	for (int i = 1; i <= (n<<1); i++) if (i & 1) a[i] = ch[(i - 1) >> 1] - 'a' + 1; n = n * 2 - 1;
	Manacher(a, n, R);
	Gen(R, f);
	reverse(R + 1, R + n + 1);
	Gen(R, g);
	reverse(g, g + get(n) + 2);
	reverse(R + 1, R + n + 1); f[get(n) + 1] = f[get(n)], g[0] = g[1];
	int ret = 0;
	for (int i = 1; i <= n; i++) {
		int l = i - R[i], r = i + R[i];
		if (!(l & 1)) l++; if (!(r & 1)) r--;
		if (l > r) continue;
		int t = !(i & 1);
		Add(ret, P(f, get(i - t) - 1) - P(f, get(l) - 2));
		Add(ret, P(g, get(i + t) + 1) - P(g, get(r) + 2));
	}
	ret = (long long) ret * inv_mod % mod;
	int tmp = f[get(n)];Add(tmp,  -f[get(n) - 1]); tmp = (long long)tmp * (tmp - 1) % mod * inv_mod % mod;
	Add(tmp, -ret);
	printf("%d\n", tmp);
	return 0;
}

