#ifdef unix
#define LL "%lld"
#else
#define LL "%I64d"
#endif
#include <cstdio>
#include <algorithm>
#define rep(i,n) for(int i = 1; i <= (n); i++)
const int MAXN = 200010;
typedef long long Int64;
Int64 s[MAXN]; int n, m;
int main(void) {
//  freopen("in", "r", stdin);
    scanf("%d%d", &n, &m);
    rep(i,n) scanf(LL,s + i), s[i] <<= 1;
    rep(j,m) {
        register Int64 x, y, c;
        scanf(LL LL LL, &x, &y, &c);
        s[x] += c; s[y] += c;
    }
    std::sort(s + 1, s + n + 1);
    std::reverse(s + 1, s + n + 1);
    Int64 A1 = 0, A2 = 0;
    rep(i,n) if (i&1) A1 += s[i]; else A2 += s[i];
    printf(LL "\n", (A1 - A2) >> 1);
    return 0;
}