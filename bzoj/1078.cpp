//#define Debug
#include <cstdio>
#include <cstring>
namespace Solve {
        #define abs(x) ((x) > 0 ? (x) : (-(x)))
        const long MAXN = 150;
        long n, L[MAXN] = {0}, R[MAXN] = {0}, A[MAXN] = {0};
        long Dfs(long u, long* A) {
                if (u < 0) return 0;
                if (L[u] == -1 && R[u] == -1){ A[0] = u; return 1; }
                long l1[MAXN] = {0}, l2[MAXN] = {0}, s1, s2;
                s1 = Dfs(L[u], l1);
                s2 = Dfs(R[u], l2);
                long delta = 0, l = 0, v1 = 0, v2 = 0;
                if (s1 - s2 > 1) {
                        delta = s1 - s2;
                        for (long i = 0; i < delta; i++)
                                A[l++] = l1[i];
                        v1 = delta;
                        A[l++] = u;
                        for (long i = l; i <= s1 + s2; i++)
                                if ((i - l + 1) & 1)
                                        A[i] = l2[v2++];
                                else
                                        A[i] = l1[v1++];
                }else if (s2 - s1 > 1) {
                        delta = s2 - s1;
                        for (long i = 0; i <= delta; i++)
                                A[l++] = l2[i];
                        v2 = delta + 1;
                        A[l++] = u;
                        for (long i = l; i <= s1 + s2; i++)
                                if ((i - l + 1) & 1)
                                        A[i] = l1[v1++];
                                else
                                        A[i] = l2[v2++];
                }else if (s1 == s2) {
                        A[l++] = u;
                        for (long i = l; i <= s1 + s2; i++)
                                if ((i - l + 1) & 1)
                                        A[i] = l2[v2++];
                                else
                                        A[i] = l1[v1++];
                }else if (s1 < s2) {
                        A[l++] = l2[v2++], A[l++] = l2[v2++], A[l++] = u;
                        for (long i = l; i <= s1 + s2; i++)
                                if ((i - l + 1) & 1)
                                        A[i] = l1[v1++];
                                else
                                        A[i] = l2[v2++];
                }else if (s1 > s2) {
                        A[l++] = u;
                        for (long i = l; i <= s1 + s2; i++)
                                if ((i - l + 1) & 1)
                                        A[i] = l1[v1++];
                                else 
                                        A[i] = l2[v2++];
                }
                return s1 + s2 + 1;
        }
        void Work(void) {
                memset(L, -1, sizeof L); memset(R, -1, sizeof R);
                scanf("%ld", &n);
                for (long i = 1; i <= n; i++) {
                        long u; scanf("%ld", &u);
                        if (u >= 100) 
                                R[u - 100] = i;
                        else
                                L[u] = i;
                }
                Dfs(0, A);
                for (long i = 0; i < n; i++) printf("%ld ", A[i] );
                printf("%ld\n", A[n]);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        Solve::Work();
        return 0;
}