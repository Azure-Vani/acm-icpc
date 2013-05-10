//#define Debug
#include <cstdio>
#include <cstring>
#include <cstdlib>
namespace Solve {
        const long MAXM = 22;
        long M[MAXM][MAXM] = {0}, n, m, MOD;
        long a[MAXM] = {0}, p[MAXM] = {0};
        void Input(void) {
                scanf("%ld %ld %ld\n", &n, &m, &MOD);
                if (n < m) {
                        long A = 1;
                        for (long i = 1; i <= n; i++) A = (A * 10) % MOD;
                        printf("%ld\n", A);
                        exit(0);
                }
                for (long i = 1; i <= m; i++) a[i] = getchar() - '0';
        }
        void KMP(void) {
                long j = 0;p[1] = 0;
                for (long i = 2; i <= m; i++) {
                        while (j > 0 && a[j + 1] != a[i]) j = p[j];
                        if (a[j + 1] == a[i])
                                p[i] = ++j;
                }
                for (long i = 0; i < m; i++)
                        for (long j = 0; j < 10; j++) {
                                long t = i;
                                while (t > 0 && a[t + 1] != j) t = p[t];
                                if (a[t + 1] == j) t++;
                                M[t][i]++;
                        }
        }
        #define Mult(a, b) {\
                long c[MAXM][MAXM] = {0};\
                for (long i = 0; i < m; i++)\
                        for (long j = 0; j < m; j++) {\
                                long temp = 0;\
                                for (long k = 0; k < m; k++)\
                                        temp = (temp + (a[i][k] * b[k][j])) % MOD;\
                                c[i][j] = temp;\
                        }\
                memcpy(a, c, sizeof a);\
        }
        void Matrix(long n) {
                long r[MAXM][MAXM] = {0};
                for (long i = 0; i < m; i++) r[i][i] = 1;
                while (n > 0) {
                        if (n & 1) Mult(r, M);
                        Mult(M, M);
                        n >>= 1;
                }
                memcpy(M, r, sizeof M);
        }
        void Work(void) {
                Input();
                KMP();
                Matrix(n);
                long A = 0;
                for (long i = 0; i < m; i++) 
                        A = (A + M[i][0]) % MOD;
                printf("%ld\n", A);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        Solve::Work();
        return 0;
}