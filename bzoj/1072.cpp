//#define Debug
#include <cstdio>
#include <set>
#include <cstring>
#include <algorithm>
namespace Solve {
        const long MAXN = 12;
        const long M = 1305;
        char s[MAXN] = {0}; long n, d;
        void Input(void) {
                scanf("%s", s); 
                scanf("%ld\n", &d);
                n = strlen(s);
                std::sort(s, s + n);
        }
        long f[M][M] = {0};bool hash[M][M] = {0};
        long Dfs(long mod, long state) {
                if (state == (1 << n) - 1) {
                        if (!mod) return 1;
                                else return 0;
                }
                if (hash[mod][state])
                        return f[mod][state];
                hash[mod][state] = true;
                long ret = 0;
                for (long i = 0; i < n; i++)
                        if (! ((1 << i) & state) ) {
                                ret += Dfs((mod * 10 + s[i] - '0') % d, state + (1 << i));
                        }
                return f[mod][state] = ret;
        }
        void Work(void) {
                Input();
                memset(hash, 0, sizeof hash);
                long temp = 1, l1 = 1, l2 = 1;
                for (long i = 1; i < n; i++) {
                        if (s[i] == s[i - 1]) {
                                l1++; l2 *= l1;
                        }else {
                                temp *= l2;
                                l1 = 1, l2 = 1;
                        }
                }
                temp *= l2;
                printf("%ld\n", Dfs(0, 0)/temp);
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("1.in", "r", stdin);
        #endif
        long T;
        scanf("%ld\n", &T);
        while (T--)
                Solve::Work();
        return 0;
}