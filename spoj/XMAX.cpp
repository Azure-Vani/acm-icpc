#include <algorithm>
#include <cstdio>

#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif

typedef long long Int64;
const int MAXN = 100010;

Int64 a[MAXN], gss[65]; int n;

int main(void) {
	freopen("in", "r", stdin);
	scanf("%d", &n); for (int i = 1; i <= n; i++) scanf(LL, a + i);
	Int64 Ans = 0;
	for (int i = 1; i <= n; i++)
		for (int j = 62; j >= 0; --j)
			if (a[i] & (1ll << j)){
				if (!gss[j]) {gss[j] = a[i]; break;} else a[i] ^= gss[j];
			}
	for (int i = 62; i >= 0; i--) if (!(Ans & (1ll << i))) Ans ^= gss[i];
	printf(LL "\n", Ans);
	return 0;
}
