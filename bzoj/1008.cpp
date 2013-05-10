#define LL "%lld"
#include <cstdio>
const long MOD = 100003;
typedef long long ll;
ll n, m;
ll Pow(ll a, ll n) {
        ll r = 1;
        while (n) {
                if (n&1) r = (r * a) % MOD;
                a = (a * a) % MOD;
                n >>= 1;
        }
        return r;
}
int main(int argc, char** argv) {
        scanf(LL LL, &m, &n);
        ll A = (Pow(m, n) - (Pow(m - 1, n - 1) * m) % MOD);
        printf(LL "\n", A < 0 ? A + MOD : A % MOD);
        return 0;
}