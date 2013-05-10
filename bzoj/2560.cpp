//#define FILEIO
#define INPUT "in"
#define OUTPUT "out"
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
#include <cassert>
#define rep(i,l,r) for(register int i = (l); i <= (r); i++)
#define In(a, b, c) (((a) >= (b)) && ((a) <= (c)))
namespace Solve {
    const int MAXN = 16;
    const int MAXM = (1 << 16);
    const int Mod = 1000000007;
    inline int ScanInt(void) {
        int c, r = 0, d;
        while (!isdigit(c = getchar()) && c != '-');
        if (c != '-') r = c - '0';
        while ( isdigit(d = getchar())) r = r * 10 + d - '0';
        return c=='-'?-r:r;
    }
    inline void Add(int &a, int b) {
        a += b;
        while (a >= Mod) a -= Mod;
        while (a < 0) a += Mod;
    }
    int n, c[MAXN][MAXN], f[MAXM], sum[MAXM], ms;
    bool vis[MAXM];
    
    inline int Dfs(int S) {
        if (vis[S]) return f[S];
        vis[S] = true;
        if (S == 0 || (S & (S - 1)) == 0) return f[S] = 1;
        register int low = S&-S, &ret = f[S]; ret = sum[S], S ^= low;
        for (register int i = (S-1)&S; ; (--i)&=S) {
            register int tmp = Dfs(low | i);
            Add(ret, -(long long) tmp * sum[S^i] % Mod);
            if (!i) break;
        }
        return ret;
    }
    void solve(void) {
        n = ScanInt(), ms = (1 << n) - 1;
        rep(i,0,n-1) rep(j,0,n-1) c[i][j] = ScanInt();
        rep(k,0, ms) {
            sum[k] = 1;
            rep(i,0,n-1) if (k & (1 << i)) rep(j,i+1,n-1) if ((k & (1 << j))) sum[k] = (long long) sum[k] * (long long)(c[i][j] + 1) % Mod;
        }
        printf("%d\n",Dfs(ms));
    }
}
int main(int argc, char* argv[]) {
    #ifdef FILEIO
        freopen(INPUT, "r", stdin);
//      freopen(OUTPUT, "w", stdout);
    #endif
    Solve::solve();
    return 0;
}