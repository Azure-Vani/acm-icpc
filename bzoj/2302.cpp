//#define Debug
#include <cstdio>
#include <algorithm>
#include <cstring>
namespace Solve {
        const int MAXN = 305;
        int s[MAXN], n, m, Mod;
        bool Fail = false;
 
        void Input(void) {
                scanf("%d%d%d", &n, &m, &Mod);
                for (int i = 1; i <= m; i++) {
                        int t, u; scanf("%d%d", &t, &u);
                        s[u]++;
                }
                for (int i = n; i >= 1; i--) {
                        s[i] += s[i + 1];
                        if (s[i] > n - i + 1) {
                                puts("NO");
                                Fail = true;
                                return;
                        }
                }
        }
        
        int c[MAXN][MAXN];
        void Initialize(void) {
                c[0][0] = 1;
                for (int i = 1; i <= n; i++) {
                        c[i][0] = 1;
                        for (int j = 1; j <= i; j++)
                                c[i][j] = (c[i - 1][j - 1] + c[i - 1][j]) % Mod;
                }
        }
 
        int f[MAXN][MAXN];
        void Work(void) {
                memset(f, 0, sizeof f);
                f[n + 1][0] = 1;
                for (int i = n; i >= 1; i--) {
                        for (int j = std::max(i == 1 ? n : 0, s[i]); j <= n - i + 1; j++) {
                                int Temp = 0;
                                for (int k = std::max(0, s[i] - s[i + 1]); j - k >= s[i + 1]; k++) {
                                        Temp = ((long long)Temp + (long long)c[j - s[i]][k - s[i] + s[i + 1]] * (long long)f[i + 1][j - k]) % Mod;
                                }
                                f[i][j] = Temp;
                        }
                }
                printf("YES %d\n", f[1][n]);
        }
 
        void solve(void) {
                memset(s + 1, 0, sizeof (s[0]) * n);
                Fail = false;
                Input();
                if (Fail) return;
                Initialize();
                Work();
        }
}
int main(int argc, char** argv) {
        #ifdef Debug
                freopen("c.in", "r", stdin);
                freopen("c.out", "w", stdout);
        #endif
        int _; scanf("%d", &_);
        while (_--)
                Solve::solve();
        return 0;
}