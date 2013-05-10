#include <cstdio>
#include <cctype>
#include <cmath>
#include <cstring>
namespace Solve {
	typedef long long ll;
	const ll MAXN = 100050;
	inline ll Read(void) {
		ll r = 0; int c;
		while (c = getchar(), !isdigit(c)) {}
		r = c - '0';
		while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
		return r;
	}
	ll n, t;
	bool a[MAXN] = {0}, b[MAXN] = {0};
	inline void Input(void) {
		n = Read(), t = Read();
		for (ll i = 0; i < n; i++) a[i] = Read() - 1;
	}
	void Work(void) {
		Input();
		ll flag = t & 1, delta = t >> 1, P = (t / n  + 1 )* n;
		while (t) {
			ll u = 1ll << long(log(t) / log(2));
			memcpy(b, a, sizeof(bool) * n);
			for (ll i = 0; i < n; i++) a[i] ^= b[(i + u) % n];
			t -= u;
		}
		for (ll i = 0; i < (n << 1); i++, putchar(' '))
			if ((i & 1) ^ flag) putchar('0');
			else putchar(a[((i>>1) - delta + P) % n]?'2':'1');
	}
}
int main(int argc, char** argv) {
	#ifdef Debug
		freopen("1.in", "r", stdin);
		freopen("1.out", "w", stdout);
	#endif
	Solve::Work();
	return 0;
}
