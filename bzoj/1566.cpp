#include <cstdio>
#include <cstring>
const long MAXN = 502;
const long MOD = 1024523;
long f[2][MAXN][MAXN] = {0};
long a[MAXN] = {0}, b[MAXN] = {0};
 
inline void Go(long & x) { if (x >= MOD) x -= MOD;}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        long n, m; int c;scanf("%ld%ld\n", &n, &m);
        for (long i = 1; i <= n; i++) c = getchar(), a[i] = c - 'A';getchar();
        for (long i = 1; i <= m; i++) c = getchar(), b[i] = c - 'A';
 
        bool now = 1, bef = 0;
        f[now][0][0] = 1;
        for (long l1 = 0; l1 <= n; l1++) {
                now ^= 1, bef ^= 1;
                memset(f[now], 0, sizeof f[now]);
                for (long l2 = 0; l2 <= m; l2++)
                        for (long k1 = 0; k1 <= n; k1++) {
                                if (!f[bef][l2][k1]) continue;
                                register long k2 = l1 + l2 - k1, t = f[bef][l2][k1];
 
                                if (a[l1 + 1] == a[k1 + 1]) {
                                        f[now][l2][k1 + 1] += t;
                                        Go(f[now][l2][k1 + 1]);
                                }
                                if (a[l1 + 1] == b[k2 + 1]) {
                                        f[now][l2][k1] += t;
                                        Go(f[now][l2][k1]);
                                }
                                if (b[l2 + 1] == a[k1 + 1]) {
                                        f[bef][l2 + 1][k1 + 1] += t;
                                        Go(f[bef][l2 + 1][k1 + 1]);
                                }
                                if (b[l2 + 1] == b[k2 + 1]) {
                                        f[bef][l2 + 1][k1] += t;
                                        Go(f[bef][l2 + 1][k1]);
                                }
                        }
        }
        printf("%ld\n", f[bef][m][n]);  
        return 0;
}