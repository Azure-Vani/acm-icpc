//#define Debug
#include <cstdio>
#include <algorithm>
#include <cctype>
#include <cstring>
namespace Solve {
        const long MAXN = 1000050;
        const long MAXM = 17000001;
        inline long Read(void) {
                long r = 0; int c;
                while (c = getchar(), !isdigit(c)) {}
                r = c - '0';
                while (c = getchar(),  isdigit(c)) r = r * 10 + c - '0';
                return r;
        }
        long p[MAXN] = {0}, n, m;bool T[MAXN] = {0}, S[MAXM] = {0};
        long A[MAXN] = {0};
        void Input(void) {
                n = Read();
                for (long i = 1; i <= n; i++) T[i] = Read();
        }
        long vs = 1, vt = 1;
        inline void Extend(void) {
                for (long i = vs; i <= vt; i++)
                        S[i<<1] = S[i], S[(i<<1) + 1] = !S[i];
                vs <<= 1, vt = (vt << 1) + 1;
        }
        void Workout(void) {
                long t = n * 8;S[1] = 1;
                while (vt <= t)
                        Extend();
                m = t;
        }
        void KMP(void) {
                long j = 0;p[1] = 0;
                for (long i = 2; i <= n; i++) {
                        while (j > 0 && T[j + 1] != T[i]) j = p[j];
                        if (T[j + 1] == T[i]) j++;
                        p[i] = j;
                }
                j = 0;
                for (long i = 0; i <= m; i++) {
                        while (j > 0 && T[j + 1] != S[i]) j = p[j];
                        if (T[j + 1] == S[i]) j++;
                        if (A[j] == -1)
                                A[j] = i - j + 1;
                        if (j == n) j = p[j];
                }
        }
        void solve(void) {
                Input();
                if (!n){puts(""); return;}
                Workout();
                memset(A, -1, sizeof(long) * (n + 1));
                KMP();
                for (long i = 1; i < n; i++) printf("%ld ", A[i]); printf("%ld\n", A[n]);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
                freopen("1.out", "w", stdout);
        #endif
        long T;
        scanf("%ld\n", &T);
        while (T--)
                Solve::solve();
        return 0;
}