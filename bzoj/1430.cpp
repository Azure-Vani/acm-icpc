#include <cstdio>
typedef long long ll;
ll n;
const int MOD = 9999991;
int Pow(ll a, ll n) {
	ll r = 1;
	while (n) {
		if (n & 1) r = (r * a) % MOD;
		a = (a * a) % MOD;
		n >>= 1;
	}
	return r;
}
int main(int argc, char** argv) {
	scanf("%lld", &n);
	ll l1 = 1;
	for (ll i = 2; i < n; i++)
		l1 = (l1 * i) % MOD;
	l1 = (Pow(n, n - 2) * l1) % MOD;
	printf("%lld\n", l1);
	return 0;
}
